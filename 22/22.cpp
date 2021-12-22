//
// Created by fgdou on 12/22/21.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stack>
#include <map>

using namespace std;

struct Point{
    long x, y, z;
};
struct Interval{
    long left, right;

    long length() const{
        return abs(right - left)+1;
    }
};
struct Cube{
    Interval x, y, z;
    bool on;

    long size() const{
        return x.length()*y.length()*z.length();
    }
    bool intersect(const Cube& c1) const{
        return
                c1.x.right > x.left && c1.x.left < x.right &&
                c1.y.right > y.left && c1.y.left < y.right &&
                c1.z.right > z.left && c1.z.left < z.right
                ;
    }
    bool inside(const Point& p) const{
        return p.x >= x.left && p.x <= x.right &&
               p.y >= y.left && p.y <= y.right &&
               p.z >= z.left && p.z <= z.right;
    }
    Cube intersection(const Cube& c1) const{
        vector<long> xx = {c1.x.left, c1.x.right, x.left, x.right};
        vector<long> yy = {c1.y.left, c1.y.right, y.left, y.right};
        vector<long> zz = {c1.z.left, c1.z.right, z.left, z.right};

        sort(xx.begin(), xx.end());
        sort(yy.begin(), yy.end());
        sort(zz.begin(), zz.end());

        return {
                {xx[1], xx[2]},
                {yy[1], yy[2]},
                {zz[1], zz[2]}
        };
    }
};

bool getPoint(Point& p, const vector<Cube>& cubes){
    bool state = false;
    for(auto& cube : cubes){
        if(cube.inside(p))
            state = cube.on;
    }
    return state;
}
long cntOn(Cube c, const vector<Cube>& cubes){
    long cnt = 0;
    for (int x = c.x.left; x <= c.x.right; ++x) {
        for (int y = c.y.left; y <= c.y.right; ++y) {
            for (int z = c.z.left; z <= c.z.right; ++z) {
                Point p = {x, y, z};
                bool state = getPoint(p, cubes);
                if(state)
                    cnt++;
            }
        }
    }
    return cnt;
}

vector<Cube> add(const vector<Cube>& vec, Cube c){
    vector<Cube> res = vec;

    if(c.on)
        res.emplace_back(c);

    for(auto& cube : vec){
        if(c.intersect(cube)){

            Cube inter = c.intersection(cube);
            inter.on = !cube.on;
            res.emplace_back(inter);
        }
    }

    return res;
}

void print(const vector<Cube>& vec, Cube& c){
    for (int x = c.x.left; x <= c.x.right; ++x) {
        for (int y = c.y.left; y <= c.y.right; ++y) {
            bool finded = false;
            Point p = {x, y, 10};
            if(getPoint(p, vec))
                finded = true;
            cout << ((finded) ? '#' : '.');
        }
        cout << endl;
    }
    cout << endl;
}

long count(const vector<Cube>& cubes){
    long cnt = 0;
    for(auto& cube : cubes){
        if(cube.on)
            cnt += cube.size();
        else
            cnt -= cube.size();
    }
    return cnt;
}
vector<Cube> openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not open");
    
    vector<Cube> vec;
    char line[100];
    while(file.peek() != EOF){
        file.getline(line, 100);
        
        Cube c{};
        char onoff[5];
        sscanf(line, "%s x=%ld..%ld,y=%ld..%ld,z=%ld..%ld", onoff, &c.x.left, &c.x.right, &c.y.left, &c.y.right, &c.z.left, &c.z.right);

        string onoffs;
        onoffs.assign(onoff);
        if(onoffs == "on")
            c.on = true;
        vec.emplace_back(c);
    }

    return vec;
}
vector<Cube> getAll(const vector<Cube>& cubes){
    vector<Cube> res;
    for (auto& cube : cubes) {
        res = add(res, cube);
    }
    return res;
}

int main(int argc, char** argv){
    string path = "../22/input.txt";
    auto cubes = openFile(path);

    //Interval i = {0, 20};
    //Cube c = {i, i, i};
    //print(cubes, c);
    auto ccubes = getAll(cubes);
    auto cnt = count(ccubes);

    //print(ccubes, c);

    //cout << cntOn(c, cubes) << endl;
    cout << cnt << endl;
}
//2758514936282235
//39769145051327


