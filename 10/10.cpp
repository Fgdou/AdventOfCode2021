//
// Created by fgdou on 12/10/21.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <stack>

using namespace std;

map<char, char> m = {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'},
        {'<', '>'}
};
map<char, int> scores = {
        {')', 3},
        {']', 57},
        {'}', 1197},
        {'>', 25137}
};
map<char, int> scoresClosing = {
        {')', 1},
        {']', 2},
        {'}', 3},
        {'>', 4}
};

vector<string> openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not open");

    vector<string> lines;
    while(file.peek() != EOF){
        string line;
        file >> line;
        lines.push_back(line);
    }
    return lines;
}

bool isOpenChar(char c){
    return m.find(c) != m.end();
}

long getFinalScore(stack<char> memory){
    long score = 0;
    while(!memory.empty()){
        char c = memory.top();
        memory.pop();

        score *= 5;
        score += scoresClosing[c];
    }
    return score;
}

int lineError(const string& line, stack<char>& memory){
    for(int i=0; i<line.size(); i++){
        char c = line[i];

        if(isOpenChar(c)){
            memory.push(m[c]);
        }else{
            char expected = memory.top();
            memory.pop();

            if(c != expected)
                return i;
        }
    }
    return -1;
}

int main(int argc, char** argv){
    string path = "../10/input.txt";
    auto lines = openFile(path);

    int totalScore = 0;
    vector<long> finalScores;

    for(auto& line : lines){
        stack<char> memory;

        int index = lineError(line, memory);
        if(index == -1) {
            long finalScore = getFinalScore(memory);
            cout << line << ' ' << finalScore << endl;
            finalScores.push_back(finalScore);
        }

        char c = line[index];
        int score = scores[c];

        totalScore += score;

        cout << line << ' ' << index << ' ' << c << ' ' << score << endl;
    }
    cout << endl << totalScore << endl;

    sort(finalScores.begin(), finalScores.end());
    long final = finalScores[finalScores.size()/2];
    cout << final << endl;
}