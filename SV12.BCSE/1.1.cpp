#include <iostream>
#include <cmath>
#include <iomanip>

class Point {
private:
    double x, y;

public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void read() {
        std::cin >> x >> y;
    }

    void move(double dx, double dy) {
        x += dx;
        y += dy;
    }

      double distance(const Point& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    double distance() const {
        return std::sqrt(x * x + y * y);
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};
