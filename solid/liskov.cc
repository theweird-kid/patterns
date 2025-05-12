#include <iostream>

// -------------------------------------------- L => Liskov Substitution Principle -------------------------------------------------------------

class Rectangle
{
protected:
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h) {}
    int getWidth() const { return width; }
    virtual void setWidth(int w) { this->width = w; }

    int getHeight() const { return height; }
    virtual void setHeight(int h) { this->height = h; }

    int area() { return width * height; }
};

class Square : Rectangle
{
public:
    Square(int size) : Rectangle(size, size) {}

    void setWidth(int w) override {
        this->width = this->height = w;
    }

    void setHeight(int h) override {
        this->width = this->height = h;
    }
};

void process(Rectangle& r)
{
    int w = r.getWidth();
    r.setHeight(10);

    std::cout << "expected area = " << (w * 10) << ", got " << r.area() << std::endl;
}

int main() {
    std::cout << "Liskov\n";
    Rectangle r {3, 10};
    process(r);

    // Inserting a square object into process which expects a Rectangle would break functionality
    // hence it violates Liskov Substitution principle
}
