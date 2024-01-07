/*
 Code by Michael White, 2024
*/

#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> fileToVector(std::string &fileName) {
    std::ifstream source;
    source.open(fileName);
    std::vector<std::string> lines;
    std::string line; 
    while(std::getline(source, line)) {
        lines.push_back(line);
    }
    source.close();
    return lines;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Incorrect format used. Please run with ./day4 <inputfile.txt>" << std::endl;
        return 0;
    }
}