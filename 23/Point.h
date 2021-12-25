//
// Created by fgdou on 12/23/21.
//

#ifndef INC_23_POINT_H
#define INC_23_POINT_H


struct Point {
    int x, y;

    bool operator==(const Point& other) const;
    bool operator<(const Point& other) const;
};


#endif //INC_23_POINT_H
