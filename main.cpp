#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <regex>
#include <algorithm>
#include <ctime>
#include <chrono>
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

	//Insert words to BST
	BST tree;
	for (int i = 0; i < words.size(); i++)
		tree.insertWord(words[i]);

	//std::cout << "Words insertion into Hashtable and BST completed." << std::endl;

	//Main
	while (true) {

		int option;
		std::cin >> option;

		switch(option) {

			case 1: {
					std::string input1;
					std::cin >> input1;
					bool found = false;

					std::chrono::high_resolution_clock::time_point begin_bst = std::chrono::high_resolution_clock::now();
					found = (tree.searchWord(input1) != NULL);
					std::chrono::high_resolution_clock::time_point end_bst = std::chrono::high_resolution_clock::now();


					std::chrono::high_resolution_clock::time_point begin_hash = std::chrono::high_resolution_clock::now();
					found = (table.searchWord(input1) != -1);
					std::chrono::high_resolution_clock::time_point end_hash = std::chrono::high_resolution_clock::now();


					std::string message = found? "true": "false";
					std::cout << message << std::endl;

					std::chrono::duration<double> time_span_bst = end_bst - begin_bst;
					std::chrono::duration<double> time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;
				}
				break;
			case 2: {
					std::string input1;
					std::cin >> input1;

					std::chrono::high_resolution_clock::time_point begin_bst = std::chrono::high_resolution_clock::now();
					tree.insertWord(input1);
					std::chrono::high_resolution_clock::time_point end_bst = std::chrono::high_resolution_clock::now();

					std::chrono::high_resolution_clock::time_point begin_hash = std::chrono::high_resolution_clock::now();
					table.insertWord(input1);
					std::chrono::high_resolution_clock::time_point end_hash = std::chrono::high_resolution_clock::now();

					std::chrono::duration<double> time_span_bst = end_bst - begin_bst;
					std::chrono::duration<double> time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;
				}
				break;
			case 3: {
					std::string input1;
					std::cin >> input1;

					std::chrono::high_resolution_clock::time_point begin_bst = std::chrono::high_resolution_clock::now();
					tree.deleteWord(input1);
					std::chrono::high_resolution_clock::time_point end_bst = std::chrono::high_resolution_clock::now();

					std::chrono::high_resolution_clock::time_point begin_hash = std::chrono::high_resolution_clock::now();
					table.deleteWord(input1);
					std::chrono::high_resolution_clock::time_point end_hash = std::chrono::high_resolution_clock::now();

					std::chrono::duration<double> time_span_bst = end_bst - begin_bst;
					std::chrono::duration<double> time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;
				}
				break;
			case 4: {
					std::string filename = "output.txt";
					std::cout << filename<< std::endl;

					std::chrono::high_resolution_clock::time_point begin_bst = std::chrono::high_resolution_clock::now();
					tree.sortWords(filename);
					std::chrono::high_resolution_clock::time_point end_bst = std::chrono::high_resolution_clock::now();
		
					std::ofstream writer;
					writer.open(filename, std::ios_base::app);
					writer << std::endl;
					writer.close();

					std::chrono::high_resolution_clock::time_point begin_hash = std::chrono::high_resolution_clock::now();
					table.sortWords(filename);
					std::chrono::high_resolution_clock::time_point end_hash = std::chrono::high_resolution_clock::now();
					
					std::chrono::duration<double> time_span_bst = end_bst - begin_bst;
					std::chrono::duration<double> time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;
				}
				break;
			case 5: {
					std::string input1, input2;
					std::cin >> input1 >> input2;

					std::chrono::high_resolution_clock::time_point begin_bst = std::chrono::high_resolution_clock::now();
					tree.searchRange(input1, input2);
					std::chrono::high_resolution_clock::time_point end_bst = std::chrono::high_resolution_clock::now();

					std::chrono::high_resolution_clock::time_point begin_hash = std::chrono::high_resolution_clock::now();
					table.searchRange(input1, input2);
					std::chrono::high_resolution_clock::time_point end_hash = std::chrono::high_resolution_clock::now();
					
					std::chrono::duration<double> time_span_bst = end_bst - begin_bst;
					std::chrono::duration<double> time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;
				}
				break;
			case 6: {
					std::cout << "tabulation data collection begin" << std::endl;

					std::cout << "<-----100 INSERTIONS BEGIN----->\n";
					std::chrono::high_resolution_clock::time_point begin_bst = std::chrono::high_resolution_clock::now();
					for (int i = 0; i < 100; i++) 
						tree.insertWord(words[i] + "s");
					std::chrono::high_resolution_clock::time_point end_bst = std::chrono::high_resolution_clock::now();

					std::chrono::high_resolution_clock::time_point begin_hash = std::chrono::high_resolution_clock::now();
					for (int i = 0; i < 100; i++)
						table.insertWord(words[i] + "s");
					std::chrono::high_resolution_clock::time_point end_hash = std::chrono::high_resolution_clock::now();

					std::chrono::duration<double> time_span_bst = end_bst - begin_bst;
					std::chrono::duration<double> time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;	
					std::cout << "<-----100 INSERTIONS END----->\n\n";


					bool found;

					std::cout << "<-----100 SEARCHES BEGIN----->\n";
					begin_bst = std::chrono::high_resolution_clock::now();
					for (int i = 0; i < 100; i++)
						found = (tree.searchWord(words[i] + "s") != NULL);
					end_bst = std::chrono::high_resolution_clock::now();


					begin_hash = std::chrono::high_resolution_clock::now();
					for (int i = 0; i < 100; i++)
						found = (table.searchWord(words[i] + "s") != -1);
					end_hash = std::chrono::high_resolution_clock::now();

					time_span_bst = end_bst - begin_bst;
					time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;
					std::cout << "<-----100 SEARCHES END----->\n\n";	




					std::cout << "<-----100 DELETES BEGIN----->\n";
					begin_bst = std::chrono::high_resolution_clock::now();
					for (int i = 0; i < 100; i++)
						tree.deleteWord(words[i]);
					end_bst = std::chrono::high_resolution_clock::now();

					begin_hash = std::chrono::high_resolution_clock::now();
					for (int i = 0; i < 100; i++)
						table.deleteWord(words[i]);
					end_hash = std::chrono::high_resolution_clock::now();

					time_span_bst = end_bst - begin_bst;
					time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;
					std::cout << "<-----100 DELETES END----->\n\n";




					std::cout << "<-----10 RANGE SEARCH BEGIN----->\n";

					begin_bst = std::chrono::high_resolution_clock::now();
					tree.searchRange("aber", "abotts");
					end_bst = std::chrono::high_resolution_clock::now();

					begin_hash = std::chrono::high_resolution_clock::now();
					table.searchRange("aber", "abotts");
					end_hash = std::chrono::high_resolution_clock::now();
					
					time_span_bst = end_bst - begin_bst;
					time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;
					std::cout << "<-----10 RANGE SEARCH END----->\n\n";	



					std::cout << "<-----100 RANGE SEARCH BEGIN----->\n";

					begin_bst = std::chrono::high_resolution_clock::now();
					tree.searchRange("aber", "accomodatingoverall");
					end_bst = std::chrono::high_resolution_clock::now();

					begin_hash = std::chrono::high_resolution_clock::now();
					table.searchRange("aber", "accomodatingoverall");
					end_hash = std::chrono::high_resolution_clock::now();

					time_span_bst = end_bst - begin_bst;
					time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;
					std::cout << "<-----100 RANGE SEARCH END----->\n\n";				




					std::cout << "<-----1000 RANGE SEARCH BEGIN----->\n";

					begin_bst = std::chrono::high_resolution_clock::now();
					tree.searchRange("aber", "apr");
					end_bst = std::chrono::high_resolution_clock::now();

					begin_hash = std::chrono::high_resolution_clock::now();
					table.searchRange("aber", "apr");
					end_hash = std::chrono::high_resolution_clock::now();
					
					time_span_bst = end_bst - begin_bst;
					time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;
					std::cout << "<-----1000 RANGE SEARCH END----->\n\n";




					std::cout << "<-----SORT BEGIN----->\n";
					std::string filename = "output.txt";
					std::cout << filename << std::endl;

					begin_bst = std::chrono::high_resolution_clock::now();
					tree.sortWords(filename);
					end_bst = std::chrono::high_resolution_clock::now();
		
					std::ofstream writer;
					writer.open(filename, std::ios_base::app);
					writer << std::endl;
					writer.close();

					begin_hash = std::chrono::high_resolution_clock::now();
					table.sortWords(filename);
					end_hash = std::chrono::high_resolution_clock::now();
					
					time_span_bst = end_bst - begin_bst;
					time_span_hash = end_hash - begin_hash;
					std::cout << std::fixed << "BST: " << time_span_bst.count() << "s" << std::endl;
					std::cout << std::fixed << "Hash: " << time_span_hash.count() << "s" << std::endl;
					std::cout << "<-----SORT END----->\n\n";
		 	}
			break;
		};

		std::cout << std::endl;
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
