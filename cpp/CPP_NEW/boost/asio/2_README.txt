Please read
 sync_timer.cpp
 async_timer.cpp,
 async_repeat_timer.cpp,
 async_repeat_timer_handler_function.cpp
 strand_usage.cpp

ExecutionContext --> A user defined ExecutionContext class must satisfy the following requirements
class MyEC {
   using executor_type = SomeType;
   executor_type get_executor();
   ~MyEC();
};

Also, such a class must derive from asio::execution_context. The asio::execution_context class defines the context for function object (CompletionHandler) execution.
Example of one such class asio::io_context.

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