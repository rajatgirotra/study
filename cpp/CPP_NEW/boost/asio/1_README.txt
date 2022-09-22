With asio, you will need an asio I/O Context. This context object represents your interface/link to the operating system's I/O services. Examples of I/O contexts are:

boost::asio::io_context;
boost::asio::thread_pool;
boost::asio::system_context;

to perform I/O, we will need an I/O object also. Examples:

boost::asio::ip::tcp::socket socket(io_context);

synchronous operations will either throw an exception of type boost::system::system_error or return an error code of type boost::system::error_code.

asynchronous operations will need to register a handler that will be called by asio  (the thread in which the handler is called is provided by the user only by calling run() method on the io_context object). Note that the handler signature can be different depending on the async operation you are trying to perform.

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
You already have seen that initiating functions accept a Completion handler. This completion handler is called a Completion Token. But that is not the only Completion Token that you can pass. There are others. Passing a Completion handler makes the initiating function trigger the async operation right away.
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
1) At initiating step but customizing the return type of the initiating function. Also, the CompletionToken decides if the async operation will immediately be called
   or be deferred;
2) At the completion step by providing a ConcreteToken i.e. a Completion Handler.
But how?? this is done using async_result<> class. How exactly?

For this the async initiating functions need to first define the Completion Handler Signatures, which describe the arguments that will be passed to its Completion Handler.
If you look at the api of example: async_read, async_resolve, they all define Completion Handler signature (there can be more than one signatures for an initiating function.

Then, the operation’s initiating function takes the completion signature (as documented in the API), completion token (use_future, use_awaitable, deferred etc), and its internal
implementation and passes them to the async_result trait. The async_result trait is a customisation point that
combines these to first produce a concrete completion handler, and then launch the async operation.

The async_result<> traits class is used for determining:
a) the concrete completion handler type to be called at the end of the asynchronous operation;
b) the initiating function return type; and
c) how the return value of the initiating function is obtained.
The trait allows the handler and return types to be determined at the point where the specific completion handler signature is known.
This template may be specialised for user-defined completion token types. The primary template assumes that the CompletionToken template parameter is the completion handler.
Lets see the class definition. It is very trivial

template <typename CompletionToken, typename Signature>
class async_result {
   public:
   using completion_handler_type = CompletionToken;  // a) above
   using return_type = void; // b) above
   explicit async_result(const completion_handler_type& h) {
       (void)h; // basically a no-op
   }

   return_type get() {} // c) above
}
}
============================================================================================================================================
