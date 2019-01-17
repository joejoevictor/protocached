// Copyright 2019
// Authors:
//   "Joe Chen" <joejoevictor@gmail.com>
//   "Gavin Lin" <gavin.lin.asd@gmail.com>
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <string>

#include "src/proto/protocached.grpc.pb.h"
#include "src/proto/protocached.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using protocached::CachedValue;
using protocached::GetRequest;
using protocached::SetRequest;
using protocached::GetResponse;
using protocached::SetResponse;
using protocached::Protocached;
using protocached::ResponseResult;

// TODO(gavin): Moved to a separate class
class ProtocachedClient {
 public:
  explicit ProtocachedClient(std::shared_ptr<Channel> channel)
      : stub_(Protocached::NewStub(channel)) {}

  // Implement the APIs
  ResponseResult Get(const std::string &key, CachedValue &cached_value) {
    // Get the cached value based on key
    GetRequest request;
    request.set_key(key);

    GetResponse response;
    ClientContext context;

    // Actually calling the stub
    std::cout << "Sending request..." << std::endl;
    Status status = stub_->Get(&context, request, &response);

    // Passing the value back
    cached_value.set_value(response.value().value());
    return getResultFromStatus(status);
  }

  // ResponseResult Set(const ::std::string &key, const ::std::string &value) {
  ResponseResult Set(
    const ::std::string &key,
    const CachedValue &cached_value
  ) {
    SetRequest request;
    request.set_key(key);
    request.mutable_value() -> CopyFrom(cached_value);
    SetResponse response;
    ClientContext context;

    Status status = stub_->Set(&context, request, &response);
    return getResultFromStatus(status);
  }

 private:
  std::unique_ptr<Protocached::Stub> stub_;

  ResponseResult getResultFromStatus(const Status &status) {
    ResponseResult result;
    if (status.ok()) {
      result.set_result_status(ResponseResult::SUCCESS);
    } else {
      result.set_result_status(ResponseResult::ERROR);
      result.set_error_message(status.error_code() + ": " +
                               status.error_message());
    }
    return result;
  }
};

int main() {
  std::cout << "Starting up Protocached client..." << std::endl;

  ProtocachedClient client(
      grpc::CreateChannel("0.0.0.0:18081", grpc::InsecureChannelCredentials()));

  while (true) {
    std::string input;
    ::std::cout << "Select from options:" << ::std::endl;
    ::std::cout << "1: Get" << ::std::endl;
    ::std::cout << "2: Set" << ::std::endl;
    ::std::cout << "3: Exit" << ::std::endl;
    ::std::cout << "Please enter 1, 2, or 3" << ::std::endl;
    ::std::cin >> input;

    if (input == "1") {
      ::std::cout << "Please enter a key: ";
      ::std::cin >> input;
      CachedValue cached_value;
      ResponseResult res = client.Get(input, cached_value);

      if (res.result_status() == ResponseResult::SUCCESS) {
        std::cout << cached_value.value() << std::endl;
      } else {
        std::cout << res.error_message() << std::endl;
      }
    } else if (input == "2") {
      ::std::cout << "Please enter a key: ";
      ::std::cin >> input;
      ::std::string key = input;
      ::std::cout << ::std::endl;
      ::std::cout << "Please enter a value: ";
      ::std::cin >> input;
      ::std::string value = input;
      ::std::cout << ::std::endl;
      CachedValue cached_value;
      cached_value.set_value(value);
      ResponseResult response_result = client.Set(key, cached_value);
      if (response_result.result_status() == ResponseResult::SUCCESS) {
        ::std::cout << "Set successful!" << ::std::endl;
      } else {
        ::std::cout << "Set failed!" << ::std::endl;
      }
    } else if (input == "3") {
      ::std::cout << "Bye!" << ::std::endl;
      return 0;
    } else {
      ::std::cout << "Invalid option entered, please try again!" << ::std::endl;
    }
  }

  return 0;
}
