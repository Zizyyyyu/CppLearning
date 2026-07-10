import h5py
import numpy as np
import torch
import torch.nn as nn
from torch.utils.data import Dataset, DataLoader


# ============================================================
# 1. 基本配置
# ============================================================

DATA_PATH = "datasets/lift/ph/low_dim_v15.hdf5"
CHECKPOINT_PATH = "best_bc_model.pth"

OBS_KEYS = [
    "object",
    "robot0_eef_pos",
    "robot0_eef_quat",
    "robot0_gripper_qpos",
]

TRAIN_RATIO = 0.8
SPLIT_SEED = 42
BATCH_SIZE = 256
NUM_SHOW_SAMPLES = 10

device = torch.device(
    "cuda" if torch.cuda.is_available() else "cpu"
)


# ============================================================
# 2. 定义与训练时完全相同的模型
# ============================================================

class MLP(nn.Module):
    def __init__(
        self,
        input_size=19,
        hidden_size=128,
        output_size=7
    ):
        super().__init__()

        self.net = nn.Sequential(
            nn.Linear(input_size, hidden_size),
            nn.ReLU(),
            nn.Linear(hidden_size , hidden_size * 2),
            nn.ReLU(),
            nn.Linear(hidden_size * 2, hidden_size * 1),
            nn.ReLU(),
            nn.Linear(hidden_size * 1, hidden_size),
            nn.ReLU(),
            nn.Linear(hidden_size, output_size)
        )

    def forward(self, x):
        return self.net(x)

# ============================================================
# 3. PyTorch Dataset
# ============================================================

class BCDataset(Dataset):
    def __init__(
        self,
        observations,
        actions,
        obs_mean=None,
        obs_std=None
    ):
        observations = torch.tensor(
            observations,
            dtype=torch.float32
        )

        actions = torch.tensor(
            actions,
            dtype=torch.float32
        )

        # 如果 checkpoint 保存了标准化参数，则使用它们
        if obs_mean is not None and obs_std is not None:
            obs_mean = torch.as_tensor(
                obs_mean,
                dtype=torch.float32
            )

            obs_std = torch.as_tensor(
                obs_std,
                dtype=torch.float32
            )

            obs_std = torch.clamp(
                obs_std,
                min=1e-6
            )

            observations = (
                observations - obs_mean
            ) / obs_std

        self.observations = observations
        self.actions = actions

    def __len__(self):
        return len(self.observations)

    def __getitem__(self, index):
        return (
            self.observations[index],
            self.actions[index]
        )


# ============================================================
# 4. 读取一条 demo
# ============================================================

def load_one_demo(demo):
    obs_parts = []

    for key in OBS_KEYS:
        obs_parts.append(
            demo["obs"][key][:]
        )

    observations = np.concatenate(
        obs_parts,
        axis=-1
    ).astype(np.float32)

    actions = demo["actions"][:].astype(
        np.float32
    )

    return observations, actions


# ============================================================
# 5. 使用与训练时相同的方法获取验证集
# ============================================================

def load_validation_dataset(
    data_path,
    train_ratio=0.8,
    seed=42
):
    val_observations = []
    val_actions = []

    with h5py.File(data_path, "r") as f:
        data = f["data"]

        demo_names = sorted(
            data.keys(),
            key=lambda x: int(
                x.split("_")[1]
            )
        )

        shuffled_demo_names = demo_names.copy()

        rng = np.random.default_rng(seed)
        rng.shuffle(shuffled_demo_names)

        split_index = int(
            len(shuffled_demo_names)
            * train_ratio
        )

        val_demo_names = (
            shuffled_demo_names[split_index:]
        )

        for demo_name in val_demo_names:
            observations, actions = load_one_demo(
                data[demo_name]
            )

            val_observations.append(
                observations
            )

            val_actions.append(
                actions
            )

    val_observations = np.concatenate(
        val_observations,
        axis=0
    )

    val_actions = np.concatenate(
        val_actions,
        axis=0
    )

    return (
        val_observations,
        val_actions,
        val_demo_names
    )


# ============================================================
# 6. 加载 checkpoint
# ============================================================

def load_model(checkpoint_path):
    checkpoint = torch.load(
        checkpoint_path,
        map_location=device
    )

    input_size = checkpoint.get(
        "input_size",
        19
    )

    hidden_size = checkpoint.get(
        "hidden_size",
        128
    )

    output_size = checkpoint.get(
        "output_size",
        7
    )

    model = MLP(
        input_size=input_size,
        hidden_size=hidden_size,
        output_size=output_size
    ).to(device)

    # 支持两种保存格式
    if "model_state_dict" in checkpoint:
        model.load_state_dict(
            checkpoint["model_state_dict"]
        )
    else:
        model.load_state_dict(checkpoint)

    model.eval()

    return model, checkpoint


