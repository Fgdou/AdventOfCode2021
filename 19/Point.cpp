//
// Created by projector-user on 12/19/21.
//

#include "Point.h"
#include <memory>
#include <cmath>

Point::Point()
    :x(0), y(0), z(0){}
Point::Point(int x, int y, int z)
    :x(x), y(y), z(z){}

Point Point::rotate(const Point& r) const{
    Point p = *this;
    _rotate(r.x, p.y, p.z);
    _rotate(r.y, p.x, p.z);
    _rotate(r.z, p.x, p.y);
    return p;
}

void Point::_rotate(int n, int &x, int &y) {
    n = n%4;
    if(n == 0)
        return;
    if(n == 1){
        int tmp = x;
        x = y;
        y = -tmp;
    }else if(n == 2){
        x = -x;
        y = -y;
    }else if(n == 3){
        int tmp = y;
        y = x;
        x = -tmp;
    }

}

long Point::distance(const Point& other) const{
    return abs(x-other.x)+abs(y-other.y)+abs(z-other.z);
}


Point Point::operator+(const Point& other) const{
    return {x+other.x, y+other.y, z+other.z};
}
Point& Point::operator+=(const Point& other){
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}
Point Point::operator-(const Point& other) const{
    return {x-other.x, y-other.y, z-other.z};
}
Point& Point::operator-=(const Point& other){
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

bool Point::operator==(const Point& other) const{
    return x == other.x && y == other.y && z == other.z;
}
std::ostream& operator<<(std::ostream& s, const Point& p){
    s << "{" << p.x << "," << p.y << "," << p.z << "}";
    return s;
}