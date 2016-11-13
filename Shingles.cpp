#include "Shingles.h"

	//String->Int
int Shingles::compress(string shingle){
	/*int value = 7;
	for(int i = 0; i < shingle.size(); ++i){
		value = value*(shingle[i]);
	}
	return value % SIZE_HASH;*/
}

void Shingles::save(char* buffer, int id){
	string shingle(buffer);
	if(US.find(shingle) != US.end()){
		US[shingle].insert(id);
	}else{
		set<int> ids = {id};
		US[shingle] = ids;
	}
}

Shingles::Shingles(string cluster){
	this->cluster = cluster;
}

void Shingles::readCharShingle(int k){
	int i = 1;
	stringstream ss;
	ss << this->cluster << "/" << std::to_string(i) << ".txt";
	const char* path = (ss.str()).c_str();
	bool mes_arxius = true;
	char buff[k];
	while(mes_arxius)
	{
		char c; 
		ifstream file(path);
		int ch = 0;
		cout << c;
		while(ch < k and file.get(c)){
				buff[ch] = c;
				++ch;
		}
		if(ch >= k){
			//guarda en el diccionario
			save(buff,i);
			while(file.get(c)){
				for(int j = 0; j < k-1; ++j){
					buff[j] = buff[j+1];
				}
				buff[k-1] = c;	
				save(buff,i);
			}	
		} 
		mes_arxius = ch > 0;
		++i;
		stringstream ss;
		ss << this->cluster << "/" << std::to_string(i) << ".txt";
		path = (ss.str()).c_str();
	}
}

void Shingles::readWordShingle(int k, string stopWords){
	//JUANCHO
}

map<string, set<int> >::iterator Shingles::getBegin(){
	return US.begin();
}

map<string, set<int> >::iterator Shingles::getEnd(){
	return US.end();
}