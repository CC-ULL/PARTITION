#include <iostream>

using namespace std;

class tripleta {
    private:
        string x_;
        string y_;
        string z_;

    public:
        tripleta();
        tripleta(string x, string y, string z);
        ~tripleta();
        string getX() const;
        string getY() const;
        string getZ() const;
};

ostream& operator << (ostream& os, const tripleta &t);