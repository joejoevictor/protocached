cc_library(
  name = "data_store_test",
  srcs = [
    "data_store_test.cc",
  ],
  copts = [
    "-Iexternal/gtest/include",
  ],
  deps = [
    "@gtest//:main",
    "//src/server/data_store:data_store",
    "//src/server/data_store:lru_cache_data_store",
  ]
)
