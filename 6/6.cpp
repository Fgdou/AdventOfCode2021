#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef vector<long long> List;

List openFile(string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not open");

    List vec(9);
    while(file.peek() != EOF){
        char buf[10];
        file.getline(buf, 10, ',');
        int n = stoi(buf);
        vec[n]++;
    }

    return vec;
}

void iterate(List& vec){
    long first = vec[0];

    for(int i=0; i<vec.size()-1; i++){
        vec[i] = vec[i+1];
    }
    vec[8] = 0;

    vec[6] += first;
    vec[8] += first;
}

void print(List& vec){
    for(auto n : vec){
        cout << n << ',';
    }
    cout << endl;
}

long sum(List& vec){
    long n = 0;
    for(long i : vec)
        n += i;
    return n;
}

int main(int argc, char** argv){
    string path = "../6/input.txt";
    auto vec = openFile(path);

    print(vec);
    for(int i=0; i<256; i++){
        iterate(vec);
        print(vec);
    }
    print(vec);

    cout << sum(vec) << endl;
}