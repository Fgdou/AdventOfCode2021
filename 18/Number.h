//
// Created by projector-user on 12/18/21.
//

#ifndef INC_4_NUMBER_H
#define INC_4_NUMBER_H

#include <memory>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Number{
private:
    unique_ptr<Number> left;
    unique_ptr<Number> right;
    int value;

public:
    Number();
    explicit Number(int value);

    Number(stringstream& ss);
    Number(Number&& left, Number&& right);
    Number(const Number& left, const Number& right);
    Number(const Number& copy);
    Number& operator=(const Number& copy);

    Number operator+(const Number& n2);
    bool operator==(const Number& other) const;
    bool operator!=(const Number& other) const;

    Number simplify() const;
    Number explode() const;

    long magnitude() const;

    bool isValue() const;

    void print() const;
    void rprint() const;
private:

    static Number _explode(const Number& current, const Number& root, Number& deleted, int cnt = 0);
    Number split();
    static void _addToVec(Number& current, vector<Number*>& vec);
    static void _addLeftRight(Number& root, const Number& toAdd);
    Number _split(bool& stop);
};


#endif //INC_4_NUMBER_H
