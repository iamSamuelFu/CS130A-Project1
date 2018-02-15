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
	int searchWord(std::string word);
	void insertWord(std::string word);
	Node* deleteWord(std::string word);
	void sortWords(std::string filename);
	void searchRange(std::string word_lower, std::string word_upper);

private:
	int hashIndex(std::string word);
	static bool nodeComparison(Node* n1, Node* n2);
	
	int table_size;
	Node** table;
};

#endif