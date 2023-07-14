#ifndef POINT_H
#define POINT_H

class Point {
private:
    int x;
    int y;

public:
    Point();

    Point(int x, int y);

    int getX();
    int getY();

    void setX(int x);
    void setY(int y);

    bool operator==(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }
};

#endif