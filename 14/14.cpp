#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

struct Input{
    string line;
    map<string, string> m;
};

typedef map<string, long> pairCount;

Input openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not opened");

    Input i;

    char buff[50];
    string line;
    file.getline(buff, 50);
    i.line.assign(buff);
    file.getline(buff, 50);

    while(file.peek() != EOF){
        file.getline(buff, 50);
        line.assign(buff);

        string left = line.substr(0, 2);
        string right = line.substr(6);

        i.m[left] = right;
    }
    return i;
}

// Part 1
map<char, int> countLetters1(string& str){
    map<char, int> count;
    for(char c : str){
        count[c]++;
    }
    return count;
}
long getScore1(map<char, int>& m){
    int min = numeric_limits<int>::max();
    int max = 0;

    for(auto& p : m){
        if(p.second > max)
            max = p.second;
        if(p.second < min)
            min = p.second;
    }

    return max - min;
}
string transform1(const string& line, const map<string, string>& m){
    string newline;
    for (int i = 0; i < line.size() - 1; ++i) {
        const string sub = line.substr(i, 2);
        newline += sub[0];
        if(m.find(sub) != m.end()){
            newline += m.at(sub);
        }
    }
    newline += line[line.size()-1];

    return newline;
}

pairCount getPairs(string& line){
    pairCount pc;
    for(int i=0; i<line.size()-1; i++){
        string sub = line.substr(i, 2);
        pc[sub]++;
    }
    return pc;
}
pairCount transform2(pairCount& pc, map<string, string>& m, map<char, long>& counter){
    pairCount res;
    for(auto& p : pc){
        string& target = m[p.first];
        string p1 = p.first[0] + target;
        string p2 = target + p.first[1];

        res[p1] += p.second;
        res[p2] += p.second;

        counter[target[0]] += p.second;
    }

    return res;
}
long getScore2(map<char, long>& m){
    long min = numeric_limits<long>::max();
    long max = 0;

    for(auto& p : m){
        if(p.second > max)
            max = p.second;
        if(p.second < min)
            min = p.second;
    }

    return max - min;
}
map<char, long> countChars(string& line){
    map<char, long> c;
    for(auto i : line)
        c[i]++;
    return c;
}

int main(int argc, char** argv){
    string path = "../14/input.txt";
    auto input = openFile(path);

    string line = input.line;
    auto cntPairs = getPairs(line);
    auto cntChars = countChars(line);

    cout << line << endl;

    for (int i = 0; i < 40; ++i) {
        cntPairs = transform2(cntPairs, input.m, cntChars);
    }

    auto score = getScore2(cntChars);

    cout << score << endl;
}
// 3247