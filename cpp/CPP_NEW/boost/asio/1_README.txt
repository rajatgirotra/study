With asio, you will need an asio I/O Context. This context object represents your interface/link to the operating system's I/O services. Examples of I/O contexts are:

boost::asio::io_context;
boost::asio::thread_pool;
boost::asio::system_context;

to perform I/O, we will need an I/O object also. Examples:

boost::asio::ip::tcp::socket socket(io_context);

synchronous operations will wither throw an exception of type boost::system::system_error or return an error code of type boost::system::error_code.

asynchronous operations will need to register a handler that will be called by asio (the thread in which the handler is called is provided by the user only by calling run() method on the io_context object). Note that the handler signature can be different depending on the async operation you are trying to perform.

=======================================================================================================================================
async operations are the basic building blocks as asio. Async Op is started by an initiating function. and the callback handlers are called completion handlers. If an initating function requires temporary resources like memory, file descriptor, thread etc.. these resources must be released before calling the corresponding completion handler.
this way we can avoid peak resource usage when a completion handler again calls an initiating function forming a loop. Example:

socket.async_read(args.., process_buffer);

void process_buffer() {
   // read buffer and process it. when done, read more.
   socket.async_read(args... process_buffer); // becomes a continuous loop.
}

So basically think about Async Op as a composition of an initiating function and a corresponding completion handler. 
Now there is another notional entity called Async agent. Think of an async agent as some kind of entity containing one or more Async Operations. Every Async Operation must be run as part of some Async Agent. Multiple Async Agents may peform work concurrently. So an Async Agent are to Async Operations what a thread is to sequential operations. Inside the Async agent, the Async Op's run sequentially. i.e.

Initiating Function called
Completion Handler called
Initiating function called
Completion Handler called
Initiating function called
Completion Handler called...

But why do we have this composition of Asyn Op's inside an Async Agent. That's because an Async Agent has associated characteristics that specifies how an Async Op should behave when it is part of that Async Agent. What are these characteristics?

1) Allocator --> how the Async Op's should obtain and free memory resources.
2) A cancellation slot --> How the Async Op's support cancellation
3) An executor --> How the Completion handlers will be queued and run.

Now each of these characteristics has an associated trait. These traits classes should return the type and the object of that characteristic. Example, we have the following traits

associated_allocator, associated_executor, associated_cancellation_slot

template <typename T, typename Allocator = std::allocator<void>>
struct associated_allocator {
};

Given an associator trait names associator_R, having
   a source value s of type S, mostly the completion handler and its type (that is the template parameter T above)
   a candidate value c of type C that meets all the type requirements of R (example R = allocator, or exceutor, or cancellation_slot), C = std::allocator<void> for example
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
    static type get(const T& t, const Allocator& c) noexcept { t.get_allocator(); }
};

Also convenience wrappers assocaited_R_t<T, C> and get_associated_R(t, c) are also available.
=======================================================================================================================================

Child Agents:
Async Agents may also compose Child Async Agents within them. Also the parent agent may propogate the aoosciated characteristics to the child agents. From the point of view of parent, when the final completion handler in the child executes, the parent agent is resumed.
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
You already have seen that initiating functions accept a Completion handler. This completion handler is called a Completion Token. But that is not the only Completion Token that you can pass. There are others. Passing a Completion handler makes the initiating function trigger the asyn operation right away.

use_future Completion Token
auto futureObject = socket.async_read_some(buffer, use_future) --> This makes the operation behave like a promise and future pair. The initiating function doesnt launch the asyn operation right away. it waits till someone calls get() or wait() on the future object.
Example: size_t n = futureObject.get();

Similarly you have use_awaitable completion token in which the initiating function behaves like it is an awaitable based co-routine. You will need to read about co-routines in C++ to understand this fully. But in a nutshell, the async op is not immediately called. rather will wait till the operation is co_await-ed.
awaitable<void> foo() {
    size_t n = co_await socket.async_read_some(buffer, use_awaitable);
    ...
}

yield_context Completion token
socket.async_read_some(buffer, yield); // will cause the initating buffer to start the async op and also blocks the co-routine till the operation is complete.
=======================================================================================================================================
