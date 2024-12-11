Boost asio was redesigned to have a new API which we also call as Networking TS, which is a technical specification for introducing Boost.Asio in the standard C++ library.
So Networking TS Boost.Asio is the same API.

With asio, you will need an asio I/O Context. This context object represents your interface/link to the operating system's I/O services. Examples of I/O contexts are:

boost::asio::io_context;
boost::asio::thread_pool;
boost::asio::system_context;

to perform I/O, we will need an I/O object also. Examples:

boost::asio::ip::tcp::socket socket(io_context);

synchronous operations will either throw an exception of type boost::system::system_error or return an error code of type boost::system::error_code.

asynchronous operations are based on the pro-actor design pattern, which means they have an initiating function which starts an async operation and then promptly returns.
The async operation proceeds in the background. Initiating function take in a completion handler, a callable which is invoked when the async operation completes. The parameters
of the completion handler will transmit the result of the async operation.

Example: Lets say you want to implement a TCP heartbeat. you class could look like this:

struct heartbeat {
  std::net::system_timer& m_timer;
  std::next::ip::tcp::socket& m_socket;
  const std::byte* m_buffer;
  std::size_t m_size;

  void initiate(); // initiating function
  void operator() (std::error_code ec, std::size_t bytesWritten); // completion handler
};

void heartbeat::initiate() {
 // the most important function.
  async_wait_then_write(m_timer, m_socket, std::chrono::seconds(5), std::net::buffer(m_buffer, m_size), std::move(*this));
}

void heartbeat::operator() (std::error_code ec, std::size_t bytesWritten) {
  if(ec) throw std::system_error(ec); // if error, throw exception
  initiate(); // calls the initiating function again to start the async operation again.
}

const std::byte write_buffer[/* ... */]
std::net::io_context io_ctx;
std::net::ip::tcp::socket socket(io_ctx);
std::net::system_timer timer(io_ctx);
heartbeat{timer, socket, write_buffer, sizeof(write_buffer)}.initiate();

the "async_wait_then_write" function is a "composed" asynchronous operation. which means it is made up of one or more other async operations. This is the fundamental building block of high quality networking TS code. wrapping async operations inside other async operations until you have written all your code.

But which two operations are composed here.? the first ofcourse is the act of waiting on the timer. and the second is the writing to a socket. Socket writing has to be done in a loop honestly, because a socket function may write only some bytes and return success without actually writing all the bytes. So we need to write in a loop. i.e. multiple async operations.
Thankfully, networking TS wraps all this neatly for us in a "std::net::async_write" function; which we will leverage here.

template <class AsyncWriteStream, class ConstBufferSequence, class CompletionToken>
auto async_write(AsyncWriteStream& stream, const ConstBufferSequence& buffers, CompletionToken&& token);

Let's now write our own async_wait_then_write function:

template <typename ConstBufferSequence, typename Handler>
void async_wait_then_write(std::net::system_timer& timer, std::net::ip::tcp::socket& socket, std::chrono::seconds duration, ConstBufferSequence bufs, Handler&& handler) {
  timer.expires_after(duration);

  auto f = [&socket, bufs = std::move(bufs), h = std::forward<Handler>(handler)] (std::error_code ec) mutable {
   if(ec) h(ec, 0);
   else std::net::async_write(socket, std::move(bufs), std::move(h));
   };
   timer.async_wait(std::move(f));
}

// what is "f" above? It is an intermediate CompletionHandler.

Now we said before that the async operation proceeds in the background. Where is that background? The answer is that the async operation is run by an "executor".
An "executor" is an opaque handler to an "execution context". The execution context will use execution resources such as a cpu core to run the async operation. the std::net::io_context provides a nested "executor_type" typedef which is an "executor". You can also define your own executor classes also. The networking TS defines three operations on an executor which determine how the CompletionHandler is called.
1. dispatch() - dispatch just means run a function object (callable) in an execution context. If you call the dispatch function itself in an execution context, the callable will be invoked immediately below you on the call stack.
2. defer() - extends dispatch by requesting that the call not block on the completion of the CompletionHandler. The CompletionHandler will be called at some point in the future.
3. post() - extends defer by making the request a requirement.

