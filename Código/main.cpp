#include <iostream>

#include "3DM.hpp"

int main(int argc, char const *argv[]) {

    vector<int> x, y, z;
    
    //_3DM problema(x,y,z);
    _3DM problema("./problema1.3dm");

    cout << problema << endl;

    problema.transformToPartition();
    return 0;
}
