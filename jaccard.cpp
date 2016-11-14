#include <set>
#include <string>

using namespace std;

double jaccard(const set<string>& d1, const set<string>& d2) {
    int ncommon = 0;
    set<string>::iterator it1 = d1.begin(), it2 = d2.begin();
    while (it1!=d1.end() and it2!=d2.end()) {
        if (*it1 < *it2) {
            it1++;
        } else if (*it1 > *it2) {
            it2++;
        } else {
            it1++;
            it2++;
            ncommon++;
        }
    }
    return ncommon/double(d1.size()+d2.size()-ncommon);
}
