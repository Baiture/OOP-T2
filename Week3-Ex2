#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class Circle {
public:
    Point center;
    double radius;
    Circle(Point center, double radius) : center(center), radius(radius) {}
};

class Rectangle {
public:
    Point corner;
    double width, height;
    Rectangle(Point corner, double w, double h) : corner(corner), width(w), height(h) {}
};

double distance_sq(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

bool point_in_circle(const Circle& circle, const Point& p) {
    return distance_sq(circle.center, p) <= (circle.radius * circle.radius);
}

bool rect_in_circle(const Circle& circle, const Rectangle& rect) {
    Point corners[] = {
        {rect.corner.x, rect.corner.y},
        {rect.corner.x + rect.width, rect.corner.y},
        {rect.corner.x, rect.corner.y + rect.height},
        {rect.corner.x + rect.width, rect.corner.y + rect.height}
    };

    for (const auto& p : corners) {
        if (!point_in_circle(circle, p)) return false;
    }
    return true;
}

bool rect_circle_overlap(const Circle& circle, const Rectangle& rect) {
    double closest_x = clamp(circle.center.x, rect.corner.x, rect.corner.x + rect.width);
    double closest_y = clamp(circle.center.y, rect.corner.y, rect.corner.y + rect.height);

    Point closest_point(closest_x, closest_y);
    return point_in_circle(circle, closest_point);
}

int main() {
    Circle circle({150, 100}, 75);

    cout << boolalpha;

    Point p1(150, 100);
    Point p2(180,360);
    cout << "p1 trong vong tron: " << point_in_circle(circle, p1) << endl;
    cout << "p2 trong vong tron: " << point_in_circle(circle, p2) << endl;

    Rectangle rSmall({140, 90}, 10, 10);
    Rectangle rLarge({0, 0}, 500, 500);

    cout << "rSmall nam trong circle: " << rect_in_circle(circle, rSmall) << endl;
    cout << "rLarge overlap circle: " << rect_circle_overlap(circle, rLarge) << endl;

    return 0;
}
