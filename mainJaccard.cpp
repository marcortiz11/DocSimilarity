#include <time.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "shinglestream.h"
#include <cmath>
#include "jaccard.h"
#include <map>
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
	
	cout << "Comparar un document amb els altres = ID_doc; comparar tots amb tots = 0" << endl;
	int id;
	cin >> id;
	
	if(not id){
		for (int i = 1; i <= num; ++i) {
			for (int j = i+1; j<=num; ++j){
				cout << "Docs: " << i << "," << j<< " | Valor: " << jaccard(shingles2[i],shingles2[j]) << endl;
			}
		}
	}else{
		for(int i = 1; i<=num; ++i){
			if (id != i) {
				cout << "Docs: " << id << "," << i << " | Valor: " << jaccard(shingles2[id],shingles2[i]) << endl;
			}
		}
	}
	
	
	cout << "Temps d'execució: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
}
