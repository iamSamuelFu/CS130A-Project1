#ifndef BST_H
#define BST_H
#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"

class BST {
public:
	BST();
	~BST();
	bool searchWord(std::string word);
	void insertWord(std::string word);
	void deleteWord(std::string word);
	void sortWords(std::string filename);
	void searchRange(std::string word1, std::string word2);

// private:
	void insertWord(Node* node, std::string word);
	void sortWords(Node* node, std::string filename);
	bool searchWord(Node* node, std::string word);
	void searchRange(Node* node, std::string word1, std::string word2);
	Node* root;

};

#endif