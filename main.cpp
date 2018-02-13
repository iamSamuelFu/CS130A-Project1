#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include "BST.h"

std::string getFileContent(std::string filename);
void fillStopwords(std::string array[], std::string filename);
void getFiles(std::string folder, std::vector<std::string> &files);

int main() {

	std::string stopwords[127];
	fillStopwords(stopwords, "stopwords.txt");

	//Get all filenames
	std::vector<std::string> folders;
	std::vector<std::string> files;
	getFiles("hotels/", folders);
	for (int i = 0; i < folders.size(); i++)
		getFiles(folders[i] + "/", files);
	std::cout << files[0] << std::endl;

	//Read file
	std::string input = getFileContent(files[0]);
	std::cout << input << std::endl;

	return 0;
};

std::string getFileContent(std::string filename) {
	std::ifstream reader(filename);
	std::string result, line;
	while (getline(reader, line))
		result += line + " ";
	reader.close();
	return result;
}

void fillStopwords(std::string array[], std::string filename) {
	std::ifstream reader(filename);
	std::string line;
	int i = 0;
	while (getline(reader, line))
		array[i++] = line;
	reader.close();
}

void getFiles(std::string folder, std::vector<std::string> &files) {
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