#include "shinglestream.h"
#include "Signatures.h"
#include <time.h>
#include <iostream>
#include <cmath>
#include "jaccard.h"
#include "docstore.h"

using namespace std;

void getBasicInfo(string& path, int& num, bool& word, int& k, int& f){
	cout << "Indica el path dels documents (elteudirectori/):\n";
	cin >> path;
	cout << "Indica el nombre de documents a analitzar:\n";
	cin >> num;
	cout << "Descomposició del document en words=1 o chars=0:\n";
	cin >> word;
	cout << "De quin tamany són els shingles?\n";
	cin >> k;
	cout << "Indica el tamany de les signatures:\n";
	cin >> f;
}

int main() {
	clock_t tStart = clock();
    int k, num, f;
    string path;
    bool word;
    getBasicInfo(path,num,word,k,f);
    map<string,set<int> > shingles;
	map<int,set<string> > shingles2;
	int rows = 0;
	
	if (word) {
		kwordstream ss(k, getwordsfromfile("data/english_stopwords.txt"));
		
		for (int i = 1; i <= num; ++i) {
			string s = path + to_string(i) + ".txt";
			ss.open(s);
			while (not ss.isdone()) {
				string shingl = ss.getshingle();
				if (shingles.count(shingl)) {
					shingles2[i].insert(shingl);
					shingles[shingl].insert(i);
				}
				else {
					++rows;
					shingles2[i] = set<string>();
					shingles2[i].insert(shingl);
					shingles[shingl] = set<int>{i};
				}
			}
			ss.close();
		}
	}
	else {
		kcharstream ss(k);
	
		for (int i = 1; i <= num; ++i) {
			string s = path + to_string(i) + ".txt";
			ss.open(s);
			while (not ss.isdone()) {
				string shingl = ss.getshingle();
				if (shingles.count(shingl)) {
					shingles2[i].insert(shingl);
					shingles[shingl].insert(i);
				}
				else {
					++rows;
					shingles2[i] = set<string>();
					shingles2[i].insert(shingl);
					shingles[shingl] = set<int>{i};
				}
			}
			ss.close();
		}
	}
	
	Signatures s(f,rows,num);
	s.computeSignatures(shingles.begin());
	
	for (int i = 1; i <= num; ++i) {
		for (int j = i+1; j <= num; ++j) {
			cout << "Docs: " << i << "," << j << " | Valor: " << s.computeSignatureSimilarity(i,j) << endl;
		}
	}
	
	cout << "Temps d'execució: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
}