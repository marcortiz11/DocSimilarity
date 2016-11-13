#include "Shingles.h"

	//String->Int
int Shingles::compress(string shingle){
	/*int value = 7;
	for(int i = 0; i < shingle.size(); ++i){
		value = value*(shingle[i]);
	}
	return value % SIZE_HASH;*/
}

void Shingles::save(char* buffer, int id, int idx){
	string shingle="";
	for (int i = 1; i <= (this->k); ++i)
	{
		shingle+=buffer[(idx+i)%(this->k)];
	}
	if(US.find(shingle) != US.end()){
		US[shingle].insert(id);
	}else{
		set<int> ids = {id};
		US[shingle] = ids;
	}
}

Shingles::Shingles(string cluster, int k){
	this->cluster = cluster;
}

void Shingles::readCharShingle(){
	int i = 1;
	bool mes_arxius = true;
	char buff[this->k];
	while(mes_arxius)
	{
		stringstream ss;
		ss << this->cluster << "/" << std::to_string(i) << ".txt";
		const char* path = (ss.str()).c_str();
		ifstream file(path);
		int ch = 0; char c;
		while(ch < k and file.get(c)){
				if(isalnum(c)){
					buff[ch] = tolower(c);
					++ch;
				}
		}
		mes_arxius = ch > 0;
		save(buff,i,ch);
		while(file.get(c)){
			if(isalnum(c)){
				ch = (++ch)%k;
				buff[ch] = tolower(c);	
				save(buff,i,ch);
			}
		} 
		++i;
		cout << "Llegint document: " << i << "\n";
	}
}

void Shingles::readWordShingle(string stopWords){
	regex filter("[a-z][A-Z][0-9]"); 
	//JUANCHO
}

map<string, set<int> >::iterator Shingles::getBegin(){
	return US.begin();
}

map<string, set<int> >::iterator Shingles::getEnd(){
	return US.end();
}