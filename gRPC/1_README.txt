gRPC is an open source high performance RPC (Remote Procedure Call) framework. It uses google protocol buffers, both as its IDL language as well as it's underlying message interchange format. It is available in many languages like Java, C++, Python, Go, Kotlin, .NET etc.

The big thing about gRPC is that it is built on top of HTTP/2. HTTP/2 provides many benefits over HTTP1.1 which makes gRPC high performance framework.

1. Multiplexing
==============
HTTP/1.1: Only one request per TCP connection at a time (or limited pipelining). Multiple connections are needed for parallelism.
HTTP/2: Multiple requests/responses can be sent simultaneously over a single connection. No head-of-line blocking at the application layer. Head-of-line (HOL) blocking at the TCP connection level occurs when a packet at the front of the TCP receive buffer (the "head" of the line) is lost or delayed, causing subsequent packets—even if they arrive on time and in order—to be held up and not delivered to the application until the missing packet is retransmitted and received. If packet #3 is lost, and packets #4, #5, etc., arrive, the receiver cannot deliver those later packets to the application until packet #3 is successfully retransmitted.

2. Binary Protocol
==================
HTTP/1.1: Text-based protocol (easy to read but harder to parse efficiently).
HTTP/2: Fully binary protocol (more compact and faster to parse by machines).

3. Header Compression
=====================
HTTP/1.1: Headers are sent in full with every request.
HTTP/2: Uses HPACK compression to reduce header size—more efficient, especially for APIs with repetitive headers.

4. Server Push
==============
HTTP/1.1: Server responds only when the client asks.
HTTP/2: Server can proactively “push” resources to the client (e.g. CSS/JS) before the browser requests them.

5. Prioritization
=================
HTTP/1.1: No built-in prioritization mechanism.
HTTP/2: Allows clients to assign priority to requests for more efficient resource loading.

6. Connection Management
========================
HTTP/1.1: Many TCP connections needed for multiple resources, increasing overhead.
HTTP/2: One long-lived connection per origin reduces latency and connection overhead.

7. TLS Requirement
==================
HTTP/1.1: Can work over plain TCP or TLS (HTTPS).
HTTP/2: Technically supports plain TCP, but most browsers require HTTPS/TLS.

--------------------------------------------------------------------------------------------------------------------------------------

Load balancing in gRPC
=====================

There are 3 options.
1. Client side load balancing

Traditional HTTP load balancers (like round-robin LBs) work at the connection level, so they’re not well-suited for gRPC, where you want request-level balancing. gRPC clients typically reuse a single HTTP/2 connection for multiple requests. gRPC supports client-side load balancing to work around these issues. in client side load balancing, the gRPC client is given a list of backend server addresses. It maintains connections to multiple servers and uses policies (like round robin or least connections) to distribute requests. This is more efficient for HTTP/2 because it avoids head-of-line blocking at the TCP connection level.

Client ----> [Server1, Server2, Server3]
         ↳ round-robin or pick-first strategy

gRPC clients support built-in load balancing policies, such as:
pick_first: Uses the first backend until it fails.
round_robin: Cycles through all available backends.
grpclb: Uses a load balancer server (deprecated in favor of xDS).
xds: Dynamic, supports traffic splitting, retries, etc.

2. gRPC + Envoy (xDS)
xDS is a protocol originally developed for Envoy proxy.
gRPC can use xDS APIs to discover backend instances and load balancing policies dynamically.
This enables centralized control, health checks, and circuit breaking.

Client (gRPC with xDS) → Envoy Control Plane → Backend Servers

3. Proxy-Based Load Balancing (not ideal for gRPC)
Using a traditional L4/L7 load balancer (e.g., NGINX, AWS ALB) in front of gRPC servers.
Downside:
Load is balanced per connection, not per request.
Doesn't leverage HTTP/2 multiplexing effectively.
--------------------------------------------------------------------------------------------------------------------------------------------

Service Mesh
============
gRPC traffic may require to be scaled up which can make things difficult to manage. So there are "Service Mesh or Traffic Control Systems" that can manage
gRPC traffic, enable advanced routing, load balancing, observability and security. Two such systems are "Traffic Director" and "Istio".

What is Traffic Director?
Google Cloud's fully managed traffic control plane for service mesh.
Works with xDS APIs (same ones used by Envoy and gRPC).
Designed for use with gRPC, Envoy, and proxyless gRPC clients.
🔸 Key Features:
Traffic splitting (canary, blue/green)
Global load balancing with health checks
Authentication (mTLS)
Automatic service discovery
Supports proxyless gRPC clients — meaning the gRPC client talks directly to Traffic Director, no need for a sidecar.
🔸 Used With:
Google Cloud
gRPC clients with xDS support
Envoy or proxyless clients

What is Istio?
Open-source service mesh primarily for Kubernetes.
Manages microservices using sidecar proxies (usually Envoy).
Handles routing, retries, failovers, traffic shaping, mTLS, and observability.

[gRPC Client Pod] --|
                    |--> Sidecar Proxy (Envoy) --> Istio Control Plane --> gRPC Server Proxy --> Server
[gRPC Server Pod] --|

--------------------------------------------------------------------------------------------------------------------------------------------

Streaming
=========

gRPC supports streaming natively, and it's one of its most powerful features.
Unlike traditional REST APIs where each request/response is a one-time exchange, gRPC allows streams of messages in both directions, all over a single HTTP/2 connection.

Types of communication patterns in gRPC:
1. Unary (Basic)
Classic request-response
Client sends 1 request, gets 1 response.
"rpc SayHello(HelloRequest) returns (HelloReply);"

2. Server streaming
Client sends 1 request.
Server sends a stream of responses.
"rpc ListItems(ListRequest) returns (stream Item);"

3. Client Streaming
Client sends a stream of requests.
Server replies with 1 final response.
"rpc Upload(stream DataChunk) returns (UploadStatus);"
Use case would include: Uploading large files in chunks or Sensor telemetry collection

4. Bidirectional Streaming
Both client and server send streams of messages concurrently.
True full-duplex communication over HTTP/2.
"rpc Chat(stream ChatMessage) returns (stream ChatMessage);"
Use case would be Chat applications or Trading systems or Real-time collaborative tools

gRPC does a lot internall like:
Framing
Flow control
Ordering
Compression
Stream lifecycle


