cc_binary(
    name = "advent-of-code",
    srcs = [
        "main.cpp",
    ],
    compiler_flags = [
        "-O2",
        "-std=c++20",
        "-g",
    ],
    linker_flags = [
        "-flto",
    ],
    deps = [
        "//aoc/src/years:years_lib",
    ],
)
