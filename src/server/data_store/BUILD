package(
  default_visibility = [
    "//visibility:public",
  ]
)

cc_library(
  name = "data_store",
  srcs = [
    "data_store.h",
  ],
)

cc_library(
  name = "lru_cache_data_store",
  srcs = [
    "lru_cache_data_store.h",
    "lru_cache_data_store.cc",
  ],
  deps = [
    ":data_store",
  ],
)
