//
// Created by projector-user on 12/18/21.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <stack>
#include <set>
#include <cmath>
#include <limits>
#include <queue>
#include <memory>
#include <sstream>

#include "Number.h"

using namespace std;




vector<Number> openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not open");

    vector<Number> vec;
    while(file.peek() != EOF) {
        string line;
        stringstream ss;
        file >> line;
        ss << line;
        vec.emplace_back(ss);
    }

    return vec;
}

long findMax(vector<Number>& vec){
    long max = 0;
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec.size(); ++j) {
            if(i == j)
                continue;
            auto sum = vec[i]+vec[j];
            sum = sum.simplify();
            long n = sum.magnitude();
            if(n > max)
                max = n;
        }
        cout << i << '/' << vec.size() << endl;
    }
    return max;
}

int main(int argc, char** argv){
    string path = "../18/input.txt";
    auto list = openFile(path);


    auto n = list[0];

    for(int i=1; i<list.size(); i++) {
        n = n + list[i];
        //cout << "add" << endl;
        //n.print();
        n = n.simplify();
    }

    n.print();

    cout << "Magnitude : " << n.magnitude() << endl;

    long max = findMax(list);

    cout << "Max = " << max << endl;

}
//13494