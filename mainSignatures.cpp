#include "shinglestream.h"
#include "Signatures.h"
#include <ctime>
#include <iostream>
#include <cmath>
#include "jaccard.h"
#include "docstore.h"

using namespace std;

void getBasicInfo(string& path, int& num, bool& word, int& k){
	cout << "Indica el path dels documents (elteudirectori/):\n";
	cin >> path;
	cout << "Indica el nombre de documents a analitzar:\n";
	cin >> num;
	cout << "Descomposició del document en words=1 o chars=0:\n";
	cin >> word;
	cout << "De quin tamany són els shingles?\n";
	cin >> k;
}

void getSignatureInfo(int& f, int& b){
	cout << "Indica el tamany de les signatures:\n";
	cin >> f;
	cout << "Indica el nombre de buckets:\n";
	cin >> b;
}

int main() {
    int k, num;
    string path;
    bool word;
    getBasicInfo(path,num,word,k);
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
	
	int f, b;
	getSignatureInfo(f,b);
	Signatures s(f,rows,num);
	s.set_buckets(b);
	s.computeSignatures(shingles.begin());
	s.LHS();
	set<pair<int,int> >::iterator beg = s.getPairs();
	set<pair<int,int> >::iterator end = s.getEnd();
	cout << "Possibles parelles:" << endl;
	while (beg != end) {
		cout << "\tSimilitud de Jaccard: " << jaccard(shingles2[(*beg).first], shingles2[(*beg).second]) << endl;
		cout << "\tDocs: " << (*beg).first << "," << (*beg).second << " | Valor: " << s.computeSignatureSimilarity((*beg).first,(*beg).second) << endl;
		cout << endl;
		++beg;
	}
	cout << "Threshold: " << pow(1/double(b),(1/double(rows/double(b)))) << endl;
}
