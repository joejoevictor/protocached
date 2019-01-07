load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# gRPC libraries
http_archive(
    name = "com_github_grpc_grpc",
    urls = [
        "https://github.com/grpc/grpc/archive/c7cc34e2d76afe67528ac5b20c5ccbe0692757e8.tar.gz",
    ],
    strip_prefix = "grpc-c7cc34e2d76afe67528ac5b20c5ccbe0692757e8",
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()
