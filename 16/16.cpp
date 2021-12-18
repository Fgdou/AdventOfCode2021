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



class BitField{
private:
    string bits;
    long index;

public:
    explicit BitField(string& bits)
        : bits(bits), index(0){}
    long size(){
        return bits.size()-index;
    }

    long getNum(int nBits){
        if(nBits > size())
            throw runtime_error("Reach the end");

        long n = 0;
        for (int i = 0; i < nBits; ++i) {
            n <<= 1;
            n |= bits[index++] - '0';
        }
        return n;
    }
    long getPos() const{
        return index;
    }
};

struct Packet{
    long version;
    long type;
    long value;
    bool lengthTypeID;
    vector<Packet> subPackets;
};

string openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not open");

    vector<char> vec;
    string line;
    file >> line;
    return line;
}
string hexToBit(const string& str){
    static map<char, string> m = {
            {'0' , "0000"},
            {'1' , "0001"},
            {'2' , "0010"},
            {'3' , "0011"},
            {'4' , "0100"},
            {'5' , "0101"},
            {'6' , "0110"},
            {'7' , "0111"},
            {'8' , "1000"},
            {'9' , "1001"},
            {'A' , "1010"},
            {'B' , "1011"},
            {'C' , "1100"},
            {'D' , "1101"},
            {'E' , "1110"},
            {'F' , "1111"},
    };
    string bytes;
    for(char c : str){
        bytes += m[c];
    }

    return bytes;
}

Packet parsePacket(BitField& bits){
    Packet p;
    p.version = bits.getNum(3);
    p.type = bits.getNum(3);

    if(p.type == 4){
        bool stop = false;
        long n = 0;
        while(!stop){
            if(bits.getNum(1) == 0)
                stop = true;
            n <<= 4;
            n |= bits.getNum(4);
        }
        p.value = n;
    }else{
        p.lengthTypeID = bits.getNum(1);
        if(p.lengthTypeID == 0){
            long totalLength = bits.getNum(15);
            long toReach = bits.getPos() + totalLength;
            while(bits.getPos() < toReach){
                p.subPackets.emplace_back(parsePacket(bits));
            }
        }else{
            long nSubpackets = bits.getNum(11);
            for (int i = 0; i < nSubpackets; ++i) {
                p.subPackets.emplace_back(parsePacket(bits));
            }
        }
    }

    return p;
}

void print(Packet& p, string tabs = ""){

    cout << tabs << "Packet v" << p.version << " t" << p.type << " l" << p.subPackets.size() << endl;
    if(p.type == 4){
        cout << tabs << "\t" << p.value << endl;
    }else{
        for(auto& pp : p.subPackets)
            print(pp, tabs + "\t");
    }
}

long totalVersion(const Packet& p){
    long cnt = p.version;
    for(auto& pp : p.subPackets){
        cnt += totalVersion(pp);
    }
    return cnt;
}
long calculate(const Packet& p){
    if(p.type == 4) // VALUE
        return p.value;
    if(p.type == 0){ // SUM
        long sum = 0;
        for(auto& pp : p.subPackets)
            sum += calculate(pp);
        return sum;
    }
    if(p.type == 1){ // PRODUCT
        long product = 1;
        for(auto& pp : p.subPackets)
            product *= calculate(pp);
        return product;
    }
    if(p.type == 2){ // MIN
        long min = numeric_limits<long>::max();
        for(auto& pp : p.subPackets){
            long v = calculate(pp);
            if(v < min)
                min = v;
        }
        return min;
    }
    if(p.type == 3){ // MAX
        long max = 0;
        for(auto& pp : p.subPackets){
            long v = calculate(pp);
            if(v > max)
                max = v;
        }
        return max;
    }
    if(p.type == 5){ // GREATER
        return (calculate(p.subPackets[0]) > calculate(p.subPackets[1]));
    }
    if(p.type == 6){ // LESS
        return (calculate(p.subPackets[0]) < calculate(p.subPackets[1]));
    }
    if(p.type == 7){ // EQU
        return (calculate(p.subPackets[0]) == calculate(p.subPackets[1]));
    }
    throw runtime_error("Not founded any operations");
}

int main(int argc, char** argv){
    string path = "../16/input.txt";
    auto hex = openFile(path);
    auto bytes = hexToBit(hex);
    BitField buffer(bytes);

    cout << hex << endl;

    Packet p = parsePacket(buffer);
    print(p);

    cout << "Version: " << totalVersion(p) << endl;
    cout << "Operation: " << calculate(p) << endl;

}