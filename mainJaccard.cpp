#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "shinglestream.h"
#include <cmath>
#include "jaccard.h"
#include "docstore.h"

using namespace std;

void getBasicInfo(vector<string>& paths, bool& word, int& k) {
	cout << "Indica el path del document 1 (elteudirectori/doc1.txt):\n";
	cin >> paths[0];
	cout << "Indica el path del document 2 (elteudirectori/doc2.txt):\n";
	cin >> paths[1];
	cout << "Descomposició del document en words=1 o chars=0\n";
	cin >> word;
	cout << "De quin tamany són els shingles?\n";
	cin >> k;
}

int main() {
	vector<string> paths(2);
	bool word;
	int k;
	getBasicInfo(paths,word,k);
	vector< set<string> > shingles(2);
	
	if (word) {
		kwordstream ss(k, getwordsfromfile("data/english_stopwords.txt"));
		
		for (int i = 0; i < 2; ++i) {
			string s = paths[i];
			ss.open(s);
			while (not ss.isdone()) {
				string shingl = ss.getshingle();
				shingles[i].insert(shingl);
			}
			ss.close();
		}
	}
	else {
		kcharstream ss(k);
	
		for (int i = 0; i < 2; ++i) {
			string s = paths[i];
			ss.open(s);
			while (not ss.isdone()) {
				string shingl = ss.getshingle();
				shingles[i].insert(shingl);
			}
			ss.close();
		}
	}
	
	cout << "Similitud de Jaccard: " << jaccard(shingles[0],shingles[1]) << endl;
}
