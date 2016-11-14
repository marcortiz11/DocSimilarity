#include <set>
#include <string>

using namespace std;

set<string> getwordsfromfile(string filename);

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