Now networking TS creates a number of abstractions to model various things; and requires those abstraction to implement some interfaces. Examples are:
1) AsyncWriteStream - a type that models the concept of a stream that can be written to asynchronously, like a socket.
2) ConstBufferSequence - a type that models the concept of a sequence of buffers that can be read from or written to, like a std::vector or std::array.
3) CompletionToken - a type that models the concept of a token that can be used to customize the behavior of an asynchronous operation, like a completion handler or a future.
4) Executor - a type that models the concept of an executor, like an io_context.
5) WaitableTimer - a type that models the concept of a timer that can be waited on, like a system_timer.

=======================================================================================================================================
async operations are the basic building blocks as asio. Async Op is started by an initiating function. and the callback handlers are called completion handlers. If an initiating function requires temporary resources like memory, file descriptor, thread etc. these resources must be released before calling the corresponding completion handler.
this way we can avoid peak resource usage when a completion handler again calls an initiating function forming a loop. Example:

socket.async_read(args.., process_buffer);

void process_buffer() {
   // read buffer and process it. when done, read more.
   socket.async_read(args... process_buffer); // becomes a continuous loop.
}

So basically think about Async Op as a composition of an initiating function and a corresponding completion handler. 
Now there is another notional entity called Async agent. Think of an async agent as some kind of entity containing one or more Async Operations. Every Async Operation must be run as part of some Async Agent. Multiple Async Agents may perform work concurrently. So an Async Agent are to Async Operations what a thread is to sequential operations. Inside the Async agent, the Async Op's run sequentially. i.e.

Initiating Function called
Completion Handler called
Initiating function called
Completion Handler called
Initiating function called
Completion Handler called...

But why do we have this composition of Async Op's inside an Async Agent. That's because an Async Agent has associated characteristics that specifies how an Async Op should behave when it is part of that Async Agent. What are these characteristics?

1) Allocator --> how the Async Op's should obtain and free memory resources.
2) A cancellation slot --> How the Async Op's support cancellation
3) An executor --> How the Completion handlers will be queued and run.

Basically, you have a heartbeat object above. Now what if you have a "process" object also which also has an "initiate()" and an "operator()()" CompletionHandler which does a normal socket read-process-read loop. If both these CompletionHandlers run on the same executor which has a single thread, everything is good.
But what if the heartbeat object runs on a different executor than the process object. They both will access the same socket in parallel, heartbeat object for writing and process object for reading and that will be a problem. So we need to run CompletionHandlers sequentially. This is where the Async Agent comes in. The Async Agent will make sure that the CompletionHandlers run sequentially.

Now each of these characteristics has an associated trait. These traits classes should return the type and the object of that characteristic. Example, we have the following traits

associated_allocator, associated_executor, associated_cancellation_slot

template <typename T, typename Allocator = std::allocator<void>>
struct associated_allocator {
};

Given an associator trait names associator_R, having
   a source value s of type S, mostly the completion handler and its type (that is the template parameter T above)
   a candidate value c of type C that meets all the type requirements of R (example R = allocator, or executor, or cancellation_slot), C = std::allocator<void> for example
the traits class should provide:

1) associated_R<S, C>::type // to get the type
2) associated_R<S, C>::get(s, c) // to get the object. This object should meet all the requirements of R.

The default associated_allocator, associated_cancellation_slot, associated_executor traits classes assume that for template parameter T, you have defined T::R_type and t.get_R() i.e.
T::allocator_type and t.get_allocator()
T::executor_type and t.get_executor()
T::cancellation_slot_type and t.get_cancellation_slot(), so a sample associator trait is implemented like this

template <typename T, typename Allocator = std::allocator<void>>
struct associated_allocator {
    using type = T::allocator_type;
    static type get(const T& t, const Allocator& c) noexcept { t.get_allocator(); if t.get_allocator() is defined else return c; // i.e. the fallback allocator }
};

Exactly same traits classes are available for executor and cancellation_slot also

Also, convenience wrappers assocaited_R_t<T, C> and get_associated_R(t, c) are also available.

So these associated traits are a way to customize your CompletionHandlers.

NOW EVERY INTERMEDIATE COMPLETION HANDLER NEEDS TO HONOUR THE ASSOCIATION OF THE FINAL COMPLETION HANDLER OF YOUR COMPOSED SET OF ASYNC OPERATIONS.

If you see carefully the asio::io_context has a typedef "executor_type" and also defines a "get_executor()" function. So the type asio::io_context can also be used
as the first parameter type S in associated_executor_t<io_context, C>
=======================================================================================================================================

Child Agents:
Async Agents may also compose Child Async Agents within them. Also the parent agent may propagate the associated characteristics to the child agents. From the point of view of parent, when the final completion handler in the child executes, the parent agent is resumed.
Trivial really..
=======================================================================================================================================
Every Async agent has an associated Executor. Executor determines how the Completion handlers are queued and run. There can be many possible strategies
1) A group of related agents can share some data structure and make sure their Completion handlers never run concurrently.
2) A group of related agents can spawn/use a thread pool to run their completion handlers.
3) Run some code before and after the completion handler is run such as logging, user authorization etc
4) Running the completion handlers by pinning them to a CPU etc etc.
=======================================================================================================================================
Similarly the Allocator associated with the Async agent is used to manage memory allocation.
=======================================================================================================================================
And the Cancellation_Slot associated with the Async agent is used to cancel async operations. There can only be one cancellation slot per Async Agent.
=======================================================================================================================================
Completion Tokens
You already have seen that initiating functions accept a Completion handler. This completion handler is a type of Completion Token. But that is not the only Completion Token that you can pass. There are others. Passing a Completion handler makes the initiating function trigger the async operation right away.
socket.async_read_some(buffer, [](error_code e, size_t) {  // ... });

use_future Completion Token
auto futureObject = socket.async_read_some(buffer, use_future) --> This makes the operation behave like a promise and future pair. The initiating function doesn't launch the async operation right away. it waits till someone calls get() or wait() on the future object.
Example: size_t n = futureObject.get();

Similarly, you have use_awaitable completion token in which the initiating function behaves like it is an awaitable based co-routine. You will need to read about co-routines in C++ to understand this fully. But in a nutshell, the async op is not immediately called. rather will wait till the operation is co_await-ed.
awaitable<void> foo() {
    size_t n = co_await socket.async_read_some(buffer, use_awaitable);
    ...
}

yield_context Completion token
socket.async_read_some(buffer, yield); // will cause the initiating buffer to start the async op and also blocks the co-routine till the operation is complete.

You can even have user defined Completion Tokens but that's a bit complex.
Did you notice something?? See again the return types of the initiating function async_read_some?? The return types are actually changing based on the CompletionToken. How??

Basically CompletionTokens provide a customization point at both the initiating step and the completion step.
1) At initiating step by customizing the return type of the initiating function.
2) At the completion step, the CompletionToken decides if the async operation will immediately be called or be deferred; and also how to retrieve the result of the async operation.
But how?? this is done using async_result<> class. How exactly?

For this the async initiating functions need to first define the Completion Handler Signatures, which describe the arguments that will be passed to its Completion Handler.
If you look at the api of example: async_read, async_resolve, they all define Completion Handler signature (there can be more than one signature for an initiating function.

Now look at the API of a sample async_read_some() async operation. It takes a concrete Completion Token as an argument (like use_future, use_awaitable, deferred etc).

Inside the async_read_some() function, the async_result<> class is used to convert this concrete completion token into a concrete completion handler based on the completion handler signature. the async_result<> must also define the return type of the initiating function and type of the concrete completion handler. The async_result<> class is also responsible for launching the async operation. So the async_result<> class has a lot of responsibility

1) define typedef "return_type" for return type of the initiating function
2) define typedef "completion_handler_type" for type of the concrete completion handler.
3) manufacture the concrete completion handler. this will be called when the async operation completes.
4) launch the async operation. this happens inside the async_result<>::initiate() function.

template <typename CompletionToken, typename Signature>
class async_result {
   public:
   using completion_handler_type = CompletionToken;
   using return_type = void;
   explicit async_result(const completion_handler_type& h) {
       (void)h; // basically a no-op
   }

   return_type get() {} // the value we are supposed to run from the initiating function.
};

This unspecialized version above is only suitable for CompletionTokens that are CompletionHandlers.
============================================================================================================================================

Buffers

boost asio provides mutable_buffer and constant_buffer classes which provide an abstraction over an array of bytes. think of them as:
mutable_buffer = std::pair<void*, size_t> // size_t in bytes
const_buffer = std::pair<const void*, size_t> // size_t in bytes

Now think you want to write a header and payload to a socket. the header is nothing but the size of the payload to keep it simple. you might use to write calls.
template <typename SyncWriteStream>
void send_message(SyncWriteStream& stream, std::net::const_buffer payload) {
   net::write(stream, make_header(payload));
   net::write(stream, payload);
}
But this is not good. I/O calls are expensive. So a better way would be to use just one call. Boost asio provides a MutableBufferSequence and a ConstBufferSequence concept. These are nothing but a BIDIRECTIONAL RANGE OF CONTIGUOUS MEMORY BUFFERS. they work on reference semantics (so no ownership). Length is fixed and cnnot be resized. Lightweight and copyable.

template <typename SyncWriteStream, typename ConstBufferSequence>
void send_message(SyncWriteStream& stream, ConstBufferSequence payload) {
   net::write(stream, payload);
}

These buffer sequences allows you to support scatter-gather operations. which means that when reading from an external device, boost asio can write the data to multiple mutable_buffers(i.e. scatter read). Similarly, when writing to an external device, boost asio can write data from multiple const_buffers (i.e. gather write). To achieve this boost asio provides two concepts called MutableBufferSequence and ConstBufferSequence. Any class which conform to these concepts can be used for scatter-gather operations. example: std::vector, std::list, std::array, boost::array are container classes which already fulfill these requirements.

You normally use read(), write() functions with a char buffer and the size in bytes to read or write. But boost::asio provides you a helper class called boost::asio::streambuf (derives from std::streambuf). This asio::streambuf class can internally hold multiple objects of some character array type (think that internally data is stored in a MutableBufferSequence or ConstBufferSequence). So you can use the read(), write() functions with asio::streambuf. The streambuf class provides a separate input and output sequence. Example:

Buffer sequences are nice, but sometimes we need something different, example:

auto matching_bytes = net::read_until(socket, b, "\r\n\r\n"); // \r\n\r\n is HTTP request header delimiter
What is "b" here?

"b" is a DynamicBuffer (resizable buffer, unlike ConstBufferSequence and MutableBufferSequence. It is a concept again so many implementations exist). It has a read area and a write area.
The way we use it is using the following API's

DynamicBuffer a;
1) prepare() - to prepare the write area. This will return a MutableBufferSequence such that the sum of the sizes of all its buffers sum up to n. This API must be called before calling commit() API. prepare(128) will ensure that the write area can accommodate 128 bytes.
   auto x = a.prepare(128); // x is a MutableBufferSequence
2) auto bytes_transferred = socket.read_some(x); // read some bytes into the write area. let's say 60 bytes are read from socket and written to the write area.
3) a.commit(bytes_transferred); // Move bytes from the write area to the read area.
4) auto bytes_used = process(a.data()); // let's say 40 bytes are processed. data() returns a class satisfying ConstBufferSequence.
5) a.consume(bytes_used); // consume the processed bytes from the read area.

An example of using DynamicBuffer is as follows:
boost::asio::streambuf sb; // this is a DynamicBuffer
size_t n = boost::asio::read_until(socket, sb, '\n');
boost::asio::streambuf::const_buffers_type bufs = sb.data(); // data() returns a class satisfying ConstBufferSequence representing all buffers in the input sequence.
// you can even iterate the "bufs" container using boost::asio::buffers_iterator<> as if it is a continuous sequence of characters.
string line(boost::asio::buffers_begin(bufs), boost::asio::buffers_end(bufs) + n); // note that you are not iterating over individual buffers in ConstBufferSequence. The buffers_iterator<> class provides an abstraction over the underlying bufs as a single contiguous sequence of bytes.

API's to use for reading/writing exact number of bytes: read(), async_read(), write(), async_write()
API's to use for reading/writing some number of bytes: read_some(), async_read_some(), write_some(), async_write_some()
API's for line based protocols: async_read_until() - Line based protocol are protocols where messages are delimited by character sequence "\r\n", or some other delimiter.

Buffer Literals: boost::asio::buffer_literals provides a way to create const_buffer objects from string, binary integer and hexadecimal integer literals. Example:
boost::asio::async_write(my_socket, "hello"_buf, my_handler);

auto b1 = 0xABCDEF_buf; // b1 is a const_buffer object containing the binary representation of the hexadecimal integer 0xABCDEF
auto b2 = 0b101010101101_buf; // b2 is a const_buffer object containing the binary representation of the binary integer 0b101010101101
============================================================================================================================================
