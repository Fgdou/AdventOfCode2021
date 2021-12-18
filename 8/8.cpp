#include <vector>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Entry{
    vector<string> wires;
    vector<string> output;
};
typedef vector<Entry> Input;
typedef vector<string> DigitalSegement;
typedef map<char, char> CharMap;
typedef map<string, vector<int>> NumberMap;

vector<string> number_segments = {
        "abcefg",
        "cf",
        "acdeg",
        "acdfg",
        "bcdf",
        "abdfg",
        "abdefg",
        "acf",
        "abcdefg",
        "abcdfg"
};

void erase(string& str, char c){
    int pos = str.find(c);
    if(pos != -1)
        str.erase(pos, 1);
}

Input openFile(string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not open");

    Input in;

    string str;
    while(file.peek() != EOF){
        Entry e;

        for(int i=0; i<10; i++){
            file >> str;
            e.wires.emplace_back(str);
        }
        file >> str;
        for(int i=0; i<4; i++){
            file >> str;
            e.output.emplace_back(str);
        }
        in.emplace_back(e);
    }
    return in;
}
string complement(const string& pattern){
    string other = "abcdefg";
    for(auto c : pattern){
        erase(other, c);
    }
    return other;
}
void putPossibility(const string& num1, const string& pattern, DigitalSegement& segments, bool forced){
    string num2 = complement(num1);
    string neg = complement(pattern);

    for(char c : pattern){
        for(char p : num2){
            int pos = p-'a';
            erase(segments[pos], c);
        }
    }
    if(!forced)
        return;
    for(char c : neg){
        for(char p : num1){
            int pos = p-'a';
            erase(segments[pos], c);
        }
    }
}
NumberMap getNums(Entry& entity){
    NumberMap m;

    for(auto& str : entity.wires){
        vector<int> nums;
        for(int i=0; i<10; i++){
            string& num = number_segments[i];
            if(num.size() == str.size())
                nums.emplace_back(i);
        }
        m[str] = nums;
    }

    return m;
}

vector<int> count(vector<string> vec){
    vector<int> nums(7);
    for(string& str : vec){
        for(char c : str){
            nums[c-'a']++;
        }
    }

    return nums;
}
bool alone(vector<int>& vec, int n){
    int v = vec[n];
    for(int i=0; i<vec.size(); i++){
        if(i == n)
            continue;
        if(vec[i] == v)
            return false;
    }
    return true;
}
CharMap getChar(DigitalSegement& segment){
    CharMap map;
    for(int i=0; i<7; i++){
        map[segment[i][0]]=i+'a';
    }
    return map;
}
int findNum(string& pattern){
    for(int i=0; i<number_segments.size(); i++){
        auto& str = number_segments[i];
        if(pattern.size() != str.size())
            continue;
        bool founded = true;
        for(char c : pattern){
            if(str.find(c) == -1) {
                founded = false;
                break;
            }
        }
        if(founded){
            return i;
        }
    }
    throw runtime_error("Not found");
}

DigitalSegement fillSegments(Entry& e){
    DigitalSegement seg;
    for(int i=0; i<7; i++)
        seg.emplace_back("abcdefg");

    auto total = count(number_segments);
    auto cnt = count(e.wires);

    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++) {
            if (total[i] == cnt[j]) {
                if (alone(total, i)) {
                    seg[i] = j + 'a';
                    for(int nn = 0; nn<7; nn++){
                        if(nn == i)
                            continue;
                        erase(seg[nn], j+'a');
                    }
                }
            }
        }
    }

    return seg;
}
string getCoverage(vector<int>& nums){
    string str;

    for(int n : nums){
        for(char c : number_segments[n]){
            if(str.find(c) == -1)
                str += c;
        }
    }
    return str;
}

void print(DigitalSegement& seg){
    cout << "  " << seg[0] << endl;
    cout << seg[1] << '\t' << seg[2] << endl;
    cout << "  " << seg[3] << endl;
    cout << seg[4] << '\t' << seg[5] << endl;
    cout << "  " << seg[6] << endl << endl;
}
bool check(DigitalSegement& d){
    for(auto& str : d){
        if(str.size() != 1)
            return false;
    }
    return true;
}

int decodeLine(Entry& e){

    auto nums = getNums(e);

    DigitalSegement segments = fillSegments(e);

    print(segments);
    while(!check(segments)) {
        for (auto &e : nums) {
            const string &pattern = e.first;
            string coverage = getCoverage(e.second);
            putPossibility(coverage, pattern, segments, e.second.size() == 1);
            print(segments);
        }
    }

    auto charmap = getChar(segments);
    int sum = 0;
    for(string str : e.output){
        for(char& c : str){
            c = charmap[c];
        }
        int n = findNum(str);
        sum *= 10;
        sum += n;
    }

    return sum;
}

int main(int argc, char** argv){
    string path = "../8/example.txt";
    auto input = openFile(path);

    int sum = 0;
    for(auto& e : input){
        sum += decodeLine(e);
    }
    cout << sum << endl;
}