AMPS Publishing and Subscribing
===============================
you already know we can publish to topics and subscribe to topics. Topic names can be ad-hoc if the messages are not persisted. You dont need the topics to be pre-configured in that case. However, for persisted messages, you need the topics to be pre configured in the config file. You can further set up subscription based on content of the message. Example: a topic name could be "ORDERS" representing Order messages. But a subscriber could further apply filtering on "ticker=IBM", where "ticker" is some field on the message.

Also, each topic is associated with a message type. example: Json, XML, protobuf etc. Combination of "Topic name and message type" should be unique. Example: there could be two topics with the same name "ORDERS", but different message types "json" and "xml". When publishing or subscribing to topics, you don't need to tell the AMPS api's about the message type. Why? because AMPS will know about the message type from the connection itself. Each connection to AMPS has an associated message type (each port provides a specific message type).

What we will do next is:
1. download the AMPS server.
2. generate a config to start the server.
   /bin/ampServer --sample-config > sample-config.xml
3. start the server with the generated config
   /bin/ampServer sample-config.xml
4. validate server is started.
   /bin/spark ping -server localhost:9007 -type json
5. start a subscriber first (so that subscription is setup before publisher is started).
   /bin/spark subscribe -server localhost:9007 -type json -topic test
6. publish a simple hello world json message.
   echo '{"message": "Hello World"}' | ./bin/spark publish -server localhost:9007 -type json -topic test

7. repeat the publisher/subscriber commands to setup content filtering.
   /bin/spark subscribe -server localhost:9007 -type json -topic test -filter "/message LIKE '(?i)world'" &
   echo '{"message": "Hello World"}' | ./bin/spark publish -server localhost:9007 -type json -topic test
   echo '{"message": "Goodbye!"}' | ./bin/spark publish -server localhost:9007 -type json -topic test

Remember that by default, AMPS has authentication enabled. the default authentication allowed is any username and empty password. When we use the "spark" utility to setup publisher/subscribers, spark will internally use the logged in user's id as the user and the empty password for authentication.