#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <set>

using namespace std;

class shinglestream {

private:
    string clean(const string& dirtyboy);

protected:
    int k;
    virtual string getnext() = 0;

public:
    virtual bool eof() = 0;
    virtual void open(const char* filename) = 0;
    virtual void close() = 0;
    string getshingle();
};

string shinglestream::clean(const string& dirtyboy) {
    string clean_boy = "";
    for (const char& c : dirtyboy) {
        clean_boy += tolower(c);
    }
    return clean_boy;
}

string shinglestream::getshingle() {
    return clean(getnext());
}


//Reads k-shingles composed of characters
class kwordstream : public shinglestream {

private:
    ifstream ifs;
    list<string> buffer;
    set<string> stopwords;
    string getnext();

public:
    bool eof();
    void open(const char* filename);
    void close();
    kwordstream(int k=3, set<string> stopwords=set<string>());
};

bool kwordstream::eof() {
    string word;
    while ((buffer.size() != this->k) and not ifs.eof()) {
        ifs >> word;
        buffer.push_back(word);
        if (not stopwords.count(buffer.front())) {
            buffer.pop_front();
        }
    }
    return ifs.eof();
}

string kwordstream::getnext() {
    if (eof()) {
        cout << "Error: unexpected end of file" << endl;
        throw 0;
    }
    string res = "";
    for (string s : buffer) {
        res += s;
    }
    buffer.pop_front();
    return res;
}

void kwordstream::open(const char* filename) {
    ifs.open(filename, ifstream::in);
}

void kwordstream::close() {
    ifs.close();
}

kwordstream::kwordstream(int k, set<string> stopwords) {
    this->k = k;
    this->stopwords = stopwords;
}


int main () {

  return 0;
}
