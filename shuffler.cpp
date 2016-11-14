#include <cstdlib>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

class shuffler {

public:
    int size;
    int coprime;
    shuffler(int n);
    int shuffle(int i);
};

shuffler::shuffler(int n){
    size = n;
    coprime = rand();
    coprime /= gcd(size, coprime);
    coprime = coprime % size;
}

int shuffler::shuffle(int i){
    return i*coprime % size;
}
