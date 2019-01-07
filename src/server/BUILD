proto_library(
    name = "protocached_proto",
    srcs = [
        "protocached.proto",
    ],
)

cc_proto_library(
    name = "protocached_cc_proto",
    deps = [
        ":protocached_proto"
    ],
)

cc_binary(
    name = "server",
    srcs = [
        "main.cc",
    ],
    deps = [
        ":protocached_cc_proto"
    ],
)
