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

bitVector bitFrom3DM(){
    int n_bits = ceil(log2(w_.size() + 1));
    int n_elements = x_.size();
    bitVector bits(n_bits, n_elements, 3);

    for(int i = 0; i < w_.size(); i++){
        bits.setBit()
    }
    
}

int find(vector<string> a, string b){
    for(int i=0;i<a.size();i++){
        if(a[i]==b){
            return i;
        }
    }
}

vector<int> _3DM::transformToPartition(){
    vector<int> partition(w_.size()+2,0);       //EL CONJUNTO DE SIZES DEL PROBLEMA PARTITION
    int n_bits=ceil(log2(w_.size()+1));         //NÚMERO DE BITS NECESARIOS PARA REPRESENTAR EL NÚMERO MÁXIMO DE REPETICIONES DE UN ELEMENTO EN EL CONJUNTO w_
    int n_elements=x_.size();                   //NÚMERO DE ELEMENTOS QUE HAY EN LOS SETS x_,y_,z_
    vector<int> aux(3*n_elements*n_bits,0);     //VECTOR PARA REPRESENTAR CADA UNO DE LOS ELEMENTOS DEL PARTITION EN BINARIO
    vector<vector<int> > datos(w_.size(),aux);  //CONJUNTO DE VECTORES aux

    //PASAR LA TRIPLETA w_[i] DEL PROBLEMA 3DM A SU REPRESENTACIÓN EN BINARIO PARA EL SIZE DEL PROBLEMA PARTITION
    for(int i=0; i<datos.size(); i++){
        datos[i][n_bits*(find(x_,w_[i].getX())+1)-1]=1;
        datos[i][(n_elements*n_bits)+n_bits*(find(y_,w_[i].getY())+1)-1]=1;
        datos[i][(2*n_elements*n_bits)+n_bits*(find(z_,w_[i].getZ())+1)-1]=1;
        cout<<"listo:{"<<w_[i].getX()<<" "<<w_[i].getY()<<" "<<w_[i].getZ()<<"}"<<endl;
    }

    //ELEMENTO QUE REPRESENTA EL MATCH EN EL 3DM PASADO A SIZE DEL PARTITION
    vector<int> b(3*n_elements*n_bits,0);
    for(int i=0; i<(3*n_elements); i++){
        b[n_bits*(i+1)-1]=1;
        b[(n_elements*n_bits)+n_bits*(i+1)-1]=1;
        b[(2*n_elements*n_bits)+n_bits*(i+1)-1]=1;
    }



    //CALCULAR LOS ELEMENTOS AÑADIDOS AL PARTITION PARA QUE SI EXISTE UN SUBCONJUNTO DE LOS ELEMENTOS QUE YA TENEMOS QUE SUME b EL PARTITION TENGA SOLUCIÓN
     cout<<"p="<<3*n_elements*n_bits<<endl;
    vector<int> c(10);
    cout<<"p"<<endl;
    for(int i=0;i<datos.size();i++){
        //ESCRIBIR sumatorio
        {
            string str("");
            for(int j=0; j<c.size(); j++){
                str+=to_string(c[j]);
                if((j+1)%(n_bits*n_elements)==0 && (j+1)%(3*n_bits*n_elements)!=0){
                    str+="|";
                }
            }
            cout<<"sumat=["+str+"]"<<endl;
        }
        for(int j=0;j<datos[i].size();j++){
            if(datos[i][j]==1){
                int k=j;
                while(c[k]==1){
                    c[k]=0;
                    k++;
                }
                c[k]=1;
            }
        }
    }



    //ESCRIBIR b
    {
        string str("");
        for(int j=0; j<b.size(); j++){
            str+=to_string(b[j]);
            if((j+1)%(n_bits*n_elements)==0 && (j+1)%(3*n_bits*n_elements)!=0){
                str+="|";
            }
        }
        cout<<"b=["+str+"]"<<endl;
    }

    //ESCRIBIR LOS ELEMENTOS DEL PARTITION SACADOS DIRECTAMENTE DEL CONJUNTO w_ EN BINARIO Y PASARLOS A DECIMAL
    for(int i=0; i<datos.size(); i++){
        string str("");
        long int a_decimal=0;
        for(int j=0; j<datos[i].size(); j++){
            str+=to_string(datos[i][j]);
            if(datos[i][j]==1){
                long int potencia=pow2(datos[i].size()-(j+1));
                a_decimal+=potencia;
            }
            if((j+1)%(n_bits*n_elements)==0 && (j+1)%(3*n_bits*n_elements)!=0){
                str+="|";
            }
        }
        partition[i]=a_decimal;
        cout<<"s(a"<<i<<")="<<"["+str+"]="<<a_decimal<<endl;
    }

    //ESCRIBIR sumatorio
    {
        string str("");
        for(int j=0; j<c.size(); j++){
            str+=to_string(c[j]);
            if((j+1)%(n_bits*n_elements)==0 && (j+1)%(3*n_bits*n_elements)!=0){
                str+="|";
            }
        }
        cout<<"sumat=["+str+"]"<<endl;
    }

    //ESCRIBIR LOS ELEMENTOS AÑADIDOS EN BINARIO Y PASARLOS A DECIMAL


    return partition;

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
