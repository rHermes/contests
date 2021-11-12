years = []

for x in glob(["[0-9]*/"]):
    ye = cc_library(
        name = "year_{}".format(x),
        srcs = glob([join_path(x, "*.cpp")]),
        hdrs = [join_path(x, "year.hpp")],
        compiler_flags = [
            "-O2",
            "-std=c++20",
        ],
        private_hdrs = [join_path(x, "days.hpp")],
        deps = [
            "//aoc/src/common",
        ],
    )
    years += [ye]

a = cc_library(
    name = "years_lib",
    srcs = [
        "years.cpp",
    ],
    hdrs = [
        "years.hpp",
    ],
    compiler_flags = [
        "-O2",
        "-std=c++20",
    ],
    visibility = [
        "//aoc/src/...",
    ],
    deps = years,
)
