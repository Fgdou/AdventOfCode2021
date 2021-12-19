//
// Created by projector-user on 12/19/21.
//

#include "Scanner.h"
#include <algorithm>

const char* ErrorNotFound::what() const noexcept {
    return "Not found";
}

Scanner::Scanner(const Point& pos, int n):points(), pos(pos), n(n){}

void Scanner::addPoint(const Point &p) {
    points.emplace_back(p);
}

Scanner Scanner::rotate(const Point &r) const {
    Scanner sc(pos, n);

    for(const Point& p : points){
        sc.addPoint((p-pos).rotate(r) + pos);
    }

    return sc;
}

bool Scanner::has12InCommon(const Scanner &sc) const {
    int cnt = 0;

    for(const Point& p1 : points){
        for(const Point& p2 : sc.points){
            if(p1 == p2)
                cnt++;
            if(cnt == 12)
                return true;
        }
    }

    return false;
}

Scanner Scanner::findBestFit1orientation(const Scanner &other) const {
    for(auto& p1 : points){
        for(auto& p2 : other.points){
            Point diff = p1-p2;

            Scanner other2 = other.move(diff);
            if(has12InCommon(other2))
                return other2;
        }
    }
    throw ErrorNotFound();
}

Scanner Scanner::move(const Point& p) const{
    Scanner sc{pos+p, n};

    for(const auto& pp : points){
        sc.addPoint(pp+p);
    }

    return sc;
}

const Point& Scanner::getPos(){
    return pos;
}
int Scanner::getN(){
    return n;
}

bool Scanner::operator==(const Scanner& other) const{
    return n == other.n;
}

Scanner Scanner::findBestFit(const Scanner& other) const{
    for (int j = 0; j < 4; ++j) {
        Point r = {0, 0, j};
        try {
            Scanner rr = other.rotate(r);
            Scanner rr2 = findBestFit1orientation(rr);
            return rr2;
        } catch (const ErrorNotFound& e) {
            continue;
        }
    }
    for (int j = 0; j < 4; ++j) {
        Point r = {1, 0, j};
        try {
            Scanner rr = other.rotate(r);
            Scanner rr2 = findBestFit1orientation(rr);
            return rr2;
        } catch (const ErrorNotFound& e) {
            continue;
        }
    }
    for (int j = 0; j < 4; ++j) {
        Point r = {2, 0, j};
        try {
            Scanner rr = other.rotate(r);
            Scanner rr2 = findBestFit1orientation(rr);
            return rr2;
        } catch (const ErrorNotFound& e) {
            continue;
        }
    }
    for (int j = 0; j < 4; ++j) {
        Point r = {3, 0, j};
        try {
            Scanner rr = other.rotate(r);
            Scanner rr2 = findBestFit1orientation(rr);
            return rr2;
        } catch (const ErrorNotFound& e) {
            continue;
        }
    }
    for (int j = 0; j < 4; ++j) {
        Point r = {0, 1, j};
        try {
            Scanner rr = other.rotate(r);
            Scanner rr2 = findBestFit1orientation(rr);
            return rr2;
        } catch (const ErrorNotFound& e) {
            continue;
        }
    }
    for (int j = 0; j < 4; ++j) {
        Point r = {0, 3, j};
        try {
            Scanner rr = other.rotate(r);
            Scanner rr2 = findBestFit1orientation(rr);
            return rr2;
        } catch (const ErrorNotFound& e) {
            continue;
        }
    }

    throw ErrorNotFound();
}

const std::vector<Point>& Scanner::getPoints() const{
    return points;
}

std::ostream& operator<<(std::ostream& s, const Scanner& sc){
    s << sc.n << sc.pos << std::endl;
    for(auto& p : sc.points){
        s << "\t" << p << std::endl;
    }
    return s;
}