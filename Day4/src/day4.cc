/*
 Code by Michael White, 2024
*/

#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> fileToVector(const std::string &fileName) {
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
    std::vector<std::string> lines = fileToVector(argv[1]);
    // Find first instance of : on line and add 2 to index, loop until pos '|' - 1
    // Construct number until ' '
    // Add number to list, move forward
    int RESULT = 0;
    for(int i = 0; i < lines.size(); ++i) {
        std::string line = lines[i];
        std::vector<int> winning_numbers;
        int card_result = 0;
        for(int j = line.find(':') + 2; j < line.find('|') - 1; ++j) {
            char c = line[j];
            int num = 0;
            while(c == ' ' && j < line.length() - 1) {
                ++j;
                c = line[j];
            }
            while(c >= '0' && c <= '9') {
                num = (10 * num) + (c - '0');
                if(j + 1 > line.length() - 1) {
                    break;
                }
                ++j;
                c = line[j];
            }
            winning_numbers.push_back(num);
        }
        // Build every number from personal numbers, compare each to winning list
        // If match is found, bitshift 1 left to double
        for(int j = line.find('|') + 2; j < line.length() - 1; ++j) {
            char c = line[j];
            int num = 0;
            while(c == ' ' && j < line.length() - 1) {
                ++j;
                c = line[j];
            }
            while(c >= '0' && c <= '9') {
                num = (10 * num) + (c - '0');
                if(j + 1 > line.length() - 1) {
                    break;
                }
                ++j;
                c = line[j];
            }
            for(int k = 0; k < winning_numbers.size(); ++k) {
                if(num == winning_numbers[k]) {
                    card_result = (card_result == 0) ? 1 : card_result << 1;
                    break;
                }
            }
        }
        RESULT += card_result;
    }
    std::cout << RESULT << std::endl;
}