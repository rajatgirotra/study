## Important classes, enums, variables, interfaces in gRPC. For the following helloworld.proto,

```protobuf
syntax = "proto3";

package helloworld;

service Greeter {
  rpc SayHello(HelloRequest) returns (HelloReply);
}

message HelloRequest {
  string name = 1;
}

message HelloReply {
  string message = 1;
}
```
the following important pieces of code are generated.
### namespace and class

```c++
typedef enum {
  /** channel is idle */
  GRPC_CHANNEL_IDLE,
  /** channel is connecting */
  GRPC_CHANNEL_CONNECTING,
  /** channel is ready for work */
  GRPC_CHANNEL_READY,
  /** channel has seen a failure but expects to recover */
  GRPC_CHANNEL_TRANSIENT_FAILURE,
  /** channel has seen a failure that it cannot recover from */
  GRPC_CHANNEL_SHUTDOWN
} grpc_connectivity_state;

class ChannelInterface {...};

class Channel : public ChannelInterface{
public:
   //Get the current channel state. If the channel is in IDLE and try_to_connect is set to true, try to connect.
   grpc_connectivity_state GetState(bool try_to_connect) override;
};

class StubOptions {...};

class ::grpc::Service {...};
class ::grpc::ServerContext {...};
class ::grpc::ClientContext {...};
class ::grpc::Status { 
private:
  StatusCode code_;
  std::string error_message_;
  std::string binary_error_details_;
  
  public:
  bool ok() const { return code_ == StatusCode::OK; }
  StatusCode error_code() const { return code_; }
  std::string error_message() const { return error_message_; }
  /// Return the (binary) error details.
  // Usually it contains a serialized google.rpc.Status proto.
  std::string error_details() const { return binary_error_details_; }
};
enum ::grpc::StatusCode {OK, CANCELLED, UNKNOWN, INVALID_ARGUMENT,...};

std::shared_ptr<Channel> CreateChannel(
    const grpc::string& target, // endpoint URI like localhost:9999
    const std::shared_ptr<ChannelCredentials>& creds); // Credentials to use for the created channel

std::shared_ptr<Channel> CreateCustomChannel(
    const grpc::string& target,
    const std::shared_ptr<ChannelCredentials>& creds,
    const ChannelArguments& args);

namespace helloworld { 
   class Greeter {
   public:
     class StubInterface {...}; // an abstract base class
     class Stub : public StubInterface{...};

   static constexpr char const* service_full_name() {
      return "helloworld.Greeter";
   }
   
   // create a new instance of Stub class.
   static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
   
   // so basically Greeter::Service derives from ::grpc::Service.
   // This class will be used on the server side.
   class Service : public ::grpc::Service {
      virtual ::grpc::Status SayHello(::grpc::ServerContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response);
   };
};
}
```