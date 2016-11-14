#include <set>
#include <string>
#include <iostream>
#include "../shuffler.h"

#define N 10

using namespace std;

int main() {
    string vec[N] = {"a","b","c","d","e","f","g","h","i","j"};
    set<string> s = set<string>();
    shuffler sf(N);
    for (int i=0; i<N; i++) {
        s.insert(vec[sf.shuffle(i)]);
    }
    if (s.size() != N) {
        cout << "Shuffle produces collisions" << endl;
        throw 0;
    }
}
