# BUILD file for protocached server
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "server",
    srcs = [
        "main.cc",
    ],
    deps = [
        "//src/proto:protocached_cc_proto",
        "//src/server/data_store:data_store",
        "//src/server/data_store:lru_cache_data_store",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
