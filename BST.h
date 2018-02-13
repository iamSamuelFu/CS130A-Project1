#ifndef BST_H
#define BST_H

class BST {
public:
	BST();
	~BST();
	bool searchWord(std::string word);
	void insertWord(std::string word);
	void deleteWord(std::string word);
	std::string sortWord();
	std::string searchRange(std::string word1, std::string word2);
};

#endif