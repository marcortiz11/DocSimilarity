#include <set>
#include <string>
#include <iostream>
#include "../docstore.h"

using namespace std;

int main() {

    docstore ds;
    string s = "data/tweets";
    ds.setcollection(s);
    while (not ds.isdone()) {
        cout << ds.getfilename() << endl;
    }
    set<string> st = getwordsfromfile("data/english_stopwords.txt");
    for (auto i : st) {
        cout << i << endl;
    }
}
