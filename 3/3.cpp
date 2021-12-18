//
// Created by projector-user on 12/3/21.
//

#include <vector>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

vector<int> readFile(string& path, int& size){
    ifstream file;
    file.open(path);

    if(!file.is_open())
        throw runtime_error("Cannot open file");

    vector<int> vec;
    while(file.peek() != EOF){
        string line;
        file >> line;

        if(line.empty())
            continue;
        size = line.size();

        int n = 0;
        for(char c : line){
            n <<= 1;
            if(c == '1')
                n++;
        }
        vec.push_back(n);
    }
    return vec;
}

int getGamma(vector<int>& nums, int size){
    vector<int> vec(size);

    for(int n : nums){
        for(int i=0; i<size; i++){
            if(n&1)
                vec[i]++;
            n >>= 1;
        }
    }

    int gamma = 0;
    for(int i=0; i<size; i++){
        if(vec[i] > nums.size()/2)
            gamma |= 1 << i;
    }
    return gamma;
}
int getEpsilon(int gamma, int size){
    int mask = 0;
    for(int i=0; i<size; i++){
        mask <<= 1;
        mask++;
    }

    return gamma^mask;
}
int getEnergy(int gamma, int epsilon){
    return gamma*epsilon;
}

int getBitCriteria(vector<int>& nums, int index, bool oxygen){
    int n = 0;
    for(int num : nums){
        if(num&(1<<index))
            n++;
    }
    if(oxygen){
        return n*2 >= nums.size();
    }else{
        return n*2 < nums.size();
    }
}
vector<int> filter(vector<int>& nums, int bit, int index){
    vector<int> vec;

    for(int n : nums){
        if(((n >> index)&1) == bit)
            vec.push_back(n);
    }

    return vec;

}

int main(int argc, char** argv){
    int size;
    string path = "../3/input.txt";
    auto nums = readFile(path, size);

    int gamma = getGamma(nums, size);
    int epsilon = getEpsilon(gamma, size);
    int energy = getEnergy(gamma, epsilon);

    cout << gamma << endl;
    cout << epsilon << endl;
    cout << energy << endl << endl;

    vector<int> vecOxy = nums;
    vector<int> vecCo = nums;

    int i = size-1;
    while(i >= 0){
        if(vecOxy.size() != 1) {
            int bo = getBitCriteria(vecOxy, i, true);
            vecOxy = filter(vecOxy, bo, i);
        }
        if(vecCo.size() != 1) {
            int bc = getBitCriteria(vecCo, i, false);
            vecCo = filter(vecCo, bc, i);
        }
        i--;
    }

    int oxygen = vecOxy[0];
    int co2 = vecCo[0];
    int life = oxygen*co2;

    cout << oxygen << endl;
    cout << co2 << endl;
    cout << life << endl;
}