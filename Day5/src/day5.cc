/*
Code by Michael White, 2024
*/

#include <iostream>
#include <fstream>
#include <vector>

struct Seed {
    int64_t seed_id; 
};

std::vector<std::string> fileToVector(const std::string &fileName) {
    std::vector<std::string> fileLines;
    std::string line;
    std::ifstream source;
    source.open(fileName);
    while(std::getline(source, line)) {
        fileLines.push_back(line);
    }
    source.close();
    return fileLines;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Incorrect format. Please use ./day5 <inputfile.txt>" << std::endl;
        return 0;
    }
    std::vector<std::string> fileLines = fileToVector(argv[1]);

    std::vector<Seed> seedList;
    // Read and store seed ID's
    // Iterate through the first line after : to find numbers
    for(int i = fileLines[0].find(':') + 2; i < fileLines[0].length() - 1; ++i) {
        char c = fileLines[0][i];
        int64_t num = 0;
        while(c == ' ' && i < fileLines[0].length() - 1) {
            i++;
            c = fileLines[0][i];
        }
        while(c >= '0' && c <= '9') {
            num = (10 * num) + (c - '0');
            if(i + 1 > fileLines[0].length() - 1) break;
            i++;
            c = fileLines[0][i];
        }
        seedList.push_back(Seed{.seed_id = num});
    }

    for(int i = 0; i < seedList.size(); ++i) {
        std::cout << seedList[i].seed_id << std::endl;
    }
}