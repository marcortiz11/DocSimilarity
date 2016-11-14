#include "Signatures.h"
#include <utility>

Signatures::Signatures(int l, int buckets, int rows, int nDocs){
	F = vector<Shuffler>(l,Shuffler(rows));
	S = vector<vector<int> > (rows, vector<int>(nDocs,-1));
}

//Pre: it és un iterador al begin del diccionari
void Signatures::computeSignatures(map<string, set<int> >::iterator it){
	for(int i = 0; i < rows; ++i){
		set<int> docsSet = it->second;
		for(int h = 0; h < F.size(); ++h){
			int r = F[h].getpos(i);
			set<int> docsSet = it->second;
			for (std::set<int>::iterator d=docsSet.begin(); d!=docsSet.end(); ++d)
				if(S[h][(*d)] == -1 or S[h][(*d)] > r) S[h][(*d)] = r;
			}
		}
		++it;
	}
}

void Signatures::LHS(){
	//Computa un set de pairs candidats
	int hashFun = S.size(); 
	int docs = S[0].size();
	int block = hashFun / this->buckets;
	for(int b = 0; b < this->buckets; ++b){
		vector<<vector<int> > Buckets = vector<vector<int> > ();
		for(int d = 0; d < docs; ++d){
			int pos = 0;
			int i = 0;
			for(int h = b*block; h < (b+1)*hashFun/docs; ++h){
				pos += S[h][d] * (rows ^ i);
				++i;
			}
			pos = pos % block; //Position of sub-signature in a set of buckets
			for(int j = 0; j < Buckets[pos].size(); ++j){
				pair<int,int> p = Buckets[pos][j] < Buckets[pos][d] ? make_pair(j,d) : make_pair(d,j);
				if(not candidates.count(p)) candidates.insert(p);
			}
		}
	}
}

double Signatures::computeSignatureSimilarity(int doc1, int doc2){
	double equals = 0;
	double total = 0;
	for (int r = 0; r < rows; ++r)
	{
		equals += (S[r][doc1] == S[r][doc2] && S[r][doc1]) ? 1 : 0;
		total += (S[r][doc2] || S[r][doc1]) ? 1 : 0;
	}
	return equals/total;
}


map<string,pair<int,int> >::iterator Signatures::findPairs(){
	return candidates.begin();
}