# ============================================================
# 7. 展示若干样本预测
# ============================================================

@torch.no_grad()
def show_predictions(
    model,
    dataset,
    num_samples=10
):
    num_samples = min(
        num_samples,
        len(dataset)
    )

    # 固定随机种子，使每次展示相同样本
    rng = np.random.default_rng(42)

    sample_indices = rng.choice(
        len(dataset),
        size=num_samples,
        replace=False
    )

    for number, index in enumerate(
        sample_indices,
        start=1
    ):
        observation, true_action = dataset[
            int(index)
        ]

        model_input = (
            observation
            .unsqueeze(0)
            .to(device)
        )

        predicted_action = (
            model(model_input)
            .squeeze(0)
            .cpu()
        )

        error = predicted_action - true_action

        sample_mse = torch.mean(
            error ** 2
        ).item()

        print("\n" + "=" * 70)
        print(
            f"样本 {number}，数据索引：{index}"
        )

        print("\n预测动作：")
        print(
            predicted_action.numpy()
        )

        print("\n专家动作：")
        print(
            true_action.numpy()
        )

        print("\n预测误差：")
        print(
            error.numpy()
        )

        print(
            f"\n该样本 MSE：{sample_mse:.8f}"
        )


# ============================================================
# 8. 计算整个验证集的误差
# ============================================================

@torch.no_grad()
def evaluate_model(
    model,
    dataloader
):
    model.eval()

    total_squared_error = 0.0
    total_elements = 0

    # 保存每个动作维度的平方误差
    per_dimension_squared_error = torch.zeros(
        7,
        device=device
    )

    total_samples = 0

    for observations, true_actions in dataloader:
        observations = observations.to(device)
        true_actions = true_actions.to(device)

        predicted_actions = model(
            observations
        )

        squared_error = (
            predicted_actions - true_actions
        ) ** 2

        total_squared_error += (
            squared_error.sum().item()
        )

        total_elements += (
            squared_error.numel()
        )

        per_dimension_squared_error += (
            squared_error.sum(dim=0)
        )

        total_samples += (
            observations.size(0)
        )

    overall_mse = (
        total_squared_error
        / total_elements
    )

    per_dimension_mse = (
        per_dimension_squared_error
        / total_samples
    ).cpu().numpy()

    return overall_mse, per_dimension_mse


# ============================================================
# 9. 主函数
# ============================================================

def main():
    print("运行设备：", device)
    print("数据路径：", DATA_PATH)
    print("模型路径：", CHECKPOINT_PATH)

    # 加载模型
    model, checkpoint = load_model(
        CHECKPOINT_PATH
    )

    print("\n模型加载成功")

    if "epoch" in checkpoint:
        print(
            "最佳 Epoch：",
            checkpoint["epoch"]
        )

    if "val_loss" in checkpoint:
        print(
            "保存时验证损失：",
            checkpoint["val_loss"]
        )

    # 获取标准化参数
    obs_mean = checkpoint.get(
        "obs_mean",
        None
    )

    obs_std = checkpoint.get(
        "obs_std",
        None
    )

    if obs_mean is not None and obs_std is not None:
        print("使用 checkpoint 中的 observation 标准化参数")
    else:
        print("checkpoint 中没有标准化参数，使用原始 observation")

    # 加载验证集
    (
        val_observations,
        val_actions,
        val_demo_names
    ) = load_validation_dataset(
        DATA_PATH,
        train_ratio=TRAIN_RATIO,
        seed=SPLIT_SEED
    )

    print("\n验证轨迹数量：", len(val_demo_names))
    print(
        "验证 observations shape：",
        val_observations.shape
    )
    print(
        "验证 actions shape：",
        val_actions.shape
    )

    val_dataset = BCDataset(
        val_observations,
        val_actions,
        obs_mean=obs_mean,
        obs_std=obs_std
    )

    val_loader = DataLoader(
        val_dataset,
        batch_size=BATCH_SIZE,
        shuffle=False,
        num_workers=0,
        pin_memory=torch.cuda.is_available()
    )

    # 展示若干样本预测
    show_predictions(
        model,
        val_dataset,
        num_samples=NUM_SHOW_SAMPLES
    )

    # 整个验证集评估
    overall_mse, per_dimension_mse = (
        evaluate_model(
            model,
            val_loader
        )
    )

    print("\n" + "=" * 70)
    print("整个验证集评估结果")

    print(
        f"\nOverall MSE：{overall_mse:.8f}"
    )

    action_names = [
        "position_x",
        "position_y",
        "position_z",
        "rotation_x",
        "rotation_y",
        "rotation_z",
        "gripper",
    ]

    print("\n每个动作维度的 MSE：")

    for name, mse in zip(
        action_names,
        per_dimension_mse
    ):
        print(
            f"{name:15s}: {mse:.8f}"
        )


if __name__ == "__main__":
    main()