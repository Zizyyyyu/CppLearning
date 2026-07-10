import h5py
import numpy as np

path = "datasets/lift/ph/low_dim_v15.hdf5"

np.set_printoptions(
    precision=4,
    suppress=True,
    linewidth=160,
)

with h5py.File(path, "r") as f:
    demo = f["data"]["demo_0"]

    print("轨迹包含的字段：")
    print(list(demo.keys()))

    print("\n轨迹长度：", demo["actions"].shape[0])

    print("\n前 5 个动作：")
    print(demo["actions"][:5])

    print("\n前 5 个末端位置 robot0_eef_pos：")
    print(demo["obs"]["robot0_eef_pos"][:5])

    print("\n前 5 个夹爪状态 robot0_gripper_qpos：")
    print(demo["obs"]["robot0_gripper_qpos"][:5])

    print("\n前 5 个 object：")
    print(demo["obs"]["object"][:5])

    if "rewards" in demo:
        print("\nreward：")
        print(demo["rewards"][:])

    if "dones" in demo:
        print("\ndone：")
        print(demo["dones"][:])