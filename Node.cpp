#include "Node.h"

Node::Node() {
	this->word = "";
	this->counter = 0;
	this->left = NULL;
	this->right = NULL;
}

Node::Node(std::string word) {
	this->word = word;
	this->counter = 0;
	this->left = NULL;
	this->right = NULL;
}

Node::Node(std::string word, int counter) {
	this->word = word;
	this->counter = counter;
	this->left = NULL;
	this->right = NULL;
}
