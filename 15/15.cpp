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

typedef vector<vector<bool>> Bool;
typedef vector<vector<int>> Tab;
struct Point{
    int x,y;
    bool operator==(const Point& other) const{
        return x == other.x && y == other.y;
    }
    bool operator<(const Point& other) const{
        return (x<other.x) || (x == other.x && y < other.y);
    }
};

const vector<Point> moves = {
        {1, 0}, {0, 1}, {-1, 0},{0, -1}
};



Tab openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not open");

    Tab tab;

    string line;

    while(file.peek() != EOF){
        file >> line;

        vector<int> v;
        for(char c : line){
            v.push_back(c-'0');
        }
        tab.emplace_back(v);
    }

    return tab;
}

template <typename T>
void print(const vector<vector<T>>& vec){
    for(auto& v : vec){
        for(auto c : v){
            if(c != numeric_limits<int>::max())
                cout << 'X';
            else
                cout << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

auto cmp = [](const pair<int, Point>& p1, const pair<int, Point>& p2){return p1.first > p2.first;};

int resolve(Tab& tab, Point start, Point end){
    priority_queue<pair<int, Point>, vector<pair<int, Point>>, decltype(cmp)> queue(cmp);

    vector<vector<int>> values;
    for (int i = 0; i < tab.size() * 5; ++i) {
        values.emplace_back();
        for(int j = 0; j < tab[0].size() * 5; ++j) {
            values[i].push_back(numeric_limits<int>::max());
        }
    }

    queue.push(make_pair(0,start));

    int cnt = 0;
    while(!queue.empty()){
        cnt++;
        if(cnt%10000 == 0)
            cout << queue.size() << endl;

        //sort(queue.begin(), queue.end(), [](const pair<int, Point>& p1, const pair<int, Point>& p2){return p1.first > p2.first;});

        auto p = queue.top();
        queue.pop();

        Point pp = p.second;

        if(pp.x < 0 || pp.x >= tab[0].size()*5 || pp.y < 0 || pp.y >= tab.size()*5)
            continue;

        int value = tab[pp.y%tab.size()][pp.x%tab[0].size()] + pp.y/tab.size() + pp.x/tab[0].size();
        value = (value-1)%9+1;

        value += p.first;

        if(value >= values[pp.y][pp.x])
            continue;
        values[pp.y][pp.x] = value;

        if(pp == end)
            break;

        for(auto& move : moves){
            Point ppp = {pp.x+move.x, pp.y+move.y};
            queue.push(make_pair(value, ppp));
        }
    }

    return values[end.y][end.x] - values[start.y][start.x];
}


int main(int argc, char** argv){
    string path = "../15/input.txt";
    auto tab = openFile(path);

    cout << resolve(tab, {0,0}, {static_cast<int>(tab.size()*5)-1, static_cast<int>(tab[0].size()*5)-1}) << endl;
}

//398
//2824
//2817