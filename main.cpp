#include <ctime>
#include <cstdlib>
#include "Shuffler.h"
#include "Shingles.h"

using namespace std;

int main() {
    srand(time(NULL));
    string cluster;
	cout << "Especifica el cluster de documents (directori):";
	cin >> cluster;
	Shingles sh(cluster,9);
	sh.readCharShingle();
	map<string, set<int> >::iterator it;
	it = sh.getBegin();
	while(it != sh.getEnd()){
		++it;
	}
}
