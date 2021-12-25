//
// Created by fgdou on 12/23/21.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <map>
#include "Board.h"
#include <queue>

using namespace std;

typedef pair<pair<int, int>, vector<Board>> ppr;

auto cmp = [](const ppr& p1, const ppr& p2){
    return p1.first.first < p2.first.first || p1.first.first == p2.first.first && p1.first.second > p2.first.second;
    //return p1.first.second > p2.first.second;
};
typedef priority_queue<ppr, vector<ppr>, decltype(cmp)> Prio;

Board openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not opened");

    Board b;

    string tmp;
    char c;
    file >> tmp;

    for (int y = 0; y < 3; ++y) {
        file >> c;
        for (int x = 0; x < 11; ++x) {
            file >> c;

            Point p = {x, y};

            if(b.isCell(p))
                b.setCell(p, c);
        }
        file >> c;
    }

    return b;
}

int getLeast(Board& b){
    Prio prio(cmp);
    prio.push(make_pair(make_pair(0, 0), vector<Board>{b}));

    while(!prio.empty()){
        vector<Board> vec = prio.top().second;
        auto bb = vec[vec.size()-1];
        auto cost = prio.top().first.second;
        prio.pop();

        if(bb.hasWin()) {
            for(auto& bbbb : vec){
                bbbb.print();
            }
            return cost;
        }

        //bb.print();

        auto list = bb.getPossibleMoves();
        for(auto e : list){
            Board bbb = bb;

            //bbb.print();
            int m = bbb.move(e.first, e.second);
            //cout << m << ' ' << m+cost << endl;
            //bbb.print();
            if(m < 0)
                continue;

            vector<Board> vec2 = vec;
            vec2.emplace_back(bbb);

            prio.push(make_pair(make_pair(bbb.getPoints(), m+cost), vec2));
        }
    }
    return -1;
}

int main(int argc, char** argv){
    string path = "../23/input.txt";
    auto board = openFile(path);

    auto list = board.getPossibleMoves();

    cout << getLeast(board) << endl;

}
//19736
//15716
//21130
//15716