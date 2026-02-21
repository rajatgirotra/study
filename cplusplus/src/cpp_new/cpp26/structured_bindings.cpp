//C++26 allows variadic structured bindings. See examples below.

#include <print>

// variadic structured binding can only be used in a template context.
// our inspect function below is a template only under the hood due to use of auto in its parameter list.
void inspect(auto&& obj) {
    auto&& [...values] = std::forward<decltype(obj)>(obj);
    std::println("object has {} elements.", sizeof...(values));
    int count = 0;
    (std::println("Elem {}: {}", count++, values), ...);
}

int main() {
    struct MyData {
        int x;
        int y;
        double z;
    };

    MyData value {1, 2, 4.5};
}
