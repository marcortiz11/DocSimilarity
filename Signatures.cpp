#include "Signatures.h"
#include <iostream>
#include <cmath>

Signatures::Signatures(int l, int nshingles, int nDocs){
	for (int i = 0; i<l; ++i){
		shuffler sf(nshingles);
		cout << sf.coprime << endl;
		F.push_back(sf);
	}
	S = vector<vector<int> > (l, vector<int>(nDocs+1,-1));
	this->nshingles = nshingles;
	cout << "Threshold " << pow((1/double(buckets)),(1/double(double(l)/double(buckets)))) << endl;
}

void Signatures::set_buckets(int bs) {
	this->buckets = bs;
}

int buckets_search(int a, int b, int nshingles, double t) {
	float bands = (a+b)/2;
	if (a==b) {
		return bands;
	}
	double thresh = pow((1/bands), bands/nshingles);
	if (thresh < t) {
		return buckets_search(bands+1, b, nshingles, t);
	} else if (thresh > t) {
		return buckets_search(a, bands, nshingles, t);
	} else {
		return bands;
	}
}

void Signatures::set_threshold(double t) {
	int max = (nshingles-1)*2;
	this->buckets = buckets_search(1, max, nshingles, t);
}

//Pre: it és un iterador al begin del diccionari
void Signatures::computeSignatures(map<string, set<int> >::iterator it){
	for(int i = 0; i < nshingles; ++i){
		set<int> docsSet = it->second;
		for(int h = 0; h < F.size(); ++h){
			int r = F[h].shuffle(i);
			for (std::set<int>::iterator d=docsSet.begin(); d!=docsSet.end(); ++d){
				if(S[h][(*d)] == -1 or S[h][(*d)] > r) {
					S[h][(*d)] = r;
				}
			}
		}
		++it;
	}
	for(int i = 0; i<S.size(); ++i){
		for(int j = 1; j<S[0].size(); ++j){
			cout << S[i][j] << ",";
		}
		cout << endl;
	}
}

void Signatures::LHS() {
	int hashFun = F.size();
	int docs = S[0].size();
	int block = hashFun / this->buckets;
	for(int b = 0; b < this->buckets; ++b){
		map<string, vector<int> > Buckets;
		for(int d = 1; d < docs; ++d){
			string minisignature = "";
			for(int h = b*block; h < min(hashFun,(b+1)*block); ++h){
				minisignature += to_string(S[h][d]);
			}
			for(int j = 0; j < Buckets[minisignature].size(); ++j){
				pair<int,int> p = (Buckets[minisignature][j] < d) ? make_pair(Buckets[minisignature][j],d) : make_pair(d,Buckets[minisignature][j]);
				candidates.insert(p);
			}
			Buckets[minisignature].push_back(d);
		}
	}
}

void Signatures::LHS(int doc_id) {

}

double Signatures::computeSignatureSimilarity(int doc1, int doc2){
	double equals = 0;
	double total = 0;
	//cout << "COMPUTING SIMILARITY BETWEEN " << doc1 << " AND " << doc2 <<endl;
	for (int r = 0; r < F.size(); ++r)
	{
		equals += (S[r][doc1] == S[r][doc2]) ? 1 : 0;
		total++;
	}
	//cout << equals << "/" << total << endl;
	return equals/total;
}


set<pair<int,int> >::iterator Signatures::getPairs(){
	return candidates.begin();
}

set<pair<int,int> >::iterator Signatures::getEnd(){
	return candidates.end();
}
