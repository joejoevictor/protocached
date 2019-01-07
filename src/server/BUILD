# BUILD file for protocached server
package(default_visibility = ["//visibility:public"])

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
