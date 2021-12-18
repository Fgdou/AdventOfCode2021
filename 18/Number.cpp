//
// Created by projector-user on 12/18/21.
//

#include "Number.h"


Number::Number()
        : left(nullptr), right(nullptr), value(0){}
Number::Number(int value) : left(nullptr), right(nullptr), value(value){}

Number::Number(Number&& left, Number&& right)
        : left(make_unique<Number>(move(left))), right(make_unique<Number>(move(right))), value(0){}
Number::Number(const Number& left, const Number& right)
        : left(make_unique<Number>(left)), right(make_unique<Number>(right)), value(0){}
Number::Number(const Number& copy)
        : right(nullptr), left(nullptr), value(copy.value){
    if(copy.left != nullptr)
        left = make_unique<Number>(*copy.left);
    if(copy.right != nullptr)
        right = make_unique<Number>(*copy.right);
}
Number& Number::operator=(const Number& copy){
    if(copy.left != nullptr)
        left = make_unique<Number>(*copy.left);
    else
        left = nullptr;
    if(copy.right != nullptr)
        right = make_unique<Number>(*copy.right);
    else
        right = nullptr;
    value = copy.value;
    return *this;
}

bool Number::isValue() const{
    return left == nullptr;
}

void Number::print() const{
    rprint();
    cout << endl;
}
void Number::rprint() const{
    if(isValue())
        cout << value;
    else{
        cout << '[';
        left->rprint();
        cout << ',';
        right->rprint();
        cout << ']';
    }
}
Number Number::operator+(const Number& n2){
    return {*this, n2};
}

Number Number::_explode(const Number& current, const Number& root, Number& deleted, int cnt){
    if(current.isValue())
        return current;
    if(cnt < 4 || !current.left->isValue()){
        auto left = _explode(*current.left, root, deleted, cnt+1);
        auto right = _explode(*current.right, root, deleted, cnt+1);
        return {move(left), move(right)};
    }else if(deleted.isValue()){
        deleted = current;
        return Number{-1};
    }else{
        return current;
    }
}
Number Number::split(){
    bool stop = false;
    return _split(stop);
}

void Number::_addToVec(Number& current, vector<Number*>& vec){
    if(current.isValue())
        vec.push_back(&current);
    else{
        _addToVec(*current.left, vec);
        _addToVec(*current.right, vec);
    }
}
void Number::_addLeftRight(Number& root, const Number& toAdd){

    if(toAdd.isValue())
        return;

    vector<Number*> vec;
    _addToVec(root, vec);

    for(int i=0; i<vec.size(); i++){
        Number& n = *vec[i];

        if(n.value == -1){
            n.value = 0;
            if(i > 0)
                (*vec[i-1]).value += toAdd.left->value;
            if(i < vec.size()-1)
                (*vec[i+1]).value += toAdd.right->value;
            break;
        }
    }
}
Number Number::explode() const{
    Number deleted;
    auto ex = _explode(*this, *this, deleted);
    _addLeftRight(ex, deleted);
    //cout << "explode "; deleted.print();
    return ex;
}

Number Number::simplify() const{
    Number n = *this;
    Number other;

    do{

        other = n;
        n = n.explode();
        //n.print();

        if(n == other){
            other = n;
            n = n.split();
            //cout << "split" << endl;
            //n.print();
        }
    }while(other != n);

    return n;
}

bool Number::operator==(const Number& other) const{
    if(isValue() != other.isValue())
        return false;
    if(isValue())
        return value == other.value;
    return *left == *other.left && *right == *other.right;
}
bool Number::operator!=(const Number& other) const{
    return !(*this == other);
}

Number::Number(stringstream &ss)
    : left(nullptr), right(nullptr), value(0)
{
    char c;
    ss >> c;

    if(c == '['){
        left = make_unique<Number>(ss);
        ss >> c;
        right = make_unique<Number>(ss);
        ss >> c;
    }else
        value = c-'0';
}

Number Number::_split(bool& stop) {
    if(isValue()){
        if(value < 10 || stop)
            return *this;
        Number left(value/2);
        Number right(value-value/2);
        stop = true;
        return {left, right};
    }
    return {left->_split(stop), right->_split(stop)};
}

long Number::magnitude() const {
    if(isValue())
        return value;
    return 3*left->magnitude() + 2*right->magnitude();
}
