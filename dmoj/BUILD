# Generate one binary for each problem.
for f in glob(["*/*.c", "*.c"]):
    base = basename(f)
    target, _ = splitext(base)
    c_binary(
        name = target,
        srcs = [f],
        compiler_flags = ["-std=c11", "-O2"],
    )

for f in glob(["*/*.cpp", "*.cpp"]):
    base = basename(f)
    target, _ = splitext(base)
    cc_binary(
        name = target,
        srcs = [f],
        compiler_flags = ["-std=c++20", "-O2"],
    )
