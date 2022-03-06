/*
 * constraints can subsume other constraints.
 * and if we have overloading templates for both concepts and both are satisfied, the compiler chooses the version that is most constrained.
 * so we do not get any ambiguity.
 */
#include <concepts>
#include <iostream>
#include <type_traits>
using namespace std;

struct GeoLocation {
    int w_;
    int h_;
    GeoLocation(int wArg, int hArg) : w_(wArg), h_(hArg) {}
    int width() const noexcept { return w_; }
    int height() const noexcept { return h_; }

    void draw() const noexcept {
        cout << "GeoObject::draw()\n";
    }
};

struct Color {};

struct ColoredGeoLocation : public GeoLocation {
    Color color_;
    ColoredGeoLocation(int wArg, int hArg, Color cArg) : GeoLocation(wArg, hArg), color_(cArg)
    {}

    Color getColor() const noexcept { return color_; }
    void setColor(Color cArg) noexcept { color_ = cArg; }
};

template <typename T>
concept GeoObject = requires(T obj) {
    { obj.width() } -> std::integral;
    { obj.height() } -> std::integral;
    obj.draw();
};

template <typename T>
concept ColoredGeoObject =
    GeoObject<T> && requires(T obj) {
      obj.setColor(Color{});
        { obj.getColor() } -> std::convertible_to<Color>;
};

template <GeoObject T>
void process(T) {
    cout << "process called for GeoObject concept\n";
}

template <ColoredGeoObject T>
void process(T) {
    cout << "process called for ColoredGeoObject concept\n";
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    GeoLocation gl(10, 20);
    ColoredGeoLocation cgl(10, 20, Color{});

    process(gl);  // chooses process with GeoObject concept
    process(cgl); // chooses process with ColoredGeoObject concept
}

