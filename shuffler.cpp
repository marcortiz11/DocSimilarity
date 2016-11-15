#include <cstdlib>
#include <iostream>

using namespace std;

int gcd ( int a, int b ) {
  int c;
  while ( a != 0 ) {
     c = a; a = b%a;  b = c;
  }
  return b;
}

class shuffler {

public:
    int size;
    long long int coprime;
    shuffler(int n);
    long long int shuffle(int i);
};

shuffler::shuffler(int n){
    size = n+1;
    int divisor = 1;
    long long int aux = 1;
    while (divisor == aux) {
        aux = (rand() % 1000)+2; //can't be zero or 1
        divisor = gcd(size, aux);
    }
    aux /= divisor;
    while ((divisor = gcd(size, aux)) != 1) {
        aux /= divisor;
    }
    coprime = aux;
}

long long int shuffler::shuffle(int i){
    return ((i+1)*coprime % size)-1;
}
