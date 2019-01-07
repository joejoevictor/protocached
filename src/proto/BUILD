# BUILD file for protos
package(default_visibility = ["//visibility:public"])
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

