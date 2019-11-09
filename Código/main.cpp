#include <iostream>

#include "3DM.hpp"

int main(int argc, char const *argv[]) {

    /*bitVector a (1234567, 27);
    bitVector b (7654321, 27);

    //8888888
    //000 100 001 111 010 001 000 111 000
    cout << "A: " << a << endl;
    cout << "B: " << b << endl;
    cout << "C: " << (a + b) << endl;*/
    
    _3DM problema("./problema1.3dm");

    cout << problema << endl << endl;

    problema.transformToPartition();
    return 0;
}
