import h5py

DATASET_PATH = "datasets/lift/ph/low_dim_v15.hdf5"


with h5py.File(DATASET_PATH, "r") as f:


    print("文件根节点：")
    print(list(f.keys()))


    data = f["data"]

    print("\n轨迹数量：")
    print(len(data))


    demo_names = list(data.keys())

    print("\n前 10 条轨迹名称：")
    print(demo_names[:10])


    demo_name = demo_names[0]
    demo = data[demo_name]

    print(f"\n当前查看轨迹：{demo_name}")

    print("\n这条轨迹包含的字段：")
    print(list(demo.keys()))

    print("\n一级字段信息：")

    for key in demo.keys():
        item = demo[key]

        if isinstance(item, h5py.Dataset):
            print(
                f"{key:15s} "
                f"shape={item.shape}, "
                f"dtype={item.dtype}"
            )

        elif isinstance(item, h5py.Group):
            print(f"{key:15s} 是一个 Group")
    obs = demo["obs"]

    print("\nobs 中包含的字段：")

    for key in obs.keys():
        item = obs[key]

        print(
            f"{key:30s} "
            f"shape={item.shape}, "
            f"dtype={item.dtype}"
        )
    next_obs = demo["next_obs"]
    print("\nnext_obs 中包含的字段：")
    for key in next_obs.keys():
        item = next_obs[key]
        print(
            f"{key:30s} "
            f"shape={item.shape}, "
            f"dtype={item.dtype}"
        )