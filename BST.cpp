#include "BST.h"

BST::BST() {
	root = NULL;
}

BST::~BST() {
	deleteAll(root);
}

void BST::deleteAll(Node* node) {
	if (node == NULL)
		return;

	deleteAll(node->left);
	deleteAll(node->right);
	
	delete node;
	return;
}

Node* BST::searchWord(std::string word) {
	return searchWord(root, word);
}

Node* BST::searchWord(Node* node, std::string word) {

	if (node->word == word) {
		return node;
	}

    if (node->word > word) {

        if (node->left == NULL)
            return NULL;
        return searchWord(node->left, word);
    }
    else {

        if (node->right == NULL)
            return NULL;
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

Node* BST::deleteWord(std::string word) {
	deleteWord(root, word);
}

Node* BST::deleteWord(Node* node, std::string word) {
	
	if (node == NULL)
		return node;

	if (word < node->word)
		node->left = deleteWord(node->left, word);

	else if (word > node->word)
		node->right = deleteWord(node->right, word);

	else {

		if (node->left == NULL) {
			Node* savedNode = node->right;
			delete node;
			return savedNode;
		}
		else if (node->right == NULL){
			Node* savedNode = node->left;
			delete node;
			return savedNode;
		}
		else {

			//Get leftmost child on right subtree
			Node* temp = node->right;
			while (temp->left != NULL)
				temp = temp->left;

			//Replace node data with temp data
			node->word = temp->word;
			node->counter = temp->counter;
			temp = NULL;
			delete temp;
		}
	}

	return node;
}

void BST::sortWords(std::string filename) {
	std::ofstream writer;
	writer.open(filename, std::ios_base::app);
	sortWords(writer, root, filename);
	writer.close();
}

void BST::sortWords(std::ofstream& writer, Node* node, std::string filename) {
	
	if (node == NULL)
		return;

	sortWords(writer, node->left, filename);

	writer << node->word << std::endl;

	sortWords(writer, node->right, filename);
}

void BST::searchRange(std::string word1, std::string word2) {
	searchRange(root, word1, word2);
}

void BST::searchRange(Node* node, std::string word1, std::string word2) {

	if (node == NULL)
		return;

	if (word1 > word2) {
		std::string temp = word1;
		word1 = word2;
		word2 = temp;
	}

	searchRange(node->left, word1, word2);

	if (node->word >= word1 && node->word <= word2)
		std::cout << node->word << std::endl;

	searchRange(node->right, word1, word2);
}
