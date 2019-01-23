#ifndef DATA_STORE_H
#define DATA_STORE_H

#include <string>

namespace protocached {

namespace datastore {

enum OperationStatus {
  KEY_FOUND,
  KEY_NOT_FOUND,
  SET_SUCCEED,
  SET_FAIL, // TODO(joejoevictor): Couldn't think of when this will happen yet
};

// TODO(joejoevictor): We should probably put this into a namespace
class DataStore {
public:
  virtual ~DataStore() {}
  virtual OperationStatus Get(const ::std::string& key, ::std::string& value) = 0; // Pure virtual
  virtual OperationStatus Set(const ::std::string& key, const ::std::string& value) = 0; // Pure virtual
};

} // datastore namespace

} // protocached namespace

#endif
