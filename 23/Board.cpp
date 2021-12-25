//
// Created by fgdou on 12/23/21.
//

#include "Board.h"
#include <iostream>
#include <string.h>

void Board::setCell(const Point &p, char c) {
    if(isCell(p))
        tab[p.y][p.x] = c;
    if(c >= 'A' && c <= 'D'){
        int x = (c-'A')*2+2;
        if(p.y == 2 && p.x == x)
            locked[p.y][p.x] = true;
    }
}

bool Board::isCell(const Point &p) const {
    if(p.x < 0 || p.x >= 11 || p.y < 0 || p.y >= 3)
        return false;
    return (tab[p.y][p.x] != '#');
}

bool Board::isFree(const Point &p) const {
    return (tab[p.y][p.x] == '.');
}

bool Board::canGo(const Point &from, const Point &to) const {
    if(from.y == 0 && to.y == 0)
        return false;
    if(from.y != 0 && to.y != 0 && from.x == to.x)
        return false;
    if(!isCell(to))
        return false;
    if(!isFree(to))
        return false;

    if(to.y > 0){
        char c = tab[from.y][from.x];

        int x = (c-'A')*2+2;

        if(x != to.x)
            return false;

        if(tab[2][to.x] == '.' && to.y != 2)
            return false;

        if(tab[2][to.x] != '.' && tab[2][to.x] != c)
            return false;
    }

    std::set<Point> points;

    std::vector<Point> moves = {
            {-1, 0},
            {1, 0},
            {0, 1},
            {0, -1}
    };

    for(auto& m : moves){
        Point p = {from.x+m.x, from.y+m.y};

        if(_canGo(p, to, points))
            return true;
    }

    return false;
}

int Board::_move(const Point &from, const Point &to, int sc, std::set<Point>& points) {
    if(points.find(from) != points.end())
        return -1;
    if(!isCell(from))
        return -1;
    if(!isFree(from))
        return -1;
    if(from == to)
        return 0;

    int min = -1;

    points.insert(from);

    std::vector<Point> moves = {
            {-1, 0},
            {1, 0},
            {0, 1},
            {0, -1}
    };

    for(auto& mm : moves){
        Point p = {from.x+mm.x, from.y+mm.y};

        int m = _move(p, to, sc, points);
        if(min == -1 || m != -1 && m < min)
            min = m;
    }

    points.erase(from);

    if(min == -1)
        return -1;

    return min + sc;
}

int Board::move(const Point &from, const Point &to) {
    std::set<Point> points;
    char c = tab[from.y][from.x];
    tab[from.y][from.x] = '.';

    int sc = score[c-'A'];

    int m = _move(from, to, sc, points);
    if(m == -1)
        return -1;

    if(to.y > 0)
        locked[to.y][to.x] = true;
    tab[to.y][to.x] = c;


    return m;
}

bool Board::_canGo(const Point &from, const Point &to, std::set<Point> &points) const {
    if(points.find(from) != points.end())
        return false;

    if(!isCell(from))
        return false;
    if(!isFree(from))
        return false;
    if(from == to)
        return true;

    points.insert(from);
    std::vector<Point> moves = {
            {-1, 0},
            {1, 0},
            {0, 1},
            {0, -1}
    };

    for(auto& m : moves){
        Point p = {from.x+m.x, from.y+m.y};

        if(_canGo(p, to, points))
            return true;
    }

    points.erase(from);

    return false;
}

bool Board::hasWin() const {
    for (int i = 0; i < 4; ++i) {
        char c = (i+'A');
        int x = i*2+2;

        if(tab[1][x] != c)
            return false;
        if(tab[2][x] != c)
            return false;
    }
    return true;
}

std::vector<Point> Board::getPossibleMoves(const Point &from) const {
    std::vector<Point> points;

    if(!isCell(from) || isFree(from))
        return points;
    if(locked[from.y][from.x])
        return points;

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 11; ++x) {
            Point p = {x, y};
            if(canGo(from, p))
                points.emplace_back(p);
        }
    }
    return points;
}

std::vector<std::pair<Point, Point>> Board::getPossibleMoves() const {
    std::vector<std::pair<Point, Point>> points;

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 11; ++x) {
            Point p = {x, y};
            auto vec = getPossibleMoves(p);

            for(auto pp : vec){
                points.emplace_back(std::make_pair(p, pp));
            }
        }
    }

    return points;
}

void Board::print() const {
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 11; ++x) {
            std::cout << tab[y][x];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

char Board::getChar(const Point &p) const {
    if(isCell(p))
        return tab[p.y][p.x];
    return '#';
}

Board &Board::operator=(const Board &other) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 11; ++j) {
            tab[i][j] = other.tab[i][j];
            locked[i][j] = other.locked[i][j];
        }
    }
    return *this;
}

Board::Board(const Board& other)
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 11; ++j) {
            tab[i][j] = other.tab[i][j];
            locked[i][j] = other.locked[i][j];
        }
    }
}

int Board::getPoints() const {
    int s = 0;
    for (int i = 0; i < 4; ++i) {
        int x = i*2+2;
        char c = (i+'A');

        if(isFree({x, 2}))
            continue;
        if(tab[2][x] == c && locked[2][x])
            s += 1*score[i];
        else
            continue;
        if(isFree({x, 1}))
            continue;
        if(tab[1][x] == c && locked[1][x])
            s += 1*score[i];
    }
    for (int i = 0; i < 11; ++i) {
        if(isFree({i, 0}))
            continue;
        char c = tab[0][i];
        int x = (c-'A')*2+2;
        int d = abs(i-x)*score[c-'A'];
        s -= d;
    }
    return s;
}

Board::Board() = default;
