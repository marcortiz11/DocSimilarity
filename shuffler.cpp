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
    int divisor = 1;
    while (divisor <= 1) {
        coprime = rand();
        divisor = gcd(size, coprime);
    }
    coprime /= divisor;
    coprime = coprime % size;
}

int shuffler::shuffle(int i){
    return i*coprime % size;
}
