//
// Created by projector-user on 12/5/21.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Vec{
    int x, y;
};
struct Line{
    Vec p1, p2;
};

vector<Line> openFile(string& path){
    fstream file;
    file.open(path);

    if(!file.is_open())
        throw runtime_error("File not open");

    vector<Line> lines;

    while(file.peek() != EOF){
        char str[40];

        file.getline(str, 40);
        if(string(str).empty())
            break;

        int x1, y1, x2, y2;
        sscanf(str, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);

        Line l = {{x1, y1}, {x2, y2}};
        lines.emplace_back(l);
    }

    return lines;
}
vector<Vec> createLine(Line l){
    vector<Vec> vec;
    int dx=0, dy=0;

    if(l.p1.x < l.p2.x)
        dx = +1;
    else if(l.p1.x > l.p2.x)
        dx = -1;

    if(l.p1.y < l.p2.y)
        dy = +1;
    else if(l.p1.y > l.p2.y)
        dy = -1;

    //if(dx != 0 && dy != 0)
    //    return vec;

    int x = l.p1.x;
    int y = l.p1.y;


    while(x != l.p2.x || y != l.p2.y){
        vec.push_back({x, y});
        x += dx;
        y += dy;
    }
    vec.push_back({x, y});

    return vec;
}

Vec getMax(vector<Line>& lines){
    int xMax=0, yMax=0;
    for(Line l : lines){
        int x = l.p1.x;
        int y = l.p1.y;

        if(x > xMax)
            xMax = x;
        if(y > yMax)
            yMax = y;

        x = l.p2.x;
        y = l.p2.y;

        if(x > xMax)
            xMax = x;
        if(y > yMax)
            yMax = y;
    }
    return {xMax+1, yMax+1};
}

vector<vector<int>> createMap(vector<Line>& lines){
    Vec max = getMax(lines);

    vector<vector<int>> vec;
    for(int i=0; i<max.y; i++){
        vector<int> v(max.x);
        vec.emplace_back(v);
    }


    for(Line l : lines){
        auto points = createLine(l);

        for(Vec v : points){
            vec[v.y][v.x]++;
        }
    }

    return vec;
}
int cntOverlap(vector<vector<int>>& vec){
    int cnt = 0;
    for(auto& v : vec){
        for(auto n : v){
            if(n >= 2)
                cnt++;
        }
    }
    return cnt;
}
void print(vector<vector<int>>& vec){
    for(auto& v : vec){
        for(auto n : v){
            if(n == 0)
                cout << "  ";
            else
                cout << n << ' ';
        }
        cout << endl;
    }
}

int main(int argc, char** argv){
    string path = "../5/input.txt";
    auto lines = openFile(path);
    auto map = createMap(lines);

    print(map);

    int cnt = cntOverlap(map);

    cout << cnt << endl;
}