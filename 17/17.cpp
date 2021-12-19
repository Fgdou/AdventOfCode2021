//
// Created by projector-user on 12/17/21.
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


using namespace std;

struct Point{
    long x, y;
    bool operator==(const Point& other) const{
        return x == other.x && y == other.y;
    }
    Point& operator+=(const Point& other){
        x += other.x;
        y += other.y;
        return *this;
    }
};

struct Rect{
    Point p1, p2;

    bool isIn(const Point& p){
        return (p.x >= p1.x && p.x <= p2.x && p.y >= p1.y && p.y <= p2.y);
    }
};

Rect openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not opened");

    char line[50];
    file.getline(line, 50);

    Rect r;

    sscanf(line, "target area: x=%ld..%ld, y=%ld..%ld", &r.p1.x, &r.p2.x, &r.p1.y, &r.p2.y);

    return r;
}

long getMax(const vector<Point>& p){
    long max = 0;
    for(auto& pp : p){
        if(pp.y > max)
            max = pp.y;
    }
    return max;
}
void print(Rect rect, const vector<Point>& points){
    long yMax = getMax(points);
    long yMin = rect.p1.y;
    long xMax = rect.p2.x;
    long xMin = 0;

    for(long i=yMax; i>=yMin; i--){
        for (long j = xMin; j <= xMax; ++j) {
            Point pp = {j, i};

            if(i == 0 && j == 0)
                cout << "S";
            else if(find(points.begin(), points.end(), pp) != points.end())
                cout << "#";
            else if(rect.isIn(pp))
                cout << "T";
            else
                cout << ".";
        }
        cout << endl;
    }
    cout << endl;
}

Point findVelocity(const Rect& rect){
    long x = sqrt(2*rect.p1.x);
    long y = -rect.p1.y-1;

    return {x, y};
}
bool simulate(Rect rect, Point v, vector<Point>& points, bool printTo = false){
    Point a = {-1, -1};
    Point d = {0,0};

    while(!rect.isIn(d)){
        d += v;
        v += a;

        if(v.x < 0)
            v.x = 0;

        points.emplace_back(d);

        if(printTo)
          print(rect, points);

        if(d.x > rect.p2.x || d.y < rect.p1.y) {
            return false;
        }
    }
    return true;
}

vector<int> findXWithY(Rect rect, long y){
    Point v = {0, y};

    vector<int> xs;

    while(true){
        vector<Point> points;
        if(simulate(rect, v, points)){
            xs.emplace_back(v.x);
        }
        v.x++;

        if(v.x > rect.p2.x)
            break;
    }
    return xs;
}
vector<Point> getVelocities(Rect rect){
    vector<Point> res;
    for(long y = rect.p1.y; y<-rect.p1.y; y++){
        auto xs = findXWithY(rect, y);
        for(auto x : xs){
            res.push_back({x, y});
        }
    }
    return res;
}

int main(int argc, char** argv){
    string path = "../17/input.txt";
    auto rect = openFile(path);

    auto vec = getVelocities(rect);
    cout << "Size : " << vec.size() << endl;
    for(auto p : vec){
        cout << "\t" << p.x << "," << p.y << endl;
    }
}
