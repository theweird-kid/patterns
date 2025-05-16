#include <cmath>
#include <iostream>
#include <ostream>

enum class PointType {
    cartesian,
    polar
};

class Point {
private:
    // Private Constructor
    Point(float x, float y) : x(x) , y(y) {}
    float x, y;

    friend std::ostream& operator<<(std::ostream &os, const Point &point) {
        os << "X: " << point.x << ", Y: " << point.y << std::endl;
        return os;
    }

    struct PointFactory {
        PointFactory() {}
        static Point NewCartesian(float x, float y) {
            return Point{x, y};
        }

        static Point NewPolar(float rho, float theta) {
            return Point{ rho * static_cast<float>(cos(theta)),
                    rho * static_cast<float>(sin(theta))
            };
        }
    };

public:
    // Inner Factory instance
    static PointFactory Factory;
};


int main() {
    std::cout << "Inner Factory Pattern\n";

    auto p = Point::Factory.NewPolar(4, M_PI_4);
    auto p2 = Point::Factory.NewCartesian(4, 5);
    std::cout << p << p2;
}
