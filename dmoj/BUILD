# Generate one binary for each problem.
for f in glob(["*.c"]):
    c_binary(
        name = f[:-2],
        srcs = [f],
        compiler_flags = ["-std=c11"],
    )

for f in glob(["*.cpp"]):
    cc_binary(
        name = f[:-4],
        srcs = [f],
        compiler_flags = ["-std=c++14"],
    )
