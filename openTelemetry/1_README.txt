OpenTelemetry is a framework and set to tools for observalibility.
What is observability? Observalibility means knowing the health and state of your infrastructure and applications in real time. How would you know that. Observability is only possible if you instrument your code. Instrumentation means generating telemetry data from your application and infrastructure and export it to some observability backend. Then, viewing that data in some observability frontend.

So the workflow is:
1. code/infrastructure is instrumented and telemetry data is generated.
2. it is then pushed and stored to some observability backend like prometheus or Jaeguer.
2. it is then viewed in some observability frontend like Grafana or Jaeguer or other such software.

OpenTelemetry provides an OpenSource specification/protocol for instrumented and storing telemetry data in a vendor neutral way, so you can plug and play any observability backend or frontend (whether free or commercial).

Telemetry data is:
1. Metric: A metric some aggregation of a numeric data over time. Example: CPU utilization over time, system error response rate, throttle beaches for some API endpoint.

2. Traces: A distributed trace or simply a trace records the paths taken by requests (made by an application or end user) as they propagate through multiple services in a distributed (microservices based) system. Tracing allows you to observe requests as they travel through complex systems. A trace is made up of one or more spans (see below what a span is). The first span represents the root span. Each root span represents a request from start to finish. The span underneath the parent provide a more in-depth context of what occurs during a request.
Traces are extremely helpful in debugging performance issues/bottlenecks in a distributed system. When a trace is made up of several spans, many observability frontends provide a way to visualize traces as waterfall diagrams of their spans.

3. Logs: Logs are messages which are recorded in log files by your application or by the system services. These are generally not tied to any particular user request or transaction. Logs usually lack contextual information, like where they were called from.


You also have SLO's, i.e. Service Level Objectives. These are goals that you must meet in order to claim that your application is working propertly 100%. You communicate reliability and healthy state of your application through such SLO's. For each of these SLO's you may define one or more SLI's i.e. Service Level Indicators. A good SLI measures your service from the perspective of end users. An example can be the speed at which a web page loads.

SPANS
====
A span is a unit of work or operation. Spans track specific operations that a request makes, painting a picture of what happened during the time in which that operation was executed. A span contains a name, time-related data, structured log messages, and other metadata/attributes. Example of attributes could be "http.request.method", "network.protocol.version", "url.path", "url.query", "server.address" etc.

Context Propagation
===================
For distributed tracing to trace a request through multiple services, you need to pass some context information from one service to the other. Without this context, you can't establish a causal relationship between operations across services.
Context is an object that contains information for sending and receving service to correlate one signal with another. When Service A calls Service B, Service A includes a TraceID and SpanID as part of the context. Service B uses these values to create a new span that belongs to the same trace, setting the span from Service A as its parent. This makes it possible to track the full flow of a request across service boundaries.

How is this context propagared? OpenTelemetry provides "Propagation APIs" that do this automatically for you. These API's handle the serialization/deserialization of the context object and provides the relevant information to be propagated from one service to another. The default propagator used in OpenTelemetry is W3C TraceContext specification.

Example: A "Frontend" service provides two endpoint "POST /card/add" and "GET /checkout". Another service "Product Catalog" provides endpoints "GET /product". By using the "traceparent" header as defined in the W3C TraceContext spec, a service can embed the following ID's in the HTTP header.
<version>-<TraceId>-<ParentId>-<TraceFlags>. Lets say "Frontend" service receives a request "POST /cart/add". "Frontend" creates a new TraceID "a0892f3577b34da6a3ce929d0e0e4736" and a new Span 1 with SpanId "f03067aa0ba902b7". It then calls the "GET /product" endpoint in Product Catalogue service by passing the "traceparent" header with value 00-a0892f3577b34da6a3ce929d0e0e4736-f03067aa0ba902b7-01". Product Catalog creates a new Span 2 with SpanId "ec0123456789" and ParentID: f03067aa0ba902b7. That's how we have one TraceID for a request with multiple Span IDs.

Logs
====
You can also inject TraceID and SpanID into log records. This allows to views all logs for a TraceID at one place in the OBservability Frontend.

Similarly, you can pass Context information and also aggregate timings across services in your metrics calculation.

Baggage
=======
OpenTelemetry allows you to stuff user defines KeyValue pairs in the Context object. This user defined KV pairs is called Baggage. To have Baggage, you will need to inject Baggage information in your Context, and extract this Baggage information on the receiving side - using the same Propagation APIs

