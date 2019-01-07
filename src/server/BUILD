# BUILD file for protocached server
cc_binary(
    name = "server",
    srcs = [
        "main.cc",
    ],
    deps = [
        "//src/proto:protocached_cc_proto",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
