#include <vector>
#include <cmath>

using namespace std;

class bitVector {
    private:
        vector<bool>  bits_;
        int n_bits_;
        int n_elements_;
        int n_sets_;

        long int pow(int exp, int base);
        long int pow2(int exp);

    public:
        bitVector(const bitVector &bits);
        bitVector(int n_bits, int n_elements, int n_sets);
        ~bitVector();
        vector<bool>  getBits() const;
        int getN_Bits() const;
        int getN_Elements() const;
        int getN_Sets() const;
        void setBit(bool bit, int position);
        long int toDecimal();

};

ostream& operator << (ostream& os, const bitVector &b);