Please read
 sync_timer.cpp
 async_timer.cpp,
 async_repeat_timer.cpp,
 async_repeat_timer_handler_function.cpp
 strand_usage.cpp

Let's understand some important class hierarchies
===============================================
Executor and ExecutorContext are two objects that are closely tied together.

ExecutionContext --> A user defined ExecutionContext class must satisfy the following requirements
class MyEC : asio::execution_context { // An ExecutionContext class must derive from asio::execution_context
   using executor_type = SomeType;
   executor_type get_executor(); // i.e. An ExecutorContext will contain an Executor object
   ~MyEC();
};

The asio::execution_context class represents a place where function objects will be executed. Example of one such class asio::io_context. Yes, io_context class derives from execution_context. More details on execution_context will be studied later, as you will hardly be required to write your ExecutionContext.

class asio::io_context : public asio::execution_context {};

How does the asio::execution_context work? --> Internally it holds a map of Services. Service is a user defined class which derives from asio::execution_context::service

class MyService : public asio::execution_context::service {
public:
    using key_type = MyService; // must declare key_type typedef.
    MyService(execution_context& ec); // must declare this. so that a service object knows which execution_context it is part of.
private:
    virtual void shutdown() noexcept override; // must destroy all copies of user defined function objects that are held by the service.
};

So asio::execution_context holds a map of Service objects where is the key_type defined in the Service class. There are free standing helper functions to work with this map.

template <typename Service, typename... Args>
friend Service& make_service(execution_context& ec, Args&&... args) {
    // add this Service to this execution_context
}

template <typename Service>
friend bool has_service(execution_context& ec) {
    // return true or false
}

template <typename Service>
friend Service& use_service(execution_context& ec) {
    // get the service
}

// this way you can create your complete ExecutionObject. All these ideally you will never need to use as you would mostly use asio::io_context which itself as an execution_object.
// all this is more for information.

----------------------------------------------------------
Executor class: Since I said that an executor_context must hold an Executor. so io_context class has a nested basic_executor_type nested class which is an Executor.
API of basic_executor_type:
1) context() --> return the ExecutionContext which this Executor is part of.
2) defer()
3) dispatch()
4) post() --> all the three function defer(), dispatch() and post() have same signature. They take a function object (FO) to be executed. But they differ in how the FO will br run.
defer() --> will wait for the io_context thread to be returned to the pool before FO is executed. So FO is executed after defer() has returned.
dispatch() --> if dispatch() is called inside an io_context thread, the FO will be executed immediately
post() --> the FO will never be called immediately, even if post() is called from inside an io_context.

5) execute() --> also takes a FO and executes the FO immediately
6) running_in_this_thread() --> return true if this function is called inside an io_context
7) on_work_started()
8) on_work_finished() -->
9) query()/require() --> We will see these later. Actually Executors can have certain properties and query()/require() are used around those Executor properties.

asio::strand --> This is an Executor Adaptor. This means it encapsulates another Executor and serializes all calls to the underlying Executor.
to create a strand object, use the asio::make_strand() method which can take an Executor or an ExecutorContext.

template <typename Executor>
auto make_strand(Executor&& executor) {
    return asio::strand(std::forward<Executor>(executor));
}

template <typename ExecutorContext>
auto make_strand(ExecutorContext&& executorContext) {
    return make_strand(std::forward<ExecutorContext>(executorContext).get_executor());
}

When using async_* functions and passing a CompletionHandler to them and to serialize on the CompletionHandlers, you can use a strand. But you must submit a FO which internally used the strand. for that we use the asio::bind_executor() function.

asio::bind_executor(asio::strand, SomeFunctionObject); // will return a FO which uses strand internally, so CompletionHandlers are synchronized.