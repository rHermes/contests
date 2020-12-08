# Generate one binary for each problem.
for f in glob(["*.c"]):
    c_binary(
        name = f[:-2],
        srcs = [f],
    )
