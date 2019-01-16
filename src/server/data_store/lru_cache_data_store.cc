#include "lru_cache_data_store.h"

::std::string KeyValuePair::get_key() const {
  return key;
}

::std::string KeyValuePair::get_value() const {
  return value;
}

// This is not thread safe and very naive implementation.
::LruCacheDataStore::LruCacheDataStore(::std::uint32_t capacity) {
  capacity = capacity;
  key_iterator_map = ::std::unordered_map<::std::string, ::std::list<KeyValuePair>::iterator>();
  pairs = ::std::list<KeyValuePair>();
}

::LruCacheDataStore::~LruCacheDataStore() {}

::std::string LruCacheDataStore::Get(::std::string key) {
  if (key_iterator_map.find(key) == key_iterator_map.end()) {
    return nullptr;
  }
  ::std::list<KeyValuePair>::const_iterator existing_pair_iterator = key_iterator_map.at(key);
  // TODO(joejoevictor): This seems dumb. I wonder if we could avoid the copy.
  KeyValuePair pair_to_be_inserted = KeyValuePair(key, (*existing_pair_iterator).get_value());
  pairs.erase(existing_pair_iterator);
  key_iterator_map.erase(key);
  pairs.push_back(pair_to_be_inserted);
  key_iterator_map[key] = --(pairs.end());
  return key_iterator_map.at(key) -> get_value();
}

void LruCacheDataStore::Set(::std::string key, ::std::string value) {
  // Case 1: key, value pair is not in the datastore
  if (key_iterator_map.find(key) == key_iterator_map.end()) {
    // Need to evict
    if (pairs.size() >= capacity) {
      KeyValuePair pair_to_be_evicted = pairs.front();
      pairs.pop_front();
      key_iterator_map.erase(pair_to_be_evicted.get_key());
    }
  } else {
    // Case 2: key, value pair already in datastore, just need to re surface it.
    ::std::list<KeyValuePair>::const_iterator existing_pair_iterator = key_iterator_map.at(key);
    pairs.erase(existing_pair_iterator);
    key_iterator_map.erase(key);
  }
  pairs.push_back(KeyValuePair(key, value));
  key_iterator_map[key] = --(pairs.end());
}
