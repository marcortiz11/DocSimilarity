#include <cstdlib>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

struct Shuffler {
    int size;
    int coprime;

    Shuffler(int n){
        size = n;
        coprime = rand();
        coprime /= gcd(size, coprime);
    }

    inline int getpos(int i){
        return i*coprime % size;
    }
};
