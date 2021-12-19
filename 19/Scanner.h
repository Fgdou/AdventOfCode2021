//
// Created by projector-user on 12/19/21.
//

#ifndef INC_4_SCANNER_H
#define INC_4_SCANNER_H

#include <vector>
#include <iostream>
#include "Point.h"

class ErrorNotFound: public std::exception{
public:
    const char * what() const noexcept override;
};

class Scanner {
public:
    Scanner(const Point& pos, int n);
    Scanner(const Scanner& copy) = default;

    void addPoint(const Point& p);
    Scanner rotate(const Point& r) const;
    Scanner move(const Point& p) const;

    bool has12InCommon(const Scanner& sc) const;

    Scanner findBestFit1orientation(const Scanner& other) const;
    Scanner findBestFit(const Scanner& other) const;

    friend std::ostream& operator<<(std::ostream& s, const Scanner& sc);

    bool operator==(const Scanner& other) const;

    const Point& getPos();
    int getN();

    const std::vector<Point>& getPoints() const;
private:
    std::vector<Point> points;
    Point pos;
    int n;
};


#endif //INC_4_SCANNER_H
