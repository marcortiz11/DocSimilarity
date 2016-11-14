#include "Shuffler.h"
#include "Shingles.sh"

class Signatures{
private:
	vector<vector<int> > S;
	vector<Shuffler> F;
	set<pair<int,int> > candidates;
	int rows;
	int buckets;
public:
	Signatures(int,int,int,int)
	void computeSignatures(map<string, set<int> >::iterator);
	map<string,pair<int,int> >::iterator findPairs();
	double computeSignatureSimilarity(pair<int,int>);
}