#include "HashTable.h"

HashTable::HashTable(int size) {
	this->table_size = int(3.0 / 2 * size);
	table = new Node*[this->table_size];
	for (int i = 0; i < table_size; i++)
		table[i] = NULL;
}

HashTable::~HashTable() {
	for (int i = 0; i < table_size; i++) {
		delete table[i];
		table[i] = NULL;
	}
	delete table;
}

Node* HashTable::searchWord(std::string word) {

}

void HashTable::insertWord(std::string word) {
	int index = hashIndex(word);
	// std::cout << index << ", " << word;

	if (table[index] == NULL) {
		table[index] = new Node(word);
	}
	else {

		// std::cout << "p1" << (table[index]->word == word) << std::endl;
		if (table[index]->word == word) {
			table[index]->counter++;
		}
		else {

			bool inserted = false;
			for (int i = index + 1; !inserted; i++) {
				i = i % table_size;

				if (table[i] == NULL) {
					table[i] = new Node(word);
					inserted = true;
				}
				else if (table[i]->word == word) {
					table[index]->counter++;
					inserted = true;
				}
			}
		}

	}
}

Node* HashTable::deleteWord(std::string word) {

}

void HashTable::sortWords(std::string filename) {

}

void HashTable::searchRange(std::string word1, std::string word2) {

}

int HashTable::hashIndex(std::string word) {
	int num = 0;
	for (int i = 0; i < word.size(); i++)
		num += int(word[i]);
	return num % table_size;
}