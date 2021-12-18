//
// Created by projector-user on 12/5/21.
//

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

typedef vector<int> Plate;
typedef vector<int> Input;

vector<int> split(string& line, char c){
    vector<int> res;

    int start = 0;

    int founded = line.find(c, start);

    while(founded != string::npos){
        string s = line.substr(start, founded-start);
        res.push_back(stoi(s));

        start = founded+1;
        founded = line.find(c, start);
    }

    string s = line.substr(start);
    res.push_back(stoi(s));

    return res;
}

void openFile(string& path, vector<Plate>& plates, Input& numbers){
    ifstream file;
    file.open(path);

    if(!file.is_open())
        throw runtime_error("File not open");

    string snumbers;
    file >> snumbers;

    numbers = split(snumbers, ',');

    //parse numbers
    char buff[50];
    string line;
    file.getline(buff, 50);
    file.getline(buff, 50);

    Plate p;

    while(file.peek() != EOF){
        file.getline(buff, 50);
        line.assign(buff);
        if(line.empty()){
            plates.push_back(p);
            p.clear();
        }else{
            auto nums = split(line, ' ');
            for(auto n : nums)
                p.push_back(n);
        }
    }
    plates.push_back(p);
}

void addNumber(vector<Plate>& plates, int n, vector<vector<bool>>& bools){
    for(int i=0; i<plates.size(); i++){
        Plate& p = plates[i];
        for(int j=0; j<p.size(); j++){
            int nn = p[j];
            if(nn == n)
                bools[i][j] = true;
        }
    }
}

bool checkH(vector<bool>&plate){
    for(int y=0; y<5; y++){
        bool flag = true;
        for(int x=0; x<5; x++){
            if(!plate[y*5+x]){
                flag = false;
                break;
            }
        }
        if(flag)
            return true;
    }
    return false;
}
bool checkV(vector<bool>&plate){
    for(int x=0; x<5; x++){
        bool flag = true;
        for(int y=0; y<5; y++){
            if(!plate[y*5+x]){
                flag = false;
                break;
            }
        }
        if(flag)
            return true;
    }
    return false;
}
int checkWinners(vector<vector<bool>>& plates){
    for(int i=0; i<plates.size(); i++){
        vector<bool>& p = plates[i];

        bool win = checkH(p) || checkV(p);
        if(win)
            return i;
    }
    return -1;
}
int getSum(Plate& vec, vector<bool>& bools){
    int n = 0;
    for(int i=0; i<vec.size(); i++) {
        if(!bools[i])
            n += vec[i];
    }
    return n;
}

template <typename T>
vector<T> deletePlate(vector<T>& plates, int n){
    vector<T> vec;

    for(int i=0; i<plates.size(); i++){
        if(i != n)
            vec.push_back(plates[i]);
    }
    return vec;
}

int main(int argc, char** argv){
    string path = "../4/input.txt";
    vector<Plate> plates;
    Input input;

    openFile(path, plates, input);


    int index = 0;

    vector<vector<bool>> bools;
    for(int i=0; i<plates.size(); i++){
        vector<bool> v(plates[0].size());
        bools.emplace_back(v);
    }

    int n;
    int restToWin = plates.size();

    Plate winPlate;
    vector<bool> winBool;

    int win;
    while(restToWin > 0 && index < input.size()){
        n = input[index];
        addNumber(plates, n, bools);
        win = 0;
        while(win != -1) {
            win = checkWinners(bools);
            if (win != -1) {
                restToWin--;
                winPlate = plates[win];
                winBool = bools[win];
                plates = deletePlate(plates, win);
                bools = deletePlate(bools, win);
            }
        }
        index++;
    }

    if(index >= input.size()){
        winPlate = plates[0];
        winBool = bools[0];
    }

    int sum = getSum(winPlate, winBool) * n;

    cout << win << " win\n";
    cout << sum << endl;
}