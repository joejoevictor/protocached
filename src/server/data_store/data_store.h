#ifndef DATA_STORE_H
#define DATA_STORE_H

#include <string>

// TODO(joejoevictor): We should probably put this into a namespace
class DataStore {
public:
  virtual ~DataStore() {}
  // TODO(joejoevictor): Use optional as returned result
  virtual ::std::string Get(::std::string key) = 0; // Pure virtual
  virtual void Set(::std::string key, ::std::string value) = 0; // Pure virtual
};

#endif
