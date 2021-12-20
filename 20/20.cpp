#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

struct Point{
    int x, y;
};

struct Image{
    vector<bool> pixels;
    int size;
};
struct Input{
    vector<bool> algo;
    Image image;
};

int boolToInt(const vector<bool>& bools){
    int n = 0;
    for(bool b : bools){
        n <<= 1;
        if(b)
            n |= 1;
    }
    return n;
}
Input openFile(const string& path){
    ifstream file;
    file.open(path);
    if(!file.is_open())
        throw runtime_error("File not opened");

    Input input;
    string line;

    file >> line;
    for(char c : line){
        input.algo.emplace_back(c == '#');
    }

    while(file.peek() != EOF){
        file >> line;
        input.image.size = line.size();
        for(char c : line)
            input.image.pixels.emplace_back(c == '#');
    }

    return input;
}
vector<bool> getAround(const Image& img, const Point& p){
    vector<bool> vec;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            Point pp = {p.x+j, p.y+i};

            if(pp.x < 0 || pp.x >= img.size || pp.y < 0 || pp.y >= img.pixels.size()/img.size)
                vec.emplace_back(img.pixels[0]);
            else
                vec.emplace_back(img.pixels[pp.y*img.size + pp.x]);
        }
    }
    return vec;
}

Image iterate(const Image& img, const vector<bool>& algo){
    Image i2;
    i2.size = img.size+2;
    int height = img.pixels.size()/img.size+2;

    for (int i = 0; i < i2.size*height; ++i) {
        Point pp = {i%i2.size-1, i/i2.size-1};
        auto bools = getAround(img, pp);
        auto n = boolToInt(bools);

        if(n < 0 || n >= algo.size())
            throw runtime_error("Not in list");
        auto finded = algo[n];
        i2.pixels.emplace_back(finded);
    }
    return i2;
}
void print(Image& img){
    for (int i = 0; i < img.pixels.size(); ++i) {
        cout << ((img.pixels[i]) ? '#' : '.');
        if(i%img.size == img.size-1)
            cout << endl;
    }
    cout << endl;
}
void print(vector<bool>& algo){
    for(bool b : algo){
        cout << ((b) ? '#' : '.');
    }
    cout << endl;
}
int cntBools(Image& img){
    int n = 0;
    for(bool b : img.pixels)
        if(b) n++;
    return n;
}
Image getBigger(const Image& img, int n){
    int width = img.size+n*2;
    int height = img.pixels.size()/img.size+n*2;

    Image img2;
    img2.size = width;

    for (int i = 0; i < width*height; ++i) {
        int x = i%width-n;
        int y = i/width-n;

        if(x < 0 || x >= img.size || y < 0 || y >= img.pixels.size()/img.size)
            img2.pixels.emplace_back(false);
        else
            img2.pixels.emplace_back(img.pixels[y*img.size+x]);
    }
    return img2;
}
int main(int argc, char** argv){
    string file = "../20/input.txt";
    auto input = openFile(file);

    auto img = input.image;
    auto algo = input.algo;

    img = getBigger(img, 3);

    int N = 50;

    print(algo);
    cout << endl;
    print(img);

    for (int i = 0; i < N; ++i) {
        img = iterate(img, algo);
        //print(img);
    }

    cout << cntBools(img) << endl;
    cout << img.size << ' ' << img.pixels.size()/img.size << endl;
}
// 5288
// 5306