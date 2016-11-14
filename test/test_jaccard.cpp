#include <set>
#include <string>
#include <iostream>
#include "../jaccard.h"

using namespace std;

int main() {
    set<string> s1 = set<string>(), s2 = set<string>();
    s1.insert("a");
    if (not (jaccard(s1,s2) == 0)) {
        cout << "jaccard 1 failed" << endl;
        throw 0;
    }
    s2.insert("b");
    if (not (jaccard(s1,s2) == 0)) {
        cout << "jaccard 2 failed" << endl;
        throw 0;
    }
    s2.insert("a");
    if (not (jaccard(s1,s2) == 0.5)) {
        cout << "jaccard 3 failed" << endl;
        throw 0;
    }
    s2.insert("c");
    if (not (jaccard(s1,s2) == 1/double(3))) {
        cout << "jaccard 4 failed" << endl;
        throw 0;
    }
    s1.insert("b");
    if (not (jaccard(s1,s2) == 2/double(3))) {
        cout << "jaccard 5 failed" << endl;
        throw 0;
    }
}
