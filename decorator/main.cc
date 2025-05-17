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

    Dynamic Decorators work at Runtime, while static Decorators work at compile time
*/

/*
    ------------------------------------------------ STATIC DECORATORS --------------------------------------------
    It uses inheritance instead of aggregation unlike dynamic decorators giving access to underlying methofs
    Mixed Inheritance: in C++ we can inherit from template argument
*/

// T must be a Shape type
template<typename T> struct ColoredShape2 : T
{
    //static_assert(is_base_of<Shape, T>::value, "Template argument must be a Shape")

    std::string color;
    ColoredShape2() {}

    // TransparentShape2<ColoredShape2<Square>> sq{10, "red", 44}
    // using varidaic templates and forwarding
    template <typename...Args>
    ColoredShape2(const std::string& color, Args ...args)
        : T(std::forward<Args>(args)...), color{color} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has the color "  << color;
        return oss.str();
    }
};

// T must be a Shape type
template<typename T> struct TransparentShape2 : T
{
    //static_assert(is_base_of<Shape, T>::value, "Template argument must be a Shape");

    uint8_t transparency;

    // using varidaic templates and forwarding
    template <typename...Args>
    TransparentShape2(const uint8_t transparency, Args ...args)
        : T(std::forward<Args>(args)...), transparency{transparency} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << " % transparency";
        return oss.str();
    }
};

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

    // Static Decorators
    std::cout << "\nStatic Decorators\n";
    ColoredShape2<Circle> green_circle{"green", 5};
    std::cout << green_circle.str() << std::endl;
    green_circle.resize(4);
    std::cout << green_circle.str() << std::endl;

    TransparentShape2<ColoredShape2<Square>> square2{51, "blue", 10};
    std::cout << square2.str() << std::endl;
    return 0;
}
