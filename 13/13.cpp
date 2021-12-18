//
// Created by fgdou on 12/13/21.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

struct Point{
    int x,y;
};
struct Instruction{
    char axis;
    int index;
};
struct Input{
    vector<Point> points;
    vector<Instruction> instructions;
};
Input openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not open");

    Input i{};

    string line;
    char l[50];

    file.getline(l, 50);
    line.assign(l);
    while(!line.empty()){
        auto founded = line.find(',');
        string sx = line.substr(0, founded);
        string sy = line.substr(founded+1);

        Point p = {stoi(sx), stoi(sy)};

        i.points.emplace_back(p);

        file.getline(l, 50);
        line.assign(l);
    }
    while(file.peek() != EOF){
        char l[50];
        file.getline(l, 50);
        line.assign(l);

        string sindex = line.substr(13);

        Instruction instru;//TODO
        instru.axis = line[11];
        instru.index = stoi(sindex);

        i.instructions.emplace_back(instru);
    }

    return i;
}

Point getSize(const vector<Point>& tab){
    Point p{};
    for(auto& pp : tab){
        if(pp.x > p.x)
            p.x = pp.x;
        if(pp.y > p.y)
            p.y = pp.y;
    }
    p.x++;
    p.y++;
    return p;
}
void printTab(const vector<Point>& tab){
    auto size = getSize(tab);
    vector<bool> v(size.y*size.x);

    for(auto p : tab){
        v[p.y*size.x + p.x] = true;
    }

    int cnt = 0;
    for (int i = 0; i < size.y; ++i) {
        for (int j = 0; j < size.x; ++j) {
            cout << ((v[i*size.x + j]) ? '#' : '.');
            if(v[i*size.x + j])
                cnt++;
        }
        cout << endl;
    }
    cout << cnt << endl << endl;
}

vector<Point> fold(const vector<Point>& tab, Instruction& instruction){
    vector<Point> vec;
    vec.reserve(tab.size());

    for(const auto& p : tab){
        if(instruction.axis == 'x'){
            if(p.x < instruction.index)
                vec.emplace_back(p);
            else
                vec.push_back({2*instruction.index - p.x, p.y});
        }else{
            if(p.y < instruction.index)
                vec.emplace_back(p);
            else
                vec.push_back({p.x, 2*instruction.index - p.y});
        }
    }

    return vec;
}

int main(int argc, char** argv){
    string path = "../13/input.txt";
    auto input = openFile(path);

    auto tab = input.points;
    printTab(tab);

    for(auto i : input.instructions){
        tab = fold(tab, i);
        printTab(tab);
    }
}