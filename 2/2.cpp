#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef pair<string, int> Move;
typedef vector<Move> Moves;
typedef struct{
    int h;
    int depth;
    int aim;
} Pos;

Moves read(string& path){
    ifstream file;
    file.open(path);

    if(!file.is_open())
        throw runtime_error("File not open");

    Moves vec;
    while(file.peek() != EOF){
        pair<string, int> p;
        file >> p.first >> p.second;
        vec.push_back(p);
    }
    return vec;
}
void addToPos(Pos& pos, Move& m){
    if(m.first == "forward") {
        pos.h += m.second;
        pos.depth += pos.aim*m.second;
    }
    else if(m.first == "down")
        pos.aim += m.second;
    else if(m.first == "up")
        pos.aim -= m.second;
}
void addToPos(Pos& pos, Moves& moves){
    for(auto& move : moves)
        addToPos(pos, move);
}

int main(int argc, char** argv){
    string path = "../2/input.txt";

    auto moves = read(path);

    Pos p = {0, 0};
    addToPos(p, moves);

    int ans1 = p.h*p.depth;
    cout << "1: " << ans1 << endl;
}