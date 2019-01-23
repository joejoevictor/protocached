/**
 * Copyright 2019, Joe Chen, Gavin Lin
 * All rights reserved.
 *
 * Authors:
 *   "Joe Chen" <joejoevictor@gmail.com>
 *   "Gavin Lin" <gavin.lin.asd@gmail.com>
 */
#include <iostream>
#include <grpcpp/grpcpp.h>
#include "src/proto/protocached.pb.h"
#include "src/proto/protocached.grpc.pb.h"
#include "src/server/data_store/data_store.h"
#include "src/server/data_store/lru_cache_data_store.h"

using protocached::datastore::OperationStatus;
using protocached::datastore::DataStore;
using protocached::datastore::lrucache::LruCacheDataStore;

// TODO(joejoevictor): Move this to separate header and implementation file
class ProtocachedServiceImpl final : public ::protocached::Protocached::Service {
private:
  DataStore* data_store;

public:
  ProtocachedServiceImpl() {
    data_store = new LruCacheDataStore(100);
  }

  ~ProtocachedServiceImpl() {
    delete data_store;
  }

  ::grpc::Status Get(
    ::grpc::ServerContext* context,
    const ::protocached::GetRequest* request,
    ::protocached::GetResponse* response
  ) override {
    ::protocached::CachedValue cachedValue;
    ::std::string value;
    OperationStatus status = data_store -> Get(request -> key(), value);
    if (status == OperationStatus::KEY_FOUND) {
      response -> mutable_value() -> set_value(value);
    }
    return ::grpc::Status::OK;
  }

  ::grpc::Status Set(
    ::grpc::ServerContext* context,
    const ::protocached::SetRequest* request,
    ::protocached::SetResponse* response
  ) override {
    // TODO(joejoevictor): value().value() seems hacky...Is there a better way
    // to name the proto field or reorganize the protos.
    data_store -> Set(request -> key(), request -> value().value());
    return ::grpc::Status::OK;
  }
};

void RunServer() {
  ProtocachedServiceImpl service;
  ::grpc::ServerBuilder builder;
  builder.AddListeningPort("0.0.0.0:18081", grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  ::std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  ::std::cout << "Server listening on 0.0.0.0:18081" << std::endl;
  server->Wait();
}

int main() {
    ::std::cout << "Starting ProtoCached server." << ::std::endl;
    RunServer();
    return 0;
}
