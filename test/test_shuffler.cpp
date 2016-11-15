#include <set>
#include <string>
#include <iostream>
#include <cstdlib>
#include "../shuffler.h"

using namespace std;

int main() {
    for (int j=0; j<10000; j++) {
        int n = (rand() % 1000)+1; //can't be zero
        set<int> s = set<int>();
        shuffler sf(n);
        for (int i=0; i<n; i++) {
            s.insert(sf.shuffle(i));
        }
        if (s.size() != n) {
            cout << "n: " << n << " size: " << s.size() << endl;
            cout << "coprime: " << sf.coprime << endl;
            cout << "Shuffle produces collisions" << endl;
            throw 0;
        }
    }
}
