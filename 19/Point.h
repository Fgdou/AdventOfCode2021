//
// Created by projector-user on 12/19/21.
//

#ifndef INC_4_POINT_H
#define INC_4_POINT_H

#include <iostream>

class Point {
public:
    Point();
    Point(int x, int y, int z);
    Point(const Point& point) = default;

    Point rotate(const Point& r) const;

    Point operator+(const Point& other) const;
    Point& operator+=(const Point& other);
    Point operator-(const Point& other) const;
    Point& operator-=(const Point& other);

    bool operator==(const Point& other) const;
    Point& operator=(const Point& other) = default;

    long distance(const Point& other) const;

    int x, y, z;

    friend std::ostream& operator<<(std::ostream& s, const Point& p);
private:
    static void _rotate(int n, int& x, int& y);
};


#endif //INC_4_POINT_H
