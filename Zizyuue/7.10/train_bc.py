import h5py
import numpy as np

import torch
DATA_PATH = "datasets/lift/ph/low_dim_v15.hdf5"

OBS_KEYS = [
    "object",
    "robot0_eef_pos",
    "robot0_eef_quat",
    "robot0_gripper_qpos",
]


def load_dataset(data_path):
    all_observations = []
    all_actions = []
    demo_lengths = []

    with h5py.File(data_path, "r") as f:
        data = f["data"]

        demo_names = sorted(
            data.keys(),
            key=lambda x: int(x.split("_")[1])
        )

        for demo_name in demo_names:
            demo = data[demo_name]

            obs_parts = []

            for key in OBS_KEYS:
                obs_parts.append(
                    demo["obs"][key][:]
                )

            observations = np.concatenate(
                obs_parts,
                axis=-1
            )

            actions = demo["actions"][:]

            all_observations.append(observations)
            all_actions.append(actions)
            demo_lengths.append(len(actions))

    all_observations = np.concatenate(
        all_observations,
        axis=0
    ).astype(np.float32)

    all_actions = np.concatenate(
        all_actions,
        axis=0
    ).astype(np.float32)

    return all_observations, all_actions, demo_lengths
observations, actions, demo_lengths = load_dataset(DATA_PATH)

print("observations shape:", observations.shape)
print("actions shape:", actions.shape)

print("轨迹数量:", len(demo_lengths))
print("前 10 条轨迹长度:", demo_lengths[:10])
print("最短轨迹长度:", min(demo_lengths))
print("最长轨迹长度:", max(demo_lengths))
print("平均轨迹长度:", np.mean(demo_lengths))
print("总时间步:", sum(demo_lengths))
def load_one_demo(demo):
    """
    读取一条轨迹，返回：
    observations: (T, 19)
    actions:      (T, 7)
    """
    obs_parts = []

    for key in OBS_KEYS:
        obs_parts.append(demo["obs"][key][:])

    observations = np.concatenate(
        obs_parts,
        axis=-1
    ).astype(np.float32)

    actions = demo["actions"][:].astype(np.float32)

    return observations, actions


def load_and_split_dataset(
    data_path,
    train_ratio=0.8,
    seed=42,
):
    train_observations = []
    train_actions = []

    val_observations = []
    val_actions = []

    with h5py.File(data_path, "r") as f:
        data = f["data"]

        demo_names = sorted(
            data.keys(),
            key=lambda x: int(x.split("_")[1])
        )

        shuffled_demo_names = demo_names.copy()
        rng = np.random.default_rng(seed)
        rng.shuffle(shuffled_demo_names)
        split_index = int(
            len(shuffled_demo_names) * train_ratio
        )

        train_demo_names = shuffled_demo_names[:split_index]
        val_demo_names = shuffled_demo_names[split_index:]

        for demo_name in train_demo_names:
            observations, actions = load_one_demo(
                data[demo_name]
            )

            train_observations.append(observations)
            train_actions.append(actions)

        for demo_name in val_demo_names:
            observations, actions = load_one_demo(
                data[demo_name]
            )

            val_observations.append(observations)
            val_actions.append(actions)
    train_observations = np.concatenate(
        train_observations,
        axis=0
    )

    train_actions = np.concatenate(
        train_actions,
        axis=0
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
        train_observations,
        train_actions,
        val_observations,
        val_actions,
        train_demo_names,
        val_demo_names,
    )


(
    train_observations,
    train_actions,
    val_observations,
    val_actions,
    train_demo_names,
    val_demo_names,
) = load_and_split_dataset(
    DATA_PATH,
    train_ratio=0.8,
    seed=42,
)


print("训练轨迹数量：", len(train_demo_names))
print("验证轨迹数量：", len(val_demo_names))

print("\n训练集：")
print("train observations shape:", train_observations.shape)
print("train actions shape:", train_actions.shape)

print("\n验证集：")
print("val observations shape:", val_observations.shape)
print("val actions shape:", val_actions.shape)

print("\n前 10 条训练轨迹：")
print(train_demo_names[:10])

print("\n前 10 条验证轨迹：")
print(val_demo_names[:10])
overlap = set(train_demo_names) & set(val_demo_names)
print("\n重复轨迹：", overlap)

import torch
from torch.utils.data import Dataset, DataLoader


class BCDataset(Dataset):
    def __init__(self, observations, actions):
        self.observations = torch.tensor(
            observations,
            dtype=torch.float32
        )

        self.actions = torch.tensor(
            actions,
            dtype=torch.float32
        )

    def __len__(self):
        return len(self.observations)

    def __getitem__(self, index):
        observation = self.observations[index]
        action = self.actions[index]

        return observation, action
train_dataset = BCDataset(
    train_observations,
    train_actions
)

val_dataset = BCDataset(
    val_observations,
    val_actions
)
print("训练 Dataset 长度：", len(train_dataset))
print("验证 Dataset 长度：", len(val_dataset))
BATCH_SIZE = 1024

train_loader = DataLoader(
    train_dataset,
    batch_size=BATCH_SIZE,
    shuffle=True,
    num_workers=0
)

val_loader = DataLoader(
    val_dataset,
    batch_size=BATCH_SIZE,
    shuffle=False,
    num_workers=0
)
batch_observations, batch_actions = next(
    iter(train_loader)
)

print("\n一个训练 batch：")
print("batch observations shape:", batch_observations.shape)
print("batch actions shape:", batch_actions.shape)

print("\n数据类型：")
print("observations dtype:", batch_observations.dtype)
print("actions dtype:", batch_actions.dtype)

print("\n第一个 batch 中的第一个 observation：")
print(batch_observations[0])

print("\n对应 action：")
print(batch_actions[0])
import torch
import torch.nn as nn


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
device = torch.device(
    "cuda" if torch.cuda.is_available() else "cpu"
)

model = MLP(
    input_size=19,
    hidden_size=128,
    output_size=7
).to(device)

print(model)
batch_observations = batch_observations.to(device)
batch_actions = batch_actions.to(device)
pred_actions = model(batch_observations)
print("输入 shape：", batch_observations.shape)
print("预测动作 shape：", pred_actions.shape)
print("真实动作 shape：", batch_actions.shape)
criterion = nn.MSELoss()

optimizer = torch.optim.Adam(
    model.parameters(),
    lr=1e-3
)
import matplotlib.pyplot as plt

criterion = nn.MSELoss()

optimizer = torch.optim.Adam(
    model.parameters(),
    lr=5e-4
)

EPOCHS = 500
SAVE_PATH = "best_bc_model.pth"

train_losses = []
val_losses = []

best_val_loss = float("inf")
best_epoch = 0


for epoch in range(EPOCHS):

    # =========================
    # 1. 训练阶段
    # =========================
    model.train()

    total_train_loss = 0.0
    total_train_samples = 0

    for batch_observations, batch_actions in train_loader:

        batch_observations = batch_observations.to(device)
        batch_actions = batch_actions.to(device)

        # 前向传播
        pred_actions = model(batch_observations)

        # 计算损失
        loss = criterion(
            pred_actions,
            batch_actions
        )

        # 清空上一轮梯度
        optimizer.zero_grad()

        # 反向传播
        loss.backward()

        # 更新参数
        optimizer.step()

        batch_size = batch_observations.size(0)

        total_train_loss += loss.item() * batch_size
        total_train_samples += batch_size

    average_train_loss = (
        total_train_loss / total_train_samples
    )

    train_losses.append(average_train_loss)

    # =========================
    # 2. 验证阶段
    # =========================
    model.eval()

    total_val_loss = 0.0
    total_val_samples = 0

    with torch.no_grad():

        for val_observations, val_actions in val_loader:

            val_observations = val_observations.to(device)
            val_actions = val_actions.to(device)

            pred_val_actions = model(
                val_observations
            )

            val_loss = criterion(
                pred_val_actions,
                val_actions
            )

            batch_size = val_observations.size(0)

            total_val_loss += (
                val_loss.item() * batch_size
            )

            total_val_samples += batch_size

    average_val_loss = (
        total_val_loss / total_val_samples
    )

    val_losses.append(average_val_loss)

    # =========================
    # 3. 保存最佳模型
    # =========================
    if average_val_loss < best_val_loss:

        best_val_loss = average_val_loss
        best_epoch = epoch + 1

        torch.save(
            {
                "epoch": best_epoch,
                "model_state_dict": model.state_dict(),
                "optimizer_state_dict": optimizer.state_dict(),
                "train_loss": average_train_loss,
                "val_loss": average_val_loss,
                "input_size": 19,
                "hidden_size": 128,
                "output_size": 7,
            },
            SAVE_PATH
        )

        save_message = " <-- 保存最佳模型"

    else:
        save_message = ""

    print(
        f"Epoch [{epoch + 1:03d}/{EPOCHS}] | "
        f"Train Loss: {average_train_loss:.6f} | "
        f"Val Loss: {average_val_loss:.6f}"
        f"{save_message}"
    )


print("\n训练完成")
print("最佳 Epoch：", best_epoch)
print("最佳验证损失：", best_val_loss)
print("模型保存位置：", SAVE_PATH)

def plot_loss(
    train_losses,
    val_losses,
    save_path="bc_loss_curve.png"
):
    epochs = range(
        1,
        len(train_losses) + 1
    )

    plt.figure(figsize=(8, 5))

    plt.plot(
        epochs,
        train_losses,
        label="Train Loss"
    )

    plt.plot(
        epochs,
        val_losses,
        label="Validation Loss"
    )

    plt.xlabel("Epoch")
    plt.ylabel("MSE Loss")
    plt.title("Behavior Cloning Loss")
    plt.legend()
    plt.grid(True)

    plt.tight_layout()
    plt.savefig(
        save_path,
        dpi=150
    )

    plt.show()

    print("损失曲线已保存：", save_path)


plot_loss(
    train_losses,
    val_losses
)