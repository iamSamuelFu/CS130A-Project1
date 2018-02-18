#include "HashTable.h"
#include <algorithm>
#include <vector>

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

int HashTable::searchWord(std::string word) {
	int index = hashIndex(word);
	int result = -1;

	if (table[index] != NULL) { 
		if (table[index]->word == word) {
			result = index;
		}	
		else {

			bool found = false;
			int i = 0;
			for (int times = 1; !found; times++) {
				i = index + times * times;
				i = i % table_size;

				if (table[i] == NULL) {
					found = true;
					result = -1;
				}
				else if (table[i]->word != "-1" && table[i]->word == word) {
					found = true;
					result = i;
				}
			}						
		}	
	}
	return result;
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
			int i = 0;
			for (int times = 1; !inserted; times++) {
				i = index + times * times;
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
	int index = searchWord(word);
	if (index == -1)
		return NULL;

	Node* toDelete = table[index];
	toDelete->word = "-1";
	toDelete->counter = 0;
	return toDelete;
}

void HashTable::sortWords(std::string filename) {
	std::vector<Node*> myVector(table, table + table_size);

	std::sort(myVector.begin(), myVector.end(), nodeComparison);

	// print out words
	std::ofstream writer;
	writer.open(filename, std::ios_base::app);

	for (int index = 0; index < table_size; index++)
		if (myVector[index] != NULL && myVector[index]->word != "-1")
			writer << myVector[index]->word << std::endl;

	writer.close();
}

void HashTable::searchRange(std::string word_lower, std::string word_upper) {

	if (word_lower > word_upper) {
		std::string temp = word_lower;
		word_lower = word_upper;
		word_upper = temp;
	}

	// Print word of node from index of word1 to index of word2
	for (int index = 0; index < table_size; index++) {
		if (table[index] == NULL || table[index]->word == "-1") 
			continue;
		
		if (table[index]->word.compare(word_lower) >= 0 && table[index]->word.compare(word_upper) <= 0)
			std::cout << table[index]->word << std::endl;
	}
}

int HashTable::hashIndex(std::string word) {
	int num = 0;
	for (int i = 0; i < word.size(); i++)
		num += int(word[i]) - int('a');
	return num % table_size;
}

bool HashTable::nodeComparison(Node* n1, Node* n2) {
	if (n1 == NULL)
		return false;
	if (n2 == NULL)
		return true;
	return n1->word.compare(n2->word) < 0;
}
