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

    # Just for making some generations faster.
    priv_headers = []
    if target == "cco06p3":
        di = dirname(f)
        priv_headers = priv_headers + [join_path(di, "weights.h")]

    cc_binary(
        name = target,
        srcs = [f],
        private_hdrs = priv_headers,
        compiler_flags = ["-std=c++20", "-O2"],
    )
