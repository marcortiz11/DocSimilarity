#include <set>
#include <list>
#include <fstream>
#include <string>

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
    kwordstream(int k=3, set<string> stopwords=set<string>());
    string getshingle();
};
