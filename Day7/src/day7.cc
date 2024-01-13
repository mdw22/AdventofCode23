/*
Code by Michael White, 2024
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

std::vector<std::string> fileToVector(const std::string &fileName) {
    std::vector<std::string> returnList;
    std::string line;
    std::fstream source;
    source.open(fileName);
    while(std::getline(source, line)) {
        returnList.push_back(line);
    }
    source.close();
    return returnList;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Incorrect format used. Please use ./day7 <inputfile.txt>" << std::endl;
        return 0;
    }
    std::vector<std::string> fileLines = fileToVector(argv[1]);

    // Map Cards to Values, with char as key
    char cardList[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    std::map<char, int> charValueMap; 
    for(int i = 0; i < 14; ++i) {
        charValueMap[cardList[i]] = i + 1;
    }
    
    for(std::string line : fileLines) {
        // Read Card Value
        for(int i = 0; i < line.find(' '); ++i) {
            char c = line[i];
            
        }
        // Read Bet Value
        for(int i = line.find(' ') + 1; i < line.length(); ++i) {
            char c = line[i];
            
        }
    }
}