/*
  Lets declare a template function which takes a pointer type of the template parameter T. And lets delete the void* and char* versions of it. Straight forward really */

template <typename T>
void processPointer(T* ptr);

// delete void*, char*, const char*, const void*, const volatile char*, const volatile void*
template <>
void processPointer<void>(void*) = delete;

template <>
void processPointer<char>(char*) = delete;
// Similary for const char*, const void* and with volatile specifiers.

// Lets declare a template function inside a normal class and disable the one which takes a void*
class Widget {
public:
    template <typename T>
    void process(T* ptr);

private:
    template<>
    void process(T* ptr); // define private and dont give body. This doesnt work unfortunately, as standard doesnt allow you to write template specializations at class scope.
};
// whereas with alias templates, it becomes very easy.

class Widget2 {
public:
    template <typename T>
    void process(T* ptr);
};

//specialization using alias template
template <>
void Widget2::process<void>(void* ptr) = delete;
