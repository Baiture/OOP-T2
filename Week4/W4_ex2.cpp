#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

class Point {
private:
    double x, y;
public:
    Point(double x = 10, double y = 20) : x(x), y(y) {}
    
    Point(const Point& p) : x(p.x), y(p.y) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void display() const {
        cout << "(" << (int)x << ", " << (int)y << ")";
    }
};

class LineSegment {
private:
    Point d1, d2;
public:
    LineSegment() : d1(85, 52), d2(10, 24) {}

    LineSegment(const Point& p1, const Point& p2) : d1(p1), d2(p2) {}

    LineSegment(double x1, double y1, double x2, double y2) 
        : d1(x1, y1), d2(x2, y2) {}

    LineSegment(const LineSegment& s) : d1(s.d1), d2(s.d2) {}

    double length() const {
        return sqrt(pow(d1.getX() - d2.getX(), 2) + pow(d1.getY() - d2.getY(), 2));
    }

    void display() const {
        cout << "Doan thang tu ";
        d1.display();
        cout << " den ";
        d2.display();
        cout << fixed << setprecision(2) << " | Do dai: " << length() << endl;
    }
};

int main() {
    LineSegment l1;
    l1.display();

    Point p1(12, 45), p2(78, 33);
    LineSegment l2(p1, p2);
    l2.display();

    LineSegment l3(25, 60, 99, 15);
    l3.display();

    LineSegment l4(l3);
    l4.display();

    return 0;
}
