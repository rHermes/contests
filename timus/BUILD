# Generate one binary for each problem.
for f in glob(["*.c"]):
    c_binary(
        name = f[:-2],
        srcs = [f],
        compiler_flags = [
            "-g",
            "-std=c2x",
            "-O2",
            "-fno-strict-aliasing",
            "-march=native",
        ],
        linker_flags = [
            "-lm",
        ],
    )

for f in glob(["*.cpp"]):
    cc_binary(
        name = f[:-4],
        srcs = [f],
        compiler_flags = [
            "-g",
            "-std=c++2a",
            "-O2",
            "-fno-strict-aliasing",
            "-march=native",
        ],
        linker_flags = [
            "-lm",
        ],
    )
