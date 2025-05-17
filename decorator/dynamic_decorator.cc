#include <iostream>
#include <cstdint>
#include <sstream>

struct Shape
{
    virtual std::string str() const = 0;
};

struct Circle : Shape
{
    float radius_;

    Circle(float radius) : radius_(radius) {}

    void resize(float scale_factor) {
        radius_ *= scale_factor;
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << "A circle of radius " << radius_;
        return oss.str();
    }
};

struct Square : Shape
{
    float side_;

    Square(float side) : side_(side) {}

    void resize(float scale_factor) {
        side_ *= scale_factor;
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << "A square of side " << side_;
        return oss.str();
    }
};

// Dynamic Decorator
struct ColoredShape : Shape
{
    Shape& shape;
    std::string color;

    ColoredShape(Shape &shape, std::string color) : shape(shape), color(color) {}

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

// Another Decorator
struct TransparentShape : Shape
{
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape &shape, uint8_t transparency) : shape(shape), transparency(transparency) {}

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << " % transparency";
        return oss.str();
    }
};

/*
    NOTE: Downside of Dynamic Decorator
    if we make ColoredCircle, then it will not have access to the resize function as
    it was not part of the "Shape" interface but only implemented in Circle class
*/

int main() {
    std::cout << "Dynamic Decorator\n";
    Square square{5};
    ColoredShape red_square{square, "red"};

    std::cout << square.str() << std::endl;
    std::cout << red_square.str() << std::endl;

    // let us make a blue square that is transparent
    ColoredShape blue_square{square, "blue"};
    TransparentShape blue_transp_square{ blue_square, 51 };
    std::cout << blue_transp_square.str() << std::endl;
    return 0;
}
