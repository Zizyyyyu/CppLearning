import h5py

path = "datasets/lift/ph/low_dim_v15.hdf5"


def show_group(group, indent=0, max_depth=3):
    if indent // 2 > max_depth:
        return

    for key in group.keys():
        item = group[key]

        if isinstance(item, h5py.Group):
            print(" " * indent + f"[Group] {key}")
            show_group(item, indent + 2, max_depth)
        else:
            print(
                " " * indent
                + f"[Dataset] {key:25s} "
                + f"shape={item.shape}, dtype={item.dtype}"
            )


with h5py.File(path, "r") as f:
    print("根节点：", list(f.keys()))
    print("示范数量：", len(f["data"]))
    print()

    show_group(f["data"]["demo_0"])