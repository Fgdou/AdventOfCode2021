//
// Created by fgdou on 12/24/21.
//

#include "Operation.h"
#include <iostream>

Operation::Operation(const std::string &type, char v1, char v2)
    : type(type), vars()
{
    vars[0] = v1;
    vars[1] = v2;
}

bool isVar(char c){
    return c >= 'a' && c <= 'z';
}

void Operation::calc(Registers &regs, Inputs& ins) const {
    long n;
    long b;
    long a = regs[vars[0]];
    if(isVar(vars[1]))
        b = regs[vars[1]];
    else
        b = (vars[1]-'0');

    if(type == "inp"){
        n = ins.front();
        ins.pop();
        regs[vars[0]] = n;
    }else if(type == "add"){
        n = a+b;
        regs[vars[0]] = n;
    }else if(type == "mul"){
        n = a*b;
        regs[vars[0]] = n;
    }else if(type == "div"){
        if(b == 0)
            throw std::runtime_error("Division by 0");
        n = a/b;
        regs[vars[0]] = n;
    }else if(type == "mod"){
        if(b == 0)
            throw std::runtime_error("Mod by 0");
        n = a%b;
        regs[vars[0]] = n;
    }else if(type == "eql") {
        n = (a == b);
        regs[vars[0]] = n;
    }
}

void Operation::print() const {
    std::cout << type << ' ' << vars[0] << ' ' << vars[1] << std::endl;
}

void Operation::reverse(Possibilities& pos) const{
    std::string rev;

    if(pos[vars[0]].empty())
        pos[vars[0]] += vars[0];
    if(isVar(vars[1]) && pos[vars[1]].empty())
        pos[vars[1]] += vars[1];

    std::string ss;
    ss += vars[1];

    std::string a = "(" + pos[vars[0]] + ")";
    std::string b = "(" + ((isVar(vars[1])) ? pos[vars[1]] : ss) + ")";

    if(type == "add")
        rev = a+"-"+b;
    else if(type == "mul")
        rev = a+"/"+b;
    else if(type == "div")
        rev = a+"*"+b;
    else if(type == "mod")
        rev = b+"*k"+"+"+a;
    else if(type == "eql")
        rev = "1:" +a+"="+b+"|0:"+a+"!="+b;// a == b --> 1 : 0

    if(!rev.empty())
        pos[vars[0]] = rev;
}
