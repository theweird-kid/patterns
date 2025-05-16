#include <cmath>
#include <iostream>
#include <ostream>

enum class PointType {
    cartesian,
    polar
};

class Point {
public:
    // friend class PointFactory                                    # Violates Open-Closed Principle
    Point(float x, float y) : x(x) , y(y) {}
private:
    float x, y;

    friend std::ostream& operator<<(std::ostream &os, const Point &point) {
        os << "X: " << point.x << ", Y: " << point.y;
        return os;
    }
};

struct PointFactory {
    static Point NewCartesian(float x, float y) {
        return Point{x, y};
    }

    static Point NewPolar(float rho, float theta) {
        return Point{ rho * static_cast<float>(cos(theta)),
                rho * static_cast<float>(sin(theta))
        };
    }
};

int main() {
    std::cout << "Factory Pattern\n";

    auto p = PointFactory::NewPolar(4, M_PI_4);
    std::cout << p << std::endl;
}
