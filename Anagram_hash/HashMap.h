#ifndef HASH_MAP_H
#define HASH_MAP_H
#include"HashNode.h"
#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
#include<math.h>
#include <fstream>
#include <locale>
using namespace std;
#include <fstream>
const int TABLE_SIZE = 200000;
static int countBin = 0;
static const size_t InitialFNV = 2166136261U;
static const size_t FNVMultiple = 16777619;
class HashMap
{
private:

	HashNode** htable;

public:
	HashMap();
	~HashMap();

	int HashFunc(string key);
	
	string alphaSort(string w);

	void Insert(string key, string word);
	void search(string key, ofstream&);


};

//destructor 
HashMap::~HashMap() {
	for (int i = 0; i < TABLE_SIZE; ++i) {
		HashNode* entry = htable[i];
		while (entry != NULL) {
			HashNode* prev = entry;
			entry = entry->next;
			delete prev;
		}
	}
	delete[] htable;
}
//constructor
HashMap::HashMap()
{
	htable = new HashNode * [TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		htable[i] = NULL;
}



string HashMap::alphaSort(string w)
{
	sort(w.begin(), w.end());
	return w;
}



//myhash function 1
int HashMap::HashFunc(string key)
{

	int hashVal = 0;

	for (int i = 0; i < key.length(); i++)
		hashVal = 37 * hashVal + key[i];
	hashVal %= TABLE_SIZE;
	if (hashVal < 0)
		hashVal += TABLE_SIZE;

	return hashVal;
}



//insert function for hash table
void HashMap::Insert(string key, string word) {
	int hash_val = HashFunc(key);
	if (htable[hash_val] == nullptr)
	{
		htable[hash_val] = new HashNode();
	}
	htable[hash_val]->insert(key, word);
}

void HashMap::search(string key, ofstream& fout)
{

	int hash_val = HashFunc(key);  //
	if (htable[hash_val] != nullptr)
	{
		HashNode* node = htable[hash_val]->search(key);
		fout << "정렬한 문자열:" << key << ", ";
		if (node->anagram != nullptr)
		{

			fout << "3k_words.txt파일에서의 애나그램 단어: " << node->anagram->val << " ";
			node->anagram = node->anagram->next;
		}

		fout << endl;
	}
	else
	{
		fout << "정렬한 문자열:" << key << ", ";
		fout << "애나그램 단어 없음" << endl;
	}
}



#endif