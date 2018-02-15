#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <regex>
#include <algorithm>
#include <ctime>
#include "BST.h"
#include "HashTable.h"
#include "Node.h"

std::string getFileContent(std::string filename);
void fillStopwords(std::vector<std::string>& list, std::string filename);
void getFiles(std::string folder, std::vector<std::string>& files);
bool listContains(std::vector<std::string> list, std::string str);
std::string cleanWord(std::string str);

int main() {

	//Clean output
	std::ofstream cleaner("output.txt");
	cleaner << "";
	cleaner.close();

	//Get list of stopwords
	std::vector<std::string> stopwords;
	fillStopwords(stopwords, "stopwords.txt");

	//Get all filenames
	std::vector<std::string> folders;
	std::vector<std::string> files;
	getFiles("hotels-small/", folders);
	for (int i = 0; i < folders.size(); i++)
		getFiles(folders[i] + "/", files);

	//Read all files to string
	std::string string = "";
	for (int i = 0; i < files.size(); i++)
		string += getFileContent(files[i]);

	//Read all words and clean out non-alphabet words
	std::vector<std::string> words;
	std::istringstream iss(string);
	for(std::string word; iss >> word;) {

		std::transform(word.begin(), word.end(), word.begin(),::tolower);
		word = cleanWord(word);
		if (word != "" && !listContains(stopwords, word))
			words.push_back(word);
	}

	//Insert words to hashtable
	HashTable table(words.size());
	for (int i = 0; i < words.size(); i++)
		table.insertWord(words[i]);
	std::cout << "done" << std::endl;

	//Sort words using hashtable
	table.sortWords("output.txt");


	//Insert words to BST
	BST tree;
	for (int i = 0; i < words.size(); i++)
		tree.insertWord(words[i]);

	//Main

	while (true) {

		int option;
		std::cin >> option;

		switch(option) {

			case 1: {
					std::string input1;
					std::cin >> input1;

					std::clock_t begin = clock();
					bool found = (tree.searchWord(input1) != NULL);
					std::clock_t end = clock();

					std::string message = found? "true": "false";
					std::cout << message << std::endl;
					std::cout << std::fixed << "BST: " << double(end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
				}
				break;
			case 2: {
					std::string input1;
					std::cin >> input1;

					std::clock_t begin = clock();
					tree.insertWord(input1);
					std::clock_t end = clock();

					std::cout << std::fixed << "BST: " << double(end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
				}
				break;
			case 3: {
					std::string input1;
					std::cin >> input1;

					std::clock_t begin = clock();
					tree.deleteWord(input1);
					std::clock_t end = clock();

					std::cout << std::fixed << "BST: " << double(end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
				}
				break;
			case 4: {
					std::cout << "output.txt" << std::endl;

					std::clock_t begin = clock();
					tree.sortWords("output.txt");
					std::clock_t end = clock();
					
					std::cout << std::fixed << "BST: " << double(end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
				}
				break;
			case 5: {
					std::string input1, input2;
					std::cin >> input1 >> input2;

					std::clock_t begin = clock();
					tree.searchRange(input1, input2);
					std::clock_t end = clock();
					
					std::cout << std::fixed << "BST: " << double(end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
				}
				break;
		};

	}

	return 0;
};

std::string cleanWord(std::string str) {
	std::string result = "";
	for (int i = 0; i < str.size(); i++) {
		if (isalpha(str[i]))
			result += str[i];
	}
	return result;
}

bool listContains(std::vector<std::string> list, std::string str) {
	bool found = false;
	for (int i = 0; i < list.size() && !found; i++) {
		if (list[i] == str)
			found = true;
	}
	return found;
}

std::string getFileContent(std::string filename) {
	std::ifstream reader(filename);
	std::string result, line;
	while (getline(reader, line))
		result += line + " ";
	reader.close();
	return result;
}

void fillStopwords(std::vector<std::string>& list, std::string filename) {
	std::ifstream reader(filename);
	std::string line;
	while (getline(reader, line))
		list.push_back(line);
	reader.close();
}

void getFiles(std::string folder, std::vector<std::string>& files) {
	DIR *dp;
	struct dirent *dirp;
	dp = opendir(folder.c_str());

	while ((dirp = readdir(dp)) != NULL) {
		std::string name = dirp->d_name;
		if (name[0] != '.')
			files.push_back(folder + name);
	}
	closedir(dp);
}