module;

export module Square;

int square(int i);

// not exported.
struct Data {
};

export class Square {
    int m_value;
public:
    Square(int i) : m_value(square(i)) {}

    int getValue() const { return m_value; }

    Data getData() const noexcept {
        return Data();
    }
};

export template <typename T>
Square toSquare(const T& t) {
    return Square(t);
}

int square(int i) {
    return i * i;
}