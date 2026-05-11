#include <iostream>
#include <cmath>
#include <iomanip>

class Point {
private:
    int x, y;

public:
    Point() {
        x = 0;
        y = 1;
    }

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    void read() {
        std::cin >> x >> y;
    }

    void print() {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    double distance() {
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    double distance(Point P) {
        return std::sqrt(std::pow(x - P.x, 2) + std::pow(y - P.y, 2));
    }
};
