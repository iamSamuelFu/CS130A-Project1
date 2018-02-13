#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <regex>
#include <algorithm>
#include "BST.h"
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

	//Insert words to BST
	BST tree;
	for (int i = 0; i < words.size(); i++)
		tree.insertWord(words[i]);
	
	//Print sorted BST words to output.txt
	tree.sortWords("output.txt");

	//Search word in BST
	tree.searchWord("accesslaundrytelevisioncentrally");

	//Delete word in BST
	tree.deleteWord("abbotts");

	//Search word range in BST
	tree.searchRange("aa", "abutting");

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