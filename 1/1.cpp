//
// Created by fgdou on 12/1/21.
//
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<int> getFile(string& path){
    ifstream file;
    file.open(path);

    if(!file.is_open())
        throw runtime_error("Cannot open the file");

    vector<int> vec;

    while(file.peek() != EOF){
        int i;
        file >> i;
        vec.push_back(i);
    }

    return vec;
}

int countLarger(vector<int>& vec){
    int n = 0;
    for(int i=1; i<vec.size(); i++){
        if(vec[i] > vec[i-1])
            n++;
    }
    return n;
}
vector<int> groupNumbers(vector<int>& in){
    vector<int> group;

    for(int i=2; i<in.size(); i++){
        int sum = in[i]+in[i-1]+in[i-2];
        group.push_back(sum);
    }
    return group;
}

int main(int argc, char** argv){
    string path = "../1/input.txt";
    auto input = getFile(path);
    int n = countLarger(input);

    cout << n << endl;

    auto group = groupNumbers(input);
    int nGroup = countLarger(group);

    cout << nGroup << endl;
}