#include <vector>
#include <map>
#include <set>
#include <utility>
#include "shuffler.h"
using namespace std;

class Signatures{
private:
	vector<vector<int> > S;
	vector<shuffler> F;
	set<pair<int,int> > candidates;
	int rows;	
	int buckets;
public:
	Signatures(int,int,int,int);
	void computeSignatures(map<string, set<int> >::iterator);  
	set<pair<int,int> >::iterator getPairs();
	set<pair<int,int> >::iterator getEnd();
	void LHS();
	double computeSignatureSimilarity(int,int);
};