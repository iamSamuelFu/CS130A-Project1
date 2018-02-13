#ifndef NODE_H
#define NODE_H
#include <string>

class Node {
public:
	Node();
	Node(std::string word);
	Node(std::string word, int counter);
	
	int counter;
	std::string word;
	Node* left;
	Node* right;
};

#endif