//
// Created by fgdou on 12/24/21.
//

#include "ALU.h"

ALU::ALU() : operations() {

}

void ALU::addOperation(const Operation &op) {
    operations.emplace_back(op);
}

Registers ALU::calc(Inputs inputs) const {
    Registers regs;
    for(auto& op : operations){
        op.calc(regs, inputs);
    }
    return regs;
}

void ALU::print() const {
    for(auto& op : operations)
        op.print();
}

Possibilities ALU::reverse() const {
    Possibilities p;
    auto i = operations.end();
    while (i != operations.begin())
    {
        --i;
        i->reverse(p);
    }
    return p;
}
