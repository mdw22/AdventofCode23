/*
 Code by Michael White, 2024
*/

#include <iostream>
#include <vector> 
#include <fstream>

/* 
Spaces around symbol that are valid
If number touches a space, it is valid
Looks like
    |   |   |
x   |   @   |
    |   |   |
        y
So if position of symbol is (x, y)
Then valid positions are: 
(x - 1, y - 1), (x - 1, y), (x - 1, y + 1)
(x, y - 1), (x, y+1)
(x + 1, y - 1), (x + 1, y), (x + 1, y + 1)
*/

struct Coord {
    int x;
    int y;
};

std::vector<std::string> fileToVector(const std::string &filename) {
    std::ifstream source;
    source.open(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(source, line)) {
        lines.push_back(line);
    }
    source.close();
    return lines;
}

bool posCheck(int x, int y, std::vector<Coord> &coordList) {
    for(int i = 0; i < coordList.size(); ++i) {
        int symbol_x = coordList[i].x;
        int symbol_y = coordList[i].y;
        if(x == symbol_x - 1 || x == symbol_x + 1) {
            if(y == symbol_y - 1 || y == symbol_y || y == symbol_y + 1) {
                return true;
            }
        }
        else if(x == symbol_x) {
            if(y == symbol_y - 1 || y == symbol_y + 1) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Incorrect format. Please use ./day3 <inputfile.txt>" << std::endl;
        return 0;
    }
    char INPUT_SYMBOLS[] = {'@', '#', '$', '%', '&', '*', '-', '+', '=', '/'};
    std::vector<std::string> fileLines = fileToVector(argv[1]);
    std::vector<Coord> coordList; 
    int RESULT = 0;

    // Find positions of symbols in input file
    for(int i = 0; i < fileLines.size(); ++i) {
        std::string line = fileLines[i];
        for(int j = 0; j < line.length() - 1; ++j) {
            char c = line[j];
            for(size_t k = 0; k < 10; ++k) {
                if(c == INPUT_SYMBOLS[k]) {
                    coordList.push_back(Coord{.x = i, .y = j});
                }
            }
        }
    }

    // Find numbers in input file. Check if each num is valid.
    for(int i = 0; i < fileLines.size(); ++i) {
        std::string line = fileLines[i];
        bool pos_check = false;
        for(int j = 0; j < line.length() - 1; ++j) {
            int num = 0;
            char c = line[j];
            std::vector<int> char_num_indices; 
            // Construct num
            while(c >= '0' && c <= '9') {
                num = (10 * num) + (c - '0');
                char_num_indices.push_back(j);
                ++j;
                c = line[j];
            }
            // Check each indices if valid
            for(int k = 0; k < char_num_indices.size(); ++k) {
                if(pos_check) break;
                pos_check = posCheck(i, char_num_indices[k], coordList);
            }
            // If at least one indices pass, add number to result and reset pos_check
            if(pos_check) {
                RESULT += num;
                pos_check = false;
            }
        }
    }
    std::cout << RESULT << std::endl;
}