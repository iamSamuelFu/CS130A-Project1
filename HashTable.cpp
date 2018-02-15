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
			for (int i = index + 1; !found; i++) {
				i = i % table_size;

				if (table[i] == NULL) {
					found = true;
					result = -1;
				}

				if (table[i]->word == "-1" )
					continue;
					
				else if (table[i]->word == word) {
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
	Node* toDelete = table[searchWord(word)];
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
		if (table[index] != NULL && table[index]->word != "-1") 
			writer << table[index]->word << std::endl;

	writer.close();
}

void HashTable::searchRange(std::string word1, std::string word2) {
	int index_word1 = searchWord(word1);
	int index_word2 = searchWord(word2);

	// Check if word1 and word2 exist

	// Print word of node from index of word1 to index of word2
	for (int index = 0; index < table_size; index++) {
		if (table[index] == NULL || table[index]->word == "-1") 
			continue;
		
		if (table[index]->word.compare(word1) >= 0 && table[index]->word.compare(word2) <= 0 )
			std::cout << table[index]->word << std::endl;
	}
	std::cout << table[index_word2]->word << std::endl;
	// std::cout<< "Index of word1: " << index_word1 << " Index of word2: " << index_word2 << std::endl;
}

int HashTable::hashIndex(std::string word) {
	int num = 0;
	for (int i = 0; i < word.size(); i++)
		num += int(word[i]);
	return num % table_size;
}

bool HashTable::nodeComparison(Node* n1, Node* n2) {
	if (n1 == NULL)
		return false;
	if (n2 == NULL)
		return true;
	return compare(n1->word,n2->word) < 0;
}

int HashTable::compare(std::string s1, std::string s2) {
    int length = s1.size() >= s2.size() ? s1.size() : s2.size();
    for (int i = 0; i < length; i++) {
        
        if (i >= s1.size())
            return -1;
        if (i >= s2.size())
            return 1;
        if (s1[i] > s2[i])
            return 1;
        if (s1[i] < s2[i])
            return -1;
    }
    return 0;
}
