//
// Created by fgdou on 12/23/21.
//

#ifndef INC_23_BOARD_H
#define INC_23_BOARD_H

#include <vector>
#include "Point.h"
#include <set>

class Board {
public:
    Board(const Board& other);
    Board();

    void setCell(const Point& p, char c);

    bool isCell(const Point& p) const;
    bool isFree(const Point& p) const;
    bool canGo(const Point& from, const Point& to) const;

    int move(const Point& from, const Point& to);
    std::vector<Point> getPossibleMoves(const Point& from) const;
    std::vector<std::pair<Point, Point>> getPossibleMoves() const;

    char getChar(const Point& p) const;

    bool hasWin() const;
    int getPoints() const;

    void print() const;

    Board& operator=(const Board& other);
private:

    int _move(const Point& from, const Point& to, int sc, std::set<Point>& points);
    bool _canGo(const Point& from, const Point& to, std::set<Point>& points) const;

    const int score[4] = {1, 10, 100, 1000};
    char tab[3][11] = {
            {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
            {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '#'},
            {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '#'},
    };

    bool locked[3][11] = {};
};


#endif //INC_23_BOARD_H
