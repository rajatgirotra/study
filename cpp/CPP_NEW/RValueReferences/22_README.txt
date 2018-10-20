Whenever considering your options whether to use separate overloads for lvalue and rvalue or to have a single function taking
an universal reference. consider the pros and cons of the 3 options shown below, and evaluate the cost in terms of copy and move
operations. But most of the types you'll find that Option 2 (using universal reference is viable).

Option 1: separate overloads
========
class Widget {
    std::vector<std::string> names;
public:
    void addName(const std::string& newName) {
        names.push_back(newName);
    }

    void addName(std::string&& newName) {
        names.push_back(std::move(newName));
    }
};

Cost for lvalue - 1 copy operation
Cost for rvalue - 1 move operation

Option 2: universal reference
========

class Widget {
    std::vector<std::string> names;
public:
    template <typename T>
    void addName(T&& newName) {
        names.push_back(std::forward<T>(newName));
    }
};

Cost for lvalue - 1 copy operation
Cost for rvalue - 1 move operation

Option 3: simple pass by value
========
class Widget {
    std::vector<std::string> names;
public:
    void addName(std::string newName) {
        names.push_back(std::move(newName));
    }
};

Cost for lvalue - 2 copies 1 copy operation
Cost for rvalue - 1 copy and 1 move operation

Use
===
Widget w;
std::string name("Rajat");
w.addName(name); // lvalue
w.addName(name + " Girotra"); // rvalue

