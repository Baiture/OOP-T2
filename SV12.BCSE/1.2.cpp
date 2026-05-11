#include <iostream>
#include <cmath>
using namespace std;

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
        cin >> x >> y;
    }

    void print() {
        cout << "(" << x << ", " << y << ")" << endl;
    }

    void move(int dx, int dy) {
        x = x + dx;
        y = y + dy;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    double distance() {
        return sqrt((double)x * x + (double)y * y);
    }

    double distance(Point P) {
        int dx = this->x - P.x;
        int dy = this->y - P.y;
        return sqrt((double)dx * dx + (double)dy * dy);
    }
};
