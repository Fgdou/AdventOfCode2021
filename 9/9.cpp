//
// Created by projector-user on 12/9/21.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> Tab;

struct Point{
    int x, y;
};

Tab openFile(string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not opened");

    Tab vec;
    while(file.peek() != EOF){
        vector<int> v;
        string line;
        file >> line;

        for(char c : line)
            v.emplace_back(c-'0');

        vec.emplace_back(v);
    }

    return vec;
}

vector<Point> getLower(Tab& tab){
    vector<Point> res;

    for(int i=0; i<tab.size(); i++){
        for(int j=0; j<tab[i].size(); j++){
            int n = tab[i][j];

            if(i>0 && tab[i-1][j] <= n)
                continue;
            if(i<tab.size()-1 && tab[i+1][j] <= n)
                continue;
            if(j>0 && tab[i][j-1] <= n)
                continue;
            if(j<tab[i].size()-1 && tab[i][j+1] <= n)
                continue;

            res.push_back({j, i});
        }
    }
    return res;
}
int sumRisk(vector<int>& vec){
    int n = 0;
    for(auto c : vec){
        n += c+1;
    }
    return n;
}
bool pointPresent(vector<Point>& vec, Point p){
    for(Point& e : vec){
        if(e.x == p.x && e.y == p.y)
            return true;
    }
    return false;
}

void print(vector<Point>& vec, Tab& tab){
    for(int i=0; i<tab.size(); i++){
        for(int j=0; j<tab[i].size(); j++){
            if(pointPresent(vec, {j, i}))
                cout << tab[i][j];
            else
                cout << '.';
        }
        cout << endl;
    }
    cout << endl;
}
int cntBassin(int n, Point p, vector<Point>& used, Tab& tab){
    if(p.x < 0 || p.x >= tab[0].size())
        return 0;
    if(p.y < 0 || p.y >= tab.size())
        return 0;


    if(tab[p.y][p.x] < n )//&& tab[p.y][p.x] != n+1
        return 0;
    if(tab[p.y][p.x] == 9)
        return 0;
    if(pointPresent(used, p))
        return 0;
    used.emplace_back(p);

    int cnt = 0;
    vector<Point> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for(Point m : moves){
        cnt += cntBassin(tab[p.y][p.x], {p.x+m.x, p.y+m.y}, used, tab);
    }

    return cnt+1;
}
vector<int> getSizeBassins(const vector<Point>& vec, Tab& tab){
    vector<int> res;
    for(auto& p : vec){
        int height = tab[p.y][p.x];
        vector<Point> s;
        int size = cntBassin(height, p, s, tab);
        print(s, tab);
        res.emplace_back(size);
    }
    sort(res.begin(), res.end(), [](int a, int b){return a > b;});

    return res;
}


int main(int argc, char** argv){
    string path = "../9/input.txt";
    auto input = openFile(path);

    auto lower = getLower(input);

    auto size = getSizeBassins(lower, input);

    cout << size[0] * size[1] * size[2] << endl;

}

//685216
//685216
//685216
//457164
//987840