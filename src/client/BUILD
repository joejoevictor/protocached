# BUILD file for ProtoCached client
package(default_visibility = ["//visibility:public"])
cc_binary(
    name = "client",
    srcs = ["main.cpp"],
    deps = [
        "//src/proto:protocached_cc_proto",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
