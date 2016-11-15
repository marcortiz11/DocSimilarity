#include "shinglestream.h"
#include "Signatures.h"
#include <time.h>
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

void getSignatureInfo(int& f, int& b, double& t, string& s){
	cout << "Indica el tamany de les signatures:\n";
	cin >> f;
	cout << "Indica el nombre de buckets (b) o el threshold (t):\n";
	cin >> s;
	cout << "Dona el valor d'aquest" << endl;
	if (s == "b") cin >> b;
	else cin >> t;
}

int main() {
	clock_t tStart = clock();
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
	double t;
	string torb;
	getSignatureInfo(f,b,t,torb);
	Signatures s(f,rows,num);
	if (torb == "b") s.set_buckets(b);
	else s.set_threshold(t);
	
	s.computeSignatures(shingles.begin());
	cout << "Comparar un document amb els altres = ID_doc; comparar tots amb tots = 0" << endl;
	int id;
	cin >> id;
	if (id == 0) s.LHS();
	else s.LHS(id);
	set<pair<int,int> >::iterator beg = s.getPairs();
	set<pair<int,int> >::iterator end = s.getEnd();
	cout << "Possibles parelles:" << endl;
	while (beg != end) {
		cout << "\tDocs: " << (*beg).first << "," << (*beg).second << " | Valor: " << s.computeSignatureSimilarity((*beg).first,(*beg).second) << endl;
		cout << endl;
		++beg;
	}
	if (torb == "b") cout << "Threshold: " << pow(1/double(b),(1/double(f/double(b)))) << endl;
	else cout << "Threshold: " << t << endl;
	cout << "Temps d'execució: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
}
