# Generate one binary for each problem.
for f in glob(["*/*.c", "*.c"], allow_empty=True):
    base = basename(f)
    target, _ = splitext(base)
    c_binary(
        name = target,
        srcs = [f],
        compiler_flags = ["-std=c11", "-O2"],
    )

for f in glob(["*/*.cpp", "*.cpp"], allow_empty=True):
    # log.warning(f)
    base = basename(f)
    target, _ = splitext(base)
    # log.warning(base)
    # log.warning(target)

    if target == "l1813_simd":
        cc_binary(
            name = target,
            srcs = [f],
            # compiler_flags = ["-Wall", "-Wextra", "-Wconversion", "-std=c++2a", "-O2"],
            # compiler_flags = ["-Wall", "-Wextra", "-pedantic", "-std=c++2a", "-O2"],
            # compiler_flags = ["-Wall", "-Wextra", "-pedantic", "-D_GLIBCXX_DEBUG", "-g", "-std=c++23", "-Wno-unused-parameter"],
            compiler_flags = ["-Wall", "-Wextra", "-pedantic", "-D_GLIBCXX_DEBUG", "-g", "-march=native", "-std=c++23", "-Wno-unused-but-set-variable", "-Wno-unused-parameter", "-Wno-unused-variable"],
        )
    else:
        cc_library(
            name = target,
            srcs = [f],
            # compiler_flags = ["-Wall", "-Wextra", "-Wconversion", "-std=c++2a", "-O2"],
            compiler_flags = ["-Wall", "-Wextra", "-pedantic", "-std=c++23"],
        )
