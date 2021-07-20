Websockets were introduced in HTML 5.
They provide bi-directional (full duplex) communication between client and server over a TCP connection.
The most common use of websockets is sending chat messages in browser. Other applications are creating realtime data/price feed in browser. All real time applications like multiplayer browser games, collaborative code editing, live test for sports/news websites, online drawing canvas etc.

To create a websocket connection. the client sends a special HTTP request something like below.

GET /chat HTTP/1.1
Host: server.example.com
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Key: <someHashKey>
Origin: http://example.com
Sec-WebSocket-Protocol: chat, superchat
Sec-WebSocket-Version: 13

The server response is like:

HTTP/1.1 101 Switching Protocols
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Accept: <someHash>
Sec-WebSocket-Protocol: chat, superchat

The WebSocket Accept Key
------------------------
the web socket accept key returned by the server is formed from the concatenation of Sec-WebSocket-Key from the request concatenated to the Globally Unique Identifier (GUID, just a special string), then encoded to an SHA-1 hash then base64 encoded to the get the result.
The concatenation of the client's key in the servers response make the client feel safe that the server's response pertains directly to the client's request.

Communication Protocol
----------------------

Once the handshake above is complete, the websocket is open. Now the exchange of data can start. But you can't just send across a giant video file, or start streaming data. It doesnt work that way. The websocket protocol is based on the TCP protocol and breaks data down into frames. Basically the frame has a structure (just like a TCP segment or an IP segment has a structure, ie header followed by payload). You can google the websocket frame stucture, but let's just see some of the important information in the frame.

FIN --> the first bit will be marked 1 or 0. A 1 indicated that this is the final framgment in a message.
RSV1, RSV2, RSV3 --> 1 bit each. These bits are typically set to zero but may be required if there are extensions places on the socket protocol.
Opcode (4 bit)--> modifiers to the message which may indicate a connection close or indicate the type of data being transmitted (like binary, utf-8 etc).
Mask (1 bit) --> This bit is used to indicate whether the data is masked. normally frames sent from server may or may not have this set. But client side will always set it and also include a 32 bit masking key (a random key for each frame)

finally you have Payload length and Payload Data. I think max payload data in 64KB in a single frame.

Closing Connection
------------------
one side will send a frame with Opcode indicating this is a closing frame. So the other end should reciprocoate the closing frame as soon as possible and practical.

