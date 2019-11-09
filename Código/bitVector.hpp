#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class bitVector {
    private:
        vector<bool>  bits_;
        int n_bits_;
        int n_elements_;
        int n_sets_;

        long int pow(int exp, int base);
        long int pow2(int exp);
        vector<bool> toBinary(long int number,int n_bits_total);

    public:
        bitVector(long int number,int n_bits_total);
        bitVector(int n_bits, int n_elements, int n_sets);
        bitVector(const bitVector &bits);
        ~bitVector();
        vector<bool>  getBits() const;
        int getN_Bits() const;
        int getN_Elements() const;
        int getN_Sets() const;
        bool getBit(int position) const;
        void setBit(bool bit, int position);
        void setBit(bool bit, int position, int element);
        long int toDecimal();
        bitVector operator + (const bitVector &sumando);
};

ostream& operator << (ostream& os, const bitVector &b);