#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

typedef vector<vector<int>> Tab;
struct Point{
    int x,y;
};

Tab openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not open");

    Tab tab;
    while(file.peek() != EOF){
        string line;
        file >> line;

        vector<int> l;
        for(char c : line){
            l.push_back(c - '0');
        }
        tab.emplace_back(l);
    }

    return tab;
}

void increase(Tab& tab){
    for(auto& line : tab){
        for(auto& i : line)
            i++;
    }
}
int flash(const Point& p, Tab& tab, bool add = false){
    if(p.x < 0 || p.x >= tab[0].size())
        return 0;
    if(p.y < 0 || p.y >= tab.size())
        return 0;

    int& v = tab[p.y][p.x];

    if(v == 0)
        return 0;

    if(add)
        v++;

    if(v <= 9)
        return 0;
    v = 0;

    int sum = 1;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if(i == 0 && j == 0)
                continue;

            Point newP = {p.x+j, p.y+i};
            sum += flash(newP, tab, true);
        }
    }

    return sum;
}
void print(Tab& tab){
    for (auto& line : tab) {
        for(auto& v : line){
            cout << v;
        }
        cout << endl;
    }
    cout << endl;
}

int step(Tab& tab){
    increase(tab);
    int sumFlashes = 0;
    for (int i = 0; i < tab.size(); ++i) {
        for (int j = 0; j < tab[i].size(); ++j) {
            sumFlashes += flash({j, i}, tab);
        }
    }
    print(tab);
    return sumFlashes;
}
bool allFlash(Tab& tab){
    for(auto& line : tab)
        for(auto v : line)
            if(v != 0)
                return false;
    return true;
}
int indexAllFlash(Tab& tab){
    int i=0;
    while(!allFlash(tab)){
        step(tab);
        i++;
    }
    return i;
}

int main(int argc, char** argv){
    string path = "../11/input.txt";
    auto lines = openFile(path);
    auto copy = lines;

    print(lines);

    int N = 100;

    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += step(lines);
    }

    cout << sum << endl;

    int index = indexAllFlash(copy);

    cout << index << endl;
}
//1705
//265