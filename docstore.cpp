#include <set>
#include <string>
#include <fstream>
#include <unistd.h>
#include <iostream>

using namespace std;

set<string> getwordsfromfile(string filename) {
    ifstream file;
    file.open (filename);
    if (!file.is_open()) {
        cout << "Error: file not found" << endl;
        throw 0;
    }
    string word;
    set<string> s = set<string>();
    while (file >> word)
    {
        s.insert(word);
    }
    return s;
}

class docstore {

private:
    int index;
    string path;
    bool file_exists(const string& filename);

public:
    docstore(int index=1);
    void setcollection(const string& path);
    bool isdone();
    string getfilename();
};

docstore::docstore(int index) {
    this->index = index;
}

void docstore::setcollection(const string& path) {
    this->path = path;
}

inline bool docstore::file_exists(const string& filename) {
    return ( access( filename.c_str(), F_OK ) != -1 );
}

bool docstore::isdone() {
    return not file_exists(path + "/" + to_string(index) + ".txt");
}

string docstore::getfilename() {
    string filename = path + "/" + to_string(index) + ".txt";
    if (not file_exists(filename)) {
        cout << "Error: there are no more files" << endl;
        throw 0;
    }
    index++;
    return filename;
}

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
