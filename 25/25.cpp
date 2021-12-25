//
// Created by fgdou on 12/25/21.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <map>
#include <queue>

using namespace std;

typedef vector<string> Map;

Map openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not opened");

    Map m;

    while(file.peek() != EOF){
        string line;
        file >> line;

        m.emplace_back(line);
    }

    return m;
}

Map move(Map m){
    Map mm = m;
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m[i].size(); ++j) {
            if(m[i][j] != '>')
                continue;
            int jj = (j+1)%(m[i].size());
            if(m[i][jj] != '.')
                continue;
            mm[i][j] = '.';
            mm[i][jj] = '>';
        }
    }
    m = mm;
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m[i].size(); ++j) {
            if(m[i][j] != 'v')
                continue;
            int ii = (i+1)%(m.size());
            if(m[ii][j] != '.')
                continue;
            mm[i][j] = '.';
            mm[ii][j] = 'v';
        }
    }
    return mm;
}

void print(const Map& m){
    for(auto& s : m){
        cout << s << endl;
    }
    cout << endl;
}
int moveUntilFreez(Map m){
    Map last;
    int i = 0;
    do{
        last = m;
        m = move(m);
        i++;
        print(m);
    }while(m != last);
    return i;
}

int main(int argc, char** argv){
    string path = "../25/input.txt";
    auto map = openFile(path);

    print(map);

    int n = moveUntilFreez(map);

    cout << n << endl;
}