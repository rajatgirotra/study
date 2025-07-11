Queues
======
Queues in AMPS help solve some common messaging problems:
1. Ensuring that a message is processed once.
2. Distributing tasks across workers in a fair manner.
3. Ensuring that a message that is delivered is definitely processed.
4. Ensuring that when a worker fails to process a message, that message is re-delivered.

Queues are intended to guarantee delivery of each message to a single consumer that processes the messages. Use queues when the problem you are solving requires a message to be processed once. When you need to distribute messages to a large number of consumers, use the AMPS pub/sub delivery model

Actually, queues in AMPS rely on the transaction log. If you look at the client API's, there is little difference between subscribing to a queue and subscribing to a sub/pub topic. Both delivery models use the subscribe command, and both delivery models can provide a filter to specify messages of interest. Both types of topics provide the same message objects in the AMPS Client interfaces. The difference is that once a message is received from a queue, the application must let AMPS know when the message is successfully processed via an ACKNOWLEDGEMENT. the acknowledgement for a message is also stored in the transaction log. Acknowledgement also helps AMPS to understand that a message is processed and is now good to be removed from the queue.

the AMPS server maintains an in-memory list of all the messages currently available for delivery in a given queue and a list of all the messages awaiting acknowledgment from subscribers. The messages themselves are stored in the transaction log for the instance. When a message has been successfully processed, the acknowledgment for that message is also stored in the transaction log. There is no separate storage required for a queue, since messages are recorded in the transaction log. Given that the transaction log contains a full record of messages and acknowledgments, AMPS queues are persistent across server restarts, and can be replicated to other instances. A QUEUE IS JUST A DELIVERY STATE IN AMPS.

You can think of a queue as holding references to messages in the transaction log. We can have a variety of ways to consume messages using queues:
1. A queue can hold messages from multiple topics
2. A single message can be present on multiple queues.
3. message from the same topic can be split to different queues based on content filtering.

Queue subscribers can specify a max_backlog option to declare the consumer capacity to process messages. This helps AMPS server to balance delivery of messages across consumers in the most efficient manner.
