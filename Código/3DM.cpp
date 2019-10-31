#include "3DM.hpp"

_3DM::_3DM(vector<string> x, vector<string> y, vector<string> z) {
    x_ = x;
    y_ = y;
    z_ = z;
};

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
};

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

vector<int> _3DM::transformToPartition(){
    //TODO
}

string printVector(string name, vector<string> vector_){
    string result = name;
    result += ": ";
    for (vector<string>::iterator it=vector_.begin(); it!=vector_.end(); ++it){
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
    for (vector<tripleta>::iterator it = w.begin(); it != w.end(); it++){
        os << (*it);
        os << " ";
    }
    return os;
}


vector<string> split (string str_, string delimiter){
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

vector<tripleta> createW (vector<string> matches){
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