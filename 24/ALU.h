//
// Created by fgdou on 12/24/21.
//

#ifndef INC_24_ALU_H
#define INC_24_ALU_H

#include <vector>
#include "Operation.h"

class ALU {
public:
    ALU();
    ALU(const ALU& copy) = default;

    void addOperation(const Operation& op);
    Registers calc(Inputs inputs) const;

    Possibilities reverse() const;

    void print() const;
private:
    std::vector<Operation> operations;
};


#endif //INC_24_ALU_H
