# BUILD file for protos
package(default_visibility = ["//visibility:public"])

load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

proto_library(
    name = "protocached_proto",
    srcs = [
        "protocached.proto",
    ],
)

cc_grpc_library(
    name = "protocached_cc_proto",
    srcs = [
        "protocached.proto"
    ],
    deps = [],
    proto_only = False,
    well_known_protos = False,
)

