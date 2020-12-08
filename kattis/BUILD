# Generate one binary for each problem.
for f in glob(["*.c"]):
    c_binary(
            name = f[:-2],
            srcs = [f],
            compiler_flags = [
                    "-g", "-O2", "-std=gnu11", "-static", "-Wall", "-Wextra"
                    ],
            linker_flags = [
                    "-lm"
                    ]
            )

for f in glob(["*.cpp"]):
    cc_binary(
            name = f[:-4],
            srcs = [f],
            compiler_flags = [
                    "-g", "-O2", "-std=gnu++17", "-static", "-Wall", "-Wextra"
                    ],
            linker_flags = []
            )
# -static -fno-strict-aliasing -DONLINE_JUDGE -lm -s 
#   -std=c11 -Wl,--stack=67108864 -O2
