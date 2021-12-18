//
// Created by projector-user on 12/7/21.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;
typedef vector<int> List;

List openFile(string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not open");

    vector<int> vec;
    while(file.peek() != EOF){
        char buf[10];
        file.getline(buf, 10, ',');
        vec.push_back(stoi(buf));
    }

    return vec;
}
void print(List& vec){
    for(int n : vec)
        cout << n << ',';
    cout << endl;
}
int median(List vec){
    sort(vec.begin(), vec.end());
    return vec[vec.size()/2];
}
int average(List& vec){
    int s = 0;
    for(auto n : vec)
        s += n;
    return round((double)s/vec.size());
}

int sum(int n){
    int res = 0;
    for(int i=1; i<n+1; i++)
        res += i;
    return res;
}

int getMax(List& vec){
    int max = 0;
    for(auto n : vec){
        if(n > max)
            max = n;
    }
    return max;
}

int goTo(List& vec, int pos){
    int fuel = 0;

    for(auto n : vec) {
        int s = sum(abs(n - pos));
        //cout << n << "->" << pos << " : " << s << endl;
        fuel += s;
    }

    return fuel;
}

int main(int argc, char** argv){
    string path = "../7/input.txt";
    auto vec = openFile(path);

    int med = average(vec);

    int fuel = goTo(vec, med);

    int max = getMax(vec);
    int min = numeric_limits<int>::max();
    for(int i=0; i<=max; i++){
        cout << i << '/' << max << endl;
        int c = goTo(vec, i);
        if(c < min)
            min = c;
    }


    cout << med << endl;
    cout << min << endl;
}