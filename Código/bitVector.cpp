#include "bitVector.hpp"

bitVector::bitVector(const bitVector &bits){
    bits_ = bits.getBits();
    n_bits_ = bits.getN_Bits();
    n_elements_ = bits.getN_Elements();
    n_sets_ = bits.getN_Sets();
}

bitVector::bitVector(int n_bits, int n_elements, int n_sets){
    bits_ = vector<bool> (n_sets * n_elements * n_bits, false);
    n_bits_ = n_bits;
    n_elements_ = n_elements;
    n_sets_ = n_sets;
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

void bitVector::setBit(bool bit, int position){
    bits_.at(position) = bit;
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

long int bitVector::toDecimal(){
  long int decimal = 0;
  for(int i = 1; i <= bits_.size(); j++){
    if(bits_[i] == 1){
        a_decimal += pow2(bits_.size() - i);
    }
  }
  return decimal;
}