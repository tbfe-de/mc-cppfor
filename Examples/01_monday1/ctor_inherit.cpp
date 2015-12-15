#include <iostream>

class Point {
protected:
    float x, y;
public:
    Point() : x(0.0), y(0.0) {}
    Point(float x_, float y_) : x(x_), y(y_) {}
    friend
    std::ostream &operator<<(std::ostream &, const Point &);
};

std::ostream &operator<<(std::ostream &lhs, const Point &rhs) {
     return lhs << "x=" << rhs.x << ", y=" << rhs.y;
}

class MovablePoint : public Point {
public:
#if 1
    using Point::Point;
    MovablePoint() =delete;
#else
    MovablePoint()
        : Point()
    {}
    MovablePoint(float x_, float y_)
        : Point(x_, y_)
    {}
#endif
    void move(float dist_x, float dist_y) {
        x += dist_x;
        y += dist_y;
    }
};

int main() {
   MovablePoint p1(1.1, 2.2);
//   MovablePoint p2;
   std::cout << p1 << std::endl;
//   std::cout << p2 << std::endl;
}

