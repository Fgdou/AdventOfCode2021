//
// Created by projector-user on 12/19/21.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Scanner.h"
#include "Point.h"

using namespace std;

vector<Scanner> openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not found");

    vector<Scanner> vec;
    while(file.peek() != EOF){
        char line[50];
        string sline;
        file.getline(line, 50);

        int n;
        sscanf(line, "--- scanner %d ---", &n);

        Scanner sc({}, n);
        while(file.peek() != EOF){
            file.getline(line, 50);
            sline.assign(line);
            if(sline.size() < 2)
                break;

            Point p;
            sscanf(line, "%d,%d,%d", &p.x, &p.y, &p.z);
            sc.addPoint(p);
        }
        vec.emplace_back(sc);
    }
    return vec;
}

vector<Scanner> getPos(vector<Scanner> list){
    vector<Scanner> done;
    done.emplace_back(list[0]);

    bool founded = true;
    while(founded){
        auto t1 = time(nullptr);
        founded = false;
        for (auto& s1 : done) {
            for (auto& s2 : list) {
                if(s1 == s2)
                    continue;
                if(find(done.begin(), done.end(), s2) != done.end())
                    continue;
                try {
                    done.emplace_back(s1.findBestFit(s2));
                    founded = true;
                    break;
                } catch (ErrorNotFound& e) {
                    continue;
                }
            }
            if(founded)
                break;
        }
        auto t2 = time(nullptr);
        cout << done.size() << '/' << list.size()  << " in " << t2-t1 << "s" << endl;
    }
    return done;
}

vector<Point> getPoints(vector<Scanner>& scs){
    vector<Point> list;

    for (const auto& sc : scs) {
        const auto& l = sc.getPoints();

        for(const auto& p : l){
            if(find(list.begin(), list.end(), p) == list.end())
                list.emplace_back(p);
        }
    }

    return list;
}

int main(int argc, char** argv){
    string path = "../19/input.txt";
    auto list = openFile(path);

    auto done = getPos(list);
    auto points = getPoints(done);

    for(auto& p : points)
        cout << p << endl;
    cout << points.size() << endl;

}