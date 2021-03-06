#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <set>

using namespace std;

class shinglestream {

protected:
    int k;

public:
    virtual bool isdone() = 0;
    virtual void open(const string& filename) = 0;
    virtual void close() = 0;
    virtual string getshingle() = 0;
};

//Reads k-shingles composed of characters
class kcharstream : public shinglestream {

private:
    ifstream ifs;
    list<char> buffer;

public:
    bool isdone();
    void open(const string& filename);
    void close();
    kcharstream(int k=3);
    string getshingle();
};

bool kcharstream::isdone() {
    char chr;
    int wspaces = 0;
    while ((buffer.size() != k) and ifs) {
        chr = ifs.get();
        bool wspace = isspace(chr);
        wspaces = wspace ? wspaces+1 : 0;
        if (isalnum(chr) or wspace) {
            buffer.push_back(tolower(chr));
        }
        if (wspaces == 2) {
            buffer.pop_back();
            wspaces = 1;
        }
    }
    return not ifs;
}

string kcharstream::getshingle() {
    if (isdone()) {
        cout << "Error: unexpected end of file" << endl;
        throw 0;
    }
    string res = "";
    for (const char& s : buffer) {
        res += s;
    }
    if (not buffer.empty()) {
        buffer.pop_front();
    }
    return res;
}

void kcharstream::open(const string& filename) {
    ifs.open(filename, ifstream::in);
}

void kcharstream::close() {
    ifs.close();
}

kcharstream::kcharstream(int k) {
    this->k = k;
}

//Reads k-shingles composed of words
class kwordstream : public shinglestream {

private:
    ifstream ifs;
    list<string> buffer;
    set<string> stopwords;
    string clean(string& dirtyboy);

public:
    bool isdone();
    void open(const string& filename);
    void close();
    string getshingle();
    kwordstream(int k=3, set<string> stopwords=set<string>());
};

string kwordstream::clean(string& dirtyboy) {
    string goodboy = "";
    for (const char& c : dirtyboy) {
        if (isalnum(c)) {
            goodboy += tolower(c);
        }
    }
    return goodboy;
}

bool kwordstream::isdone() {
    string word;
    while ((buffer.size() != k) and ifs) {
        ifs >> word;
        word = clean(word);
        if (word.size() == 0) {
            continue;
        }
        buffer.push_back(word);
        if (not stopwords.count(buffer.front())) {
            buffer.pop_front();
        }
    }
    return not ifs;
}

string kwordstream::getshingle() {
    if (isdone()) {
        cout << "Error: unexpected end of file" << endl;
        throw 0;
    }
    string res = "";
    for (const string& s : buffer) {
        res += s + " ";
    }
    res.pop_back();
    if (not buffer.empty()) {
        buffer.pop_front();
    }
    return res;
}

void kwordstream::open(const string& filename) {
    ifs.open(filename, ifstream::in);
}

void kwordstream::close() {
    ifs.close();
}

kwordstream::kwordstream(int k, set<string> stopwords) {
    this->k = k;
    this->stopwords = stopwords;
}
