State of the World (SOW)
==================
There are many use cases where an application requires the latest and greatest update on a message when the application starts up. AMPS can keep track of the latest version of any message using SOW topics. SOW topics are topics which you need to configure in the <SOW> section of the configuration file.

What configuration is required?
===============================
Before we get to configuration, lets see how AMPS identifies each message uniquely. To identify each message uniquely, we need a unique key. We call it the SOWKey. How is SOWKey generated?
1. Don't provide any configuration for key --> In this case, application will be responsible to provide a unique key for each message.
2. Provide an XPath type configuration for the unique key --> In this case, AMPS will fetch these fields from the message and construct a unique key itself.
3. Provide a custom AMPS module, which contains logic to generate SOW keys for each message.

Persistent vs Transient
=======================
SOW topics could be persistent (i.e. the latest update is also pushed to a file and retrieved later when AMPS is restarted), or transient (i.e. just maintained in memory by AMPS).

Use cases for SOW Topics
========================
An application needs the current state of a record, but does not need to recreate the message flow that created that record:
An order fulfillment system presents a view of all currently pending orders when the application starts up.
An application needs the current state of a record or set of records, even when the topic is high-volume or quickly changing:
A warehouse management application locates the current inventory level for a product.
A taxi dispatch company locates taxis currently within 10 blocks of an event.
An application wants to be able to publish incremental updates to a record:
A customer updates her shipping address. All pending orders for the customer are automatically updated without affecting any other information in the order, and processors working with the orders are notified of the change.
An application wants to receive only the changed fields of a record:
A mobile application displays the status of an order as the order progresses through the stages of validation: the application receives only the identifier for the record and the changed fields.
A management console constantly calculates the real-time value of pending orders. The console uses a view, calculated based on data saved in a topic in the SOW.

What we will do next
====================
We will configure some SOW topics in our config, then we will publish on those Topics. Later we will use the "spark" tool to query and subscribe to messages on that topic and see the behavior.

Configuration
=============
Added this to amps-config file.
 <SOW>
    <Topic>
      <Name>test-sow</Name>  # Topic name
      <MessageType>json</MessageType>  # Topic type
      <FileName>./sow/%n.sow</FileName>  # %n means topic name.
      <Key>/id</Key>  # unique id will the "id" key in the json.
    </Topic>
  </SOW>

Publish
=======
echo '{"id": 1, "note": "Crank it up with a SOW!"}' | ./bin/spark publish -server localhost:9007   -type json -topic test-sow
echo '{"id": 1, "note": "How have you been!"}' | ./bin/spark publish -server localhost:9007   -type json -topic test-sow

Query
=====
./bin/spark sow -server localhost:9007  -type json -topic test-sow

Query & Subscribe
==================
./bin/spark sow_and_subscribe -server localhost:9007  -type json -topic test-sow & # run in background

Publish a few more
==================
echo '{"id": 1, "note": "My name is Rajat. Excited to learn AMPS SOW!"}' | ./bin/spark publish -server localhost:9007   -type json -topic test-sow