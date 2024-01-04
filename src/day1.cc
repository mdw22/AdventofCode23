/* 
Code by Michael White, 2024
*/

#include <iostream>
#include <fstream>

std::vector<std::string> fileToVector(const std::string& filename) {
    std::ifstream source;
    source.open(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(source, line))
    {
        lines.push_back(line);
    }
    source.close();
    return lines;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Incorrect format. Please use ./day1 <inputfile>" << std::endl;
        return 0;
    }
    // Vector of input, each index is a line
    std::vector<std::string> inputVector = fileToVector(argv[1]);
}