target("png2ico")
set_kind("binary")
set_warnings("all", "error")
set_languages("c99")
add_files("src/*.c")
add_cflags("-Os", "-Wall", "-Wextra", "-Wfloat-equal", "-Wundef", "-Wshadow", "-Wpointer-arith", "-Wcast-align", "-Wstrict-prototypes", "-Wswitch-default", "-Wunreachable-code")
