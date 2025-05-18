Important points when using gRPC
=================================
1. Because RPC calls are made over a Channel, and there can be multiple channels, always assume that different RPC calls can be made at the same time.
This means that RPC implementations on the server side should use thread safe data-structures or use explicitly locking, atomics or any other thread-safe
mechanism.

EnableDefaultHealthCheckService
===============================
In gRPC, EnableDefaultHealthCheckService(true) is a server-side function that enables the built-in gRPC Health Checking Service.

Purpose
--------
This health check service allows clients (such as load balancers, Kubernetes, or monitoring tools) to query the server's health status through the standard gRPC Health Checking Protocol, which is defined in the grpc.health.v1.Health service. What it does? Calling EnableDefaultHealthCheckService():
* Registers the grpc.health.v1.Health service on the server.
* Creates a default HealthServiceImpl instance that keeps track of service health statuses.
* Allows tools or services to send Check or Watch requests to query the server's health.

The true argument allows the default health check service to be used with reflection (so tools like grpcurl can discover it

Behavior
--------
Once enabled:
* Clients can call Check with a service name (or empty string for whole server).
* Server can dynamically update the health status via the HealthCheckServiceInterface.
Example of how to update the status (if using a custom health service):

health_service->SetServingStatus("my.service.name", grpc::health::v1::HealthCheckResponse::SERVING);

When to Use:
-----------
Use EnableDefaultHealthCheckService() if:
You want Kubernetes to perform gRPC-based health checks.
You want to integrate with Envoy, gRPCurl, or monitoring tools.
You don't want to write a custom health-checking implementation.

InitProtoReflectionServerBuilderPlugin
======================================
Just like the health check service, gRPC also has a reflection service which is enabled by this call. This service allows clients to discover services,
methods and message types at runtime - this is used especially useful when they dont have access to the original .proto files. Calling this function
registers the gRPC server reflection service with the ::gRPC::ServerBuilder. Tools like gRPCurl, Postman etc, can introspect the gRPC server and do things like:
* List all services and methods.
* Get message schemas.
* Make dynamic RPC calls.
without needing .proto files locally