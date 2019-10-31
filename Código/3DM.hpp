#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "tripleta.hpp"

using namespace std;

class _3DM {
    private:
        vector<string> x_;
        vector<string> y_;
        vector<string> z_;
        vector<tripleta> w_;

    public:
        _3DM(vector<string> x, vector<string> y, vector<string> z);
        _3DM(string fichero);
        ~_3DM();
        vector<string> getX() const;
        vector<string> getY() const;
        vector<string> getZ() const;
        vector<tripleta> getW() const;

        vector<int> transformToPartition();
};

ostream& operator << (ostream& os, const _3DM &p);
vector<string> split (string str_, string delimiter);
vector<tripleta> createW (vector<string> matches);
