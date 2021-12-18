#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

typedef map<string, vector<string>> Cave;
typedef map<string, int> Passed;
typedef vector<vector<string>> Paths;

Cave openFile(string& path){
    fstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not opened");

    Cave c;
    while(file.peek() != EOF){
        string line;
        file >> line;

        int finded = line.find('-');

        string e1 = line.substr(0, finded);
        string e2 = line.substr(finded+1);

        c[e1].emplace_back(e2);
        c[e2].emplace_back(e1);
    }

    return c;
}

bool isSmallCave(const string& cave){
    return cave[0] >= 'a' && cave[0] <= 'z';
}

Paths getPaths(const string& start, Cave& cave, Passed passed = {}, vector<string> list = {}, bool singleSmall = false){
    if(isSmallCave(start) && passed[start] > 0) {
        if(!singleSmall && start != "start")
            singleSmall = true;
        else
            return {};
    }

    passed[start]++;
    list.emplace_back(start);

    if(start == "end")
        return {list};


    Paths p;
    for(const auto& child : cave[start]){
        auto res = getPaths(child, cave, passed, list, singleSmall);
        p.insert(p.end(), res.begin(), res.end());
    }

    return p;
}

void printPaths(Paths& paths){
    for(auto& path : paths){
        for(auto& str : path){
            cout << str << ',';
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char** argv){
    string path = "../12/input.txt";

    auto cave = openFile(path);

    auto paths = getPaths("start", cave);

    printPaths(paths);

    cout << paths.size() << endl;
}
//4707
//130493