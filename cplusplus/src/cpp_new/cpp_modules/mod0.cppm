module;

export module Square;

int square(int i);

export class Square {
private:
    int m_value;
public:
    Square(int i) : m_value(square(i)) {}

    int getValue() const { return m_value; }
};

export template <typename T>
Square toSquare(const T& t) {
    return Square(t);
}

int square(int i) {
    return i * i;
}