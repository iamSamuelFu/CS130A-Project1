#include "BST.h"

BST::BST() {
	root = NULL;
}

BST::~BST() {

}

bool BST::searchWord(std::string word) {
	return searchWord(root, word);
}

bool BST::searchWord(Node* node, std::string word) {

	if (node->word == word) {
		return true;
	}

    if (node->word > word) {

        if (node->left == NULL)
            return false;
        return searchWord(node->left, word);
    }
    else {

        if (node->right == NULL)
            return false;
        return searchWord(node->right, word);
    }
}

void BST::insertWord(std::string word) {

	if (root == NULL) {
		root = new Node(word);
		root->right = NULL;
	}
	else {
		insertWord(root, word);
	}
}

void BST::insertWord(Node* node, std::string word) {

	if (node->word == word) {
		node->counter ++;
		return;
	}

    if (node->word > word) {

        if (node->left == NULL) {
            node->left = new Node(word);
            return;
        }
        return insertWord(node->left, word);
    }
    else {

        if (node->right == NULL) {
            node->right = new Node(word);
            return;
        }
        return insertWord(node->right, word);
    }
}

void BST::deleteWord(std::string word) {

}

void BST::sortWords(std::string filename) {
	sortWords(root, filename);
}

void BST::sortWords(Node* node, std::string filename) {
	
	if (node == NULL)
		return;

	sortWords(node->left, filename);

	std::ofstream writer;
	writer.open(filename, std::ios_base::app);
	writer << node->word << std::endl;
	writer.close();

	sortWords(node->right, filename);
}

void BST::searchRange(std::string word1, std::string word2) {
	searchRange(root, word1, word2);
}

void BST::searchRange(Node* node, std::string word1, std::string word2) {

	if (node == NULL)
		return;

	searchRange(node->left, word1, word2);

	if (node->word >= word1 && node->word <= word2)
		std::cout << node->word << std::endl;

	searchRange(node->right, word1, word2);
}