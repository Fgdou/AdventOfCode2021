//
// Created by fgdou on 12/23/21.
//

#include "Point.h"

bool Point::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}
bool Point::operator<(const Point &other) const {
    return (x < other.x || x == other.x && y < other.y);
}