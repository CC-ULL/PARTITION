#include "tripleta.hpp"

tripleta::tripleta(string x, string y, string z){
    x_ = x;
    y_ = y;
    z_ = z;
}

tripleta::tripleta(){
    x_ = "";
    y_ = "";
    z_ = "";
}

tripleta::~tripleta(){
    x_ = "";
    y_ = "";
    z_ = "";
}

string tripleta::getX() const{
    return x_;
}

string tripleta::getY() const{
    return y_;
}

string tripleta::getZ() const{
    return z_;
}

ostream& operator << (ostream& os, const tripleta &t){
    os << "{" << t.getX() << ", " << t.getY() << ", " << t.getZ() << "}";
    return os;
}