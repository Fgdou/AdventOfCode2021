//
// Created by fgdou on 12/24/21.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <map>
#include "ALU.h"
#include <queue>

using namespace std;

ALU openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not opened");

    ALU alu;
    char buff[100];
    while(file.peek() != EOF){
        file.getline(buff, 100);
        string line = buff;

        string ope = line.substr(0, 3);
        char v1, v2 = '.';

        v1 = line[4];
        if(ope != "inp")
            v2 = line[6];

        Operation op(ope, v1, v2);
        alu.addOperation(op);
    }

    return alu;
}

ostream& operator<<(ostream& cc, const Registers& in){
    for(auto p : in){
        cc << p.first << ':' << p.second << endl;
    }
    return cc;
}
ostream& operator<<(ostream& cc, const Possibilities& pos){
    for(auto p : pos){
        cc << p.first << ':' << p.second << endl;
    }
    return cc;
}

int main(int argc, char** argv){
    string path = "../24/example.txt";

    auto alu = openFile(path);

    Inputs in;
    in.push(1);
    in.push(3);

    alu.print();
    cout << alu.calc(in);
    cout << alu.reverse();
}