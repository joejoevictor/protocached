# ProtoCached
Memcached with ProtoBuff


## Build System

We use bazel as build system.

```
bazel build //src/server:server
bazel build //src/client:client
```

Build artifacts are inside bazel-bin/*
