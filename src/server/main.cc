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

// TODO(joejoevictor): Move this to separate header and implementation file
class ProtocachedServiceImpl final : public ::protocached::Protocached::Service {
  ::grpc::Status Get(
    ::grpc::ServerContext* context,
    const ::protocached::GetRequest* request,
    ::protocached::GetResponse* response
  ) override {
    ::protocached::CachedValue cachedValue;
    cachedValue.set_value("This is a hard-coded value");
    response -> mutable_value() -> CopyFrom(cachedValue);
    return ::grpc::Status::OK;
  } 
  
  ::grpc::Status Set(
    ::grpc::ServerContext* context,
    const ::protocached::SetRequest* request,
    ::protocached::SetResponse* response
  ) override {
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
