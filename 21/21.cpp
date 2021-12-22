#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stack>
#include <map>


using namespace std;

const int SCORE_WIN = 21;
const int DICE_SIZE = 100;
const int TRACK_SIZE = 10;


struct Player{
    int score;
    int pos;

    bool operator<(const Player& other) const{
        return (score < other.score || score == other.score && pos < other.pos);
    }
};
typedef vector<long> Win;

typedef vector<Player> Game;

vector<Player> openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not opened");

    vector<Player> vec;

    char line[50];
    while(file.peek() != EOF){
        file.getline(line, 50);

        int player, pos;
        sscanf(line, "Player %d starting position: %d", &player, &pos);

        vec.push_back({0, pos});
    }
    return vec;
}

void addWin(Win& target, const Win& add){
    for (int i = 0; i < target.size(); ++i) {
        target[i] += add[i];
    }
}

Win cntWin(Game& g, int player, map<pair<int, Game>, Win>& map){
    Win w(g.size());

    player = player%((int)g.size());

    if(map.find(make_pair(player, g)) != map.end())
        return map[make_pair(player, g)];

    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            for (int k = 1; k <= 3; ++k) {
                Game gg = g;
                gg[player].pos = (gg[player].pos+i+j+k-1)%TRACK_SIZE+1;
                gg[player].score += gg[player].pos;

                //cout << player << ' ' << i << ' ' << gg[player].score << endl;

                if(gg[player].score >= SCORE_WIN)
                    w[player]++;
                else{
                    auto list = cntWin(gg, player+1, map);
                    addWin(w, list);
                }
            }
        }
    }

    map[make_pair(player, g)] = w;

    return w;
}

int main(int argc, char** aargv){
    string path = "../21/input.txt";
    Game game = openFile(path);

    map<pair<int, Game>, Win> m;
    auto win = cntWin(game, 0, m);

    for(auto& p : win)
        cout << p << endl;
}
//272847859601291