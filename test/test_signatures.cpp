#include "../shinglestream.h"
#include "../Signatures.h"
#include <ctime>
#include <iostream>
#include <cmath>
#include "../jaccard.h"

using namespace std;

void params_lectura(int& k, string& path, bool& word){
	cout << "Indica el path del conjunt de documents:" << "\n";
	cin >> path;
	cout << "Descomposició del document en words=1 o chars=0" << "\n";
	cin >> word;
	cout << "De quin tamany són els shingles?" << "\n";
	cin >> k;
}

void params_signatures(int& f, int& b){
	cout << "Indica el tamany de les signatures" << "\n";
	cin >> f;
	cout << "Indica el nombre de buckets" << "\n";
	cin >> b;
}

int main() {
    srand(time(NULL));
    int k,h;
    string path;
    bool word;
    params_lectura(k,path,word);
	kcharstream ss(k);
	map<string,set<int> > shingles;
	map<int,set<string> > shingles2;
	int rows = 0;
	//Leiendo novelas
	for(int i = 1; i <= 20; ++i){
		string s = path + to_string(i) + ".txt";
		ss.open(s);
		while(not ss.isdone()){
			string shingl = ss.getshingle();
			if(shingles.count(shingl)){
				shingles2[i].insert(shingl);
				shingles[shingl].insert(i);
			}else{
				++rows;
				shingles2[i] = set<string>();
				shingles2[i].insert(shingl);
				shingles[shingl] = set<int>{i};
			}
		}
		ss.close();
	}
	int f,b;
	cout << rows << endl;
	params_signatures(f,b);
	Signatures s(f,rows,20);
	s.set_buckets(b);
	s.computeSignatures(shingles.begin());
	s.LHS();
	set<pair<int,int> >::iterator beg = s.getPairs();
	set<pair<int,int> >::iterator end = s.getEnd();
	cout << "Possible pairs:" << endl;
	while(beg != end){
		cout << "jaccard " << jaccard(shingles2[(*beg).first], shingles2[(*beg).second]) << endl;
		cout << (*beg).first << " " << (*beg).second << " Similarity:" << s.computeSignatureSimilarity((*beg).first,(*beg).second) << endl;
		++beg;
	}
	cout << "Threshold " << pow(1/double(b),(1/double(rows/double(b)))) << endl;
}
