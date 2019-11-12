#include "bitVector.hpp"

bitVector::bitVector(int n_bits, int n_elements, int n_sets){
    bits_ = vector<bool> (n_sets * n_elements * n_bits, false);
    n_bits_ = n_bits;
    n_elements_ = n_elements;
    n_sets_ = n_sets;
}

bitVector::bitVector(long int number,int n_bits_total){
    bits_ = toBinary(number, n_bits_total);
    n_bits_ = 3;
    n_elements_ = 3;
    n_sets_ = 3;
}

bitVector::bitVector(const bitVector &bits){
    bits_ = bits.getBits();
    n_bits_ = bits.getN_Bits();
    n_elements_ = bits.getN_Elements();
    n_sets_ = bits.getN_Sets();
}

bitVector::~bitVector(){
    bits_ = vector<bool> (0);
    n_bits_ = 0;
    n_elements_ = 0;
    n_sets_ = 0;
}

vector<bool> bitVector::getBits() const{
    return bits_;
}

int bitVector::getN_Bits() const{
    return n_bits_;
}

int bitVector::getN_Elements() const{
    return n_elements_;
}

int bitVector::getN_Sets() const{
    return n_sets_;
}

bool bitVector::getBit(int position) const{
    return bits_.at(position);
}

void bitVector::setBit(bool bit, int position){
    bits_.at(position) = bit;
}

void bitVector::setBit(bool bit, int position, int element){
    int pos = (((element - 1) * getN_Elements() * getN_Bits()) + (getN_Bits() * (position)) - 1);
    bits_.at(pos) = bit;
}

long int bitVector::pow(int exp, int base){
    long int result = 1;
    for(int i = 0; i < exp; i++){
        result *= base;
    }
    return result;
}

long int bitVector::pow2(int exp){
    return pow(exp, 2);
}

vector<bool> bitVector::toBinary(long int number,int n_bits_total){
    vector<bool> sol(0);
    long int dividendo = number;
    long int cociente = 0;
    bool resto = false;
    while(dividendo != 0){
        cociente = dividendo / 2;
        resto = (bool)(dividendo % 2);
        sol.insert(sol.begin(),resto);
        dividendo = cociente;
    }
    while(sol.size() < n_bits_total){
        sol.insert(sol.begin(), false);
    }
    return sol;
}

long int bitVector::toDecimal(){
  long int decimal = 0;
  for(int i = 0; i < bits_.size(); i++){
    if(bits_[i]){
        decimal += pow2(bits_.size() - (i + 1));
    }
  }
  return decimal;
}

bitVector bitVector::operator + (const bitVector &sumando){
    bitVector resultado(getN_Bits(), getN_Elements(), getN_Sets());
    bool carrier = false;
    bool carrier2 = false;
    bool res = false;
    for(int i = resultado.getBits().size() - 1;i >= 0; i--){
        res = getBit(i) ^ sumando.getBit(i) ^ carrier;
        carrier = ((getBit(i) & sumando.getBit(i)) | (sumando.getBit(i) & carrier) | (getBit(i) & carrier));
        resultado.setBit(res, i);
    }
    return resultado;
}

ostream& operator << (ostream& os, const bitVector &b){
    os << "[";
    for(int i = 0; i < b.getBits().size(); i++){
        if (b.getBit(i)){
            os << "1";
        }else{
            os << "0";
        }
        if ((((i + 1) % (b.getN_Bits() * b.getN_Elements())) == 0) && ((i + 1) != b.getBits().size())){
            os <<  "|";
        }else if((((i + 1) % (b.getN_Bits())) == 0) && ((i + 1) != b.getBits().size())){
            os << " ";
        }
    }
    os << "]";
    return os;
}