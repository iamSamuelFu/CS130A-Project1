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
	Node* searchWord(std::string word);
	void insertWord(std::string word);
	Node* deleteWord(std::string word);
	void sortWords(std::string filename);
	void searchRange(std::string word1, std::string word2);

private:
	void insertWord(Node* node, std::string word);
	void sortWords(std::ofstream& writer, Node* node, std::string filename);
	Node* searchWord(Node* node, std::string word);
	void searchRange(Node* node, std::string word1, std::string word2);
	Node* deleteWord(Node* node, std::string word);
	void deleteAll(Node* node);
	Node* root;

};

#endif
