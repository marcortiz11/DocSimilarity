#include <string>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <fstream>
#include <regex>

using namespace std;

class Shingles{
private:
	map<string, set<int> > US; //UniversalShingles
	string cluster;
	void save(char*,int,int);
	int k;
	//String->Int
	int compress(string);
public:
	Shingles(string, int);
	void readCharShingle();
	void readWordShingle(string);
	map<string, set<int> >::iterator getBegin();
	map<string, set<int> >::iterator getEnd();

};