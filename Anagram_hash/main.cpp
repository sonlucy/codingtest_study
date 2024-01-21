#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include"HashMap.h"
using namespace std;


int main() {
	HashMap hash;
	int key;
	string str, strsort;
	ifstream fin;
	fin.open("3k_words.txt");
	if (!fin) {
		exit(1);
	}
	
	///////////////////////////////////////////////
	while (!fin.eof()) {
		fin >> str;  //3k_words.txt 파일로부터 문자열 읽어서
		cout << str << endl;
		strsort = hash.alphaSort(str);  //문자열(단어)을 정렬하고
		hash.Insert(strsort, str);  ////////////////////////////////////////

	}
	fin.close();

	ofstream fout;
	fout.open("output.txt");
	if (!fout) {
		exit(1);
	}
	ifstream fin2;
	string str2;
	fin2.open("input.txt");
	if (!fin2) {
		exit(1);
	}

	while (!fin2.eof()) {
		getline(fin2, str2);
		strsort = hash.alphaSort(str2);
		fout << endl <<"[" << str2 << "] ";
		hash.search(strsort, fout);
	}
	fout.close();





	_getch();
	return 0;
}
