#include <string>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <fstream>

using namespace std;

class Shingles{
private:
	map<string, set<int> > US; //UniversalShingles
	string cluster;
	void save(char*,int);
	//String->Int
	int compress(string shingle);
public:
	Shingles(string cluster);
	void readCharShingle(int k);
	void readWordShingle(int k, string stopWords);
	map<string, set<int> >::iterator getBegin();
	map<string, set<int> >::iterator getEnd();

};