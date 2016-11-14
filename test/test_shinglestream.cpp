#include <set>
#include <string>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include "../docstore.h"
#include "../shinglestream.h"

using namespace std;

//***TESTS***
void runchars(string filename, bool v=false) {
    if (v) {
        cout << endl;
        cout << "CHARS _____________________________________" << endl;
        cout << endl;
    }
    kcharstream ss1(3);
    ss1.open(filename);
    while (not ss1.isdone()) {
        string tmp = ss1.getshingle();
        if (v) {
            cout << tmp << endl;
        }
    }
    ss1.close();
}

void runwords(string filename, bool v=false) {
    if (v) {
        cout << endl;
        cout << "WORDS _____________________________________" << endl;
        cout << endl;
    }
    auto s = set<string>();
    s.insert("and");
    s.insert("or");
    s.insert("then");
    s.insert("stop");
    s.insert("hat");
    kwordstream ss2(3,s);
    ss2.open(filename);
    while (not ss2.isdone()) {
        string tmp = ss2.getshingle();
        if (v) {
            cout << tmp << endl;
        }
    }
    ss2.close();
}

int main () {

    string filename = "data/tweets/80.txt";
    runchars(filename,true);
    runwords(filename,true);

    docstore ds;
    cout << "permutations ---------------------------------------------" << endl;
    string s = "data/permutations";
    ds.setcollection(s);
    while (not ds.isdone()) {
        filename =  ds.getfilename();
        runchars(filename);
        runwords(filename);
    }

    cout << "novels ---------------------------------------------" << endl;
    s = "data/novels";
    ds.setcollection(s);
    while (not ds.isdone()) {
        filename =  ds.getfilename();
        runchars(filename);
        runwords(filename);
    }

    cout << "tweets ---------------------------------------------" << endl;
    s = "data/tweets";
    ds.setcollection(s);
    while (not ds.isdone()) {
        filename =  ds.getfilename();
        runchars(filename);
        runwords(filename);
    }

    return 0;
}
