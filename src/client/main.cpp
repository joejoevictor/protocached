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
using protocached::GetResponse;
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

 private:
  std::unique_ptr<Protocached::Stub> stub_;
};

int main() {
  std::cout << "Starting up Protocached client..." << std::endl;

  ProtocachedClient client(
      grpc::CreateChannel("0.0.0.0:18081", grpc::InsecureChannelCredentials()));

  while (true) {
    std::string input;

    std::cout << "Please enter a key: ";
    std::cin >> input;
    CachedValue cached_value;
    ResponseResult res = client.Get(input, cached_value);

    if (res.result_status() == ResponseResult::SUCCESS) {
      std::cout << cached_value.value() << std::endl;
    } else {
      std::cout << res.error_message() << std::endl;
    }
  }

  return 0;
}
