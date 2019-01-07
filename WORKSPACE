workspace(name = "protocached")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# gRPC libraries
http_archive(
    name = "com_github_grpc_grpc",
    urls = [
        "https://github.com/grpc/grpc/archive/46bd2f7adb926053345665d5c487fa20acd2b5b0.tar.gz",
    ],
    strip_prefix = "grpc-46bd2f7adb926053345665d5c487fa20acd2b5b0",
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()


# proto_library, cc_proto_library, and java_proto_library rules implicitly
# depend on @com_google_protobuf for protoc and proto runtimes.
# This statement defines the @com_google_protobuf repo.
http_archive(
    name = "com_google_protobuf",
    sha256 = "d6618d117698132dadf0f830b762315807dc424ba36ab9183f1f436008a2fdb6",
    strip_prefix = "protobuf-3.6.1.2",
    urls = ["https://github.com/google/protobuf/archive/v3.6.1.2.zip"],
)
