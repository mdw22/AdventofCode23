/*
Code by Michael White, 2024
*/

#include <iostream>
#include <fstream>
#include <vector> 

std::vector<std::string> fileToVector(const std::string &fileName) {
    std::fstream source;
    std::vector<std::string> fileVector;
    std::string line;
    source.open(fileName);
    while(std::getline(source, line)) {
        fileVector.push_back(line);
    }
    source.close();
    return fileVector;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Incorrect format entered. Please use ./day6 <inputfile.txt>" << std::endl;
        return 0;
    }
    std::vector<std::string> fileLines = fileToVector(argv[1]);

    for(int i = fileLines[0].find(':') + 1; i < fileLines[0].length() - 1; ++i) {

    }
}