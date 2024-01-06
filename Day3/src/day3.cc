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

struct Part {
    int x;
    std::vector<int> y_list;
    int number;
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

bool gearCheck(int gear_x, int gear_y, int x, int y) {
    if(x == gear_x - 1 || x == gear_x + 1) {
        if(y == gear_y - 1 || y == gear_y || y == gear_y + 1) {
            return true;
        }
    }
    else if(x == gear_x) {
        if(y == gear_y - 1 || y == gear_y + 1) {
            return true;
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
    std::vector<Coord> gearList;
    std::vector<Part> partList;
    int RESULT = 0;
    int GEAR_RESULT = 0;

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
            if(c == '*') {
                gearList.push_back(Coord{.x = i, .y = j});
            }
        }
    }

    // Find numbers in input file. Check if each num is valid.
    // Part 1 solution
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
            if(num != 0) {
                // Add part to part list
                partList.push_back(Part{.x = i, .y_list = char_num_indices, .number = num});
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

    // Part 2 solution
    // Use gear locations to check each gear how many part numbers it intersects
    for(int i = 0; i < gearList.size(); ++i) {
        std::vector<int> intersected_List; 
        // Get coords of current gear
        int gear_x = gearList[i].x;
        int gear_y = gearList[i].y;
        for(int j = 0; j < partList.size(); ++j) {
            int part_x = partList[j].x;
            for(int k = 0; k < partList[j].y_list.size(); ++k) {
                int part_y = partList[j].y_list[k];
                bool gear_check = gearCheck(gear_x, gear_y, part_x, part_y);
                if(gear_check) {
                    intersected_List.push_back(partList[j].number);
                    break;
                }
            }
        }
        if(intersected_List.size() == 2) {
            GEAR_RESULT += intersected_List[0] * intersected_List[1];
        }
    }
    std::cout << RESULT << std::endl;
    std::cout << GEAR_RESULT << std::endl;
}