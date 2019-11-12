#include <iostream>

#include "3DM.hpp"

int main(int argc, char const *argv[]) {
    
    _3DM problema("./problema1.3dm");
    vector<long int> resultado;

    cout << problema << endl << endl;

    resultado = problema.transformToPartition();

    cout << "Resultado de la Transformación: [";
    for(int i = 0; i < resultado.size() - 1; i++){
        cout << resultado.at(i) << " ";
    }
    cout << resultado.at(resultado.size() - 1) << "]" << endl;
    return 0;
}
