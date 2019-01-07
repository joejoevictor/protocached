# BUILD file for protos
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
    visibility = ["//visibility:public"],
)


