#include <string>
#include "gtest/gtest.h"
#include "src/server/data_store/data_store.h"
#include "src/server/data_store/lru_cache_data_store.h"
namespace {

using protocached::datastore::DataStore;
using protocached::datastore::OperationStatus;
using protocached::datastore::lrucache::LruCacheDataStore;

// Test Fixture
class LruCacheDataStoreTest : public testing::Test {
 protected:
  // Per TEST_F setup
  void SetUp() override {
    data_store = new LruCacheDataStore(2);
    data_store -> Set("A", "1");
  }

  // Per TEST_F cleanup
  void TearDown() override {
    delete data_store;
  }

  DataStore* data_store;
};

TEST_F(LruCacheDataStoreTest, Get) {
  ::std::string value_a;
  OperationStatus status_a = data_store -> Get("A", value_a);
  EXPECT_EQ(value_a, "1");
  EXPECT_EQ(status_a, OperationStatus::KEY_FOUND);
}

TEST_F(LruCacheDataStoreTest, TestingLRUEviction) {
  data_store -> Set("B", "2");
  data_store -> Set("C", "3");
  ::std::string value_a;
  ::std::string value_b;
  ::std::string value_c;
  EXPECT_EQ(data_store -> Get("A", value_a), OperationStatus::KEY_NOT_FOUND);
  OperationStatus status_b = data_store -> Get("B", value_b);
  EXPECT_EQ(status_b, OperationStatus::KEY_FOUND);
  EXPECT_EQ(value_b, "2");
  OperationStatus status_c = data_store -> Get("C", value_c);
  EXPECT_EQ(status_c, OperationStatus::KEY_FOUND);
  EXPECT_EQ(value_c, "3");
}

} // namespace
