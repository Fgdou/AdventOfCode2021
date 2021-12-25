//
// Created by fgdou on 12/24/21.
//

#ifndef INC_24_OPERATION_H
#define INC_24_OPERATION_H

#include <string>
#include <map>
#include <vector>
#include <queue>

typedef std::map<char, long> Registers;
typedef std::queue<long> Inputs;
typedef std::map<char, std::string> Possibilities;

class Operation {
public:
    Operation(const std::string& type, char v1, char v2);
    Operation(const Operation& copy) = default;

    void calc(Registers& regs, Inputs& ins) const;
    void print() const;

    void reverse(Possibilities& pos) const;
private:
    std::string type;
    char vars[2];
};


#endif //INC_24_OPERATION_H
