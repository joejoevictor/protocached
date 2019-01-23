#ifndef LRU_CACHE_DATA_STORE_H
#define LRU_CACHE_DATA_STORE_H

#include <string>
#include <unordered_map>
#include <list>
#include <cstdint>
#include "data_store.h"

namespace protocached {

namespace datastore {

namespace lrucache {

using protocached::datastore::OperationStatus;

// Immutable key value pair wrapper
class KeyValuePair {
public:
  KeyValuePair(::std::string key, ::std::string value) : key(key), value(value) {}
  ~KeyValuePair() {}
  ::std::string get_key() const;
  ::std::string get_value() const;

private:
  ::std::string key;
  ::std::string value;
};

// TODO(joejoevictor): We should probably put this into a namespace
class LruCacheDataStore : public DataStore {
public:
  LruCacheDataStore(::std::uint32_t capacity);
  ~LruCacheDataStore();
  OperationStatus Get(const ::std::string& key, ::std::string& value);
  OperationStatus Set(const ::std::string& key, const ::std::string& value);

private:
  ::std::uint32_t capacity;
  ::std::list<KeyValuePair> pairs;
  // The map from key to iterator pointing to the the value
  ::std::unordered_map<::std::string, ::std::list<KeyValuePair>::iterator> key_iterator_map;
};

} // lrucache namespace

} // datastore namespace

} // protocached namespace

#endif
