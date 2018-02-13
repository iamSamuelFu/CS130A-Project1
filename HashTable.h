#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include "Node.h"

class HashTable {
public:
	HashTable(int size);
	~HashTable();
	Node* searchWord(std::string word);
	void insertWord(std::string word);
	Node* deleteWord(std::string word);
	void sortWords(std::string filename);
	void searchRange(std::string word1, std::string word2);

// private:
	int hashIndex(std::string word);
	
	int table_size;
	Node** table;
};

#endif