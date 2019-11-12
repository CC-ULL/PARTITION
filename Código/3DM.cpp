#include "3DM.hpp"

_3DM::_3DM(vector<string> x, vector<string> y, vector<string> z) {
    x_ = x;
    y_ = y;
    z_ = z;
}

_3DM::_3DM(string fichero){
    try {
        int nVector = 0;
        string element;
        ifstream fich(fichero);
        string linea;
        vector<string> matches;
        while (nVector <= 2) {
            getline(fich, linea);
            matches = split(linea, " ");

            for (int i = 0; i<matches.size(); ++i) {
                switch (nVector){
                    case 0:
                        x_.push_back(matches[i]);
                        break;
                    case 1:
                        y_.push_back(matches[i]);
                        break;
                    case 2:
                        z_.push_back(matches[i]);
                        break;
                }
            }
            nVector++;
        }

        getline(fich, linea);
        nVector++;

        matches = split(linea, ", ");
        w_ = createW(matches);

        fich.close();
        if(nVector != 4){
            throw "Error: numero de conjuntos no adecuado";
        }
        if(x_.size() != y_.size() || x_.size() != z_.size()) {
            throw "Error: El tamaño de los conjuntos no es el mismo";
        }
    }catch (const string* msg) {
        cerr << msg << endl;
        exit(1);
    }
}

_3DM::~_3DM() {
    x_.clear();
    y_.clear();
    z_.clear();
}

vector<string> _3DM::getX() const{
    return x_;
}

vector<string> _3DM::getY() const{
    return y_;
}

vector<string> _3DM::getZ() const{
    return z_;
}

vector<tripleta> _3DM::getW() const{
    return w_;
}

int find(vector<string> a, string b){
    for(int i=0;i<a.size();i++){
        if(a[i]==b){
            return i + 1;
        }
    }
    return -1;
}

vector<long int> _3DM::transformToPartition(){
    vector<long int> partition;                                                  //EL CONJUNTO DE SIZES DEL PROBLEMA PARTITION
    int n_bits = ceil(log2(w_.size() + 1));                                 //NÚMERO DE BITS NECESARIOS PARA REPRESENTAR EL NÚMERO MÁXIMO DE REPETICIONES DE UN ELEMENTO EN EL CONJUNTO w_
    int n_elements = x_.size();                                             //NÚMERO DE ELEMENTOS QUE HAY EN LOS SETS x_,y_,z_
    vector<bitVector> datos(w_.size(), bitVector(n_bits, n_elements, 3));   //VECTOR PARA REPRESENTAR CADA UNO DE LOS ELEMENTOS DEL PARTITION EN BINARIO

    //PASAR LA TRIPLETA w_[i] DEL PROBLEMA 3DM A SU REPRESENTACIÓN EN BINARIO PARA EL SIZE DEL PROBLEMA PARTITION
    for(int i = 0; i < datos.size(); i++){
        datos[i].setBit(true, find(x_,w_[i].getX()), 1);
        datos[i].setBit(true, find(y_,w_[i].getY()), 2);
        datos[i].setBit(true, find(z_,w_[i].getZ()), 3);
    }

    for(int i = 0; i < datos.size(); i++){
        cout << "S(a" << i << ") = " << w_[i] << " = " << datos[i] << " = " << datos[i].toDecimal() << endl;
        partition.push_back(datos[i].toDecimal());
    }

    //CALCULAR LOS ELEMENTOS AÑADIDOS AL PARTITION PARA QUE SI EXISTE UN SUBCONJUNTO DE LOS ELEMENTOS QUE YA TENEMOS QUE SUME b EL PARTITION TENGA SOLUCIÓN
    bitVector sumatorio (n_bits, n_elements, 3);
    for(int i = 0;i < datos.size(); i++){
        sumatorio = sumatorio + datos[i];
    }

    partition.push_back(sumatorio.toDecimal());

    cout << "\t\t∑ = " << sumatorio << " = " << sumatorio.toDecimal() << endl << endl;


    //ELEMENTO QUE REPRESENTA EL MATCH EN EL 3DM PASADO A SIZE DEL PARTITION
    bitVector b (n_bits, n_elements, 3);
    for(int i = 1; i <= (n_elements); i++){
        b.setBit(true, i, 1);
        b.setBit(true, i, 2);
        b.setBit(true, i, 3);
    }

    partition.push_back(b.toDecimal());

    cout << " b = " << b << " = " << b.toDecimal() << endl;

    bitVector b1 ((2 * sumatorio.toDecimal()) - b.toDecimal(), n_bits * n_elements * 3);
    bitVector b2 (sumatorio + b);

    partition.push_back(b1.toDecimal());
    partition.push_back(b2.toDecimal());

    cout << "b1 = " << b1 << " = " << b1.toDecimal() << endl;
    cout << "b2 = " << b2 << " = " << b2.toDecimal() << endl << endl;

    return partition;
}

string printVector(string name, vector<string> vector_){
    string result = name;
    result += ": ";
    for (vector<string>::iterator it=vector_.begin(); it!=vector_.end(); ++it) {
        result += *it + " ";
    }
    return result;
}

ostream& operator <<(ostream& os, const _3DM &p) {
    os << printVector("X", p.getX()) << endl;
    os << printVector("Y", p.getY()) << endl;
    os << printVector("Z", p.getZ()) << endl;

    vector<tripleta> w = p.getW();
    os << "W: ";
    for (vector<tripleta>::iterator it = w.begin(); it != w.end(); it++) {
        os << (*it);
        os << " ";
    }
    return os;
}


vector<string> split (string str_, string delimiter) {
    vector<string> ocurrences;
    string str = str_;
    int last = 0;
    while(!str.empty()){
        last = str.find(delimiter);
        if(last != -1){
            ocurrences.push_back(str.substr(0, last));
            str.erase(0, last + delimiter.size());
        }else{
            ocurrences.push_back(str.substr(0, str.size()));
            str.erase(0, str.size());
        }
    }
    return ocurrences;
}

vector<tripleta> createW (vector<string> matches) {
    vector<string> elements;
    vector<tripleta> w;
    try{
        for (int i = 0; i < matches.size(); i++){
            elements = split(matches[i], " ");
            if(elements.size() == 3){
                w.push_back(tripleta(elements[0], elements[1], elements[2]));
            }else{
                throw "Error: numero de elementos de posibles matches erroneo";
            }
        }
        return w;
    } catch(const string* msg) {
        cerr << msg << endl;
        exit(1);
    }
}
