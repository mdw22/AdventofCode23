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

int charToInt(char c) {
    switch (c)
    {
    case '0':
        return 0;
        break;
    case '1':
        return 1;
        break;
    case '2':
        return 2;
        break;
    case '3':
        return 3;
        break;
    case '4':
        return 4;
        break;
    case '5':
        return 5;
        break;
    case '6':
        return 6;
        break;
    case '7':
        return 7;
        break;
    case '8':
        return 8;
        break;
    case '9':
        return 9;
        break;
    default:
        return -1;
        break;
    }
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Incorrect format. Please use ./day1 <inputfile>" << std::endl;
        return 0;
    }
    // Vector of input, each index is a line
    std::vector<std::string> inputVector = fileToVector(argv[1]);
    int result = 0;
    for(size_t i = 0; i < inputVector.size(); ++i) {
        int first_num = 0;
        int first_index = 0;
        int last_num = 0;
        std::string line = inputVector[i];
        for(size_t j = 0; j < line.length(); ++j) {
            char c = line[j];
            // Attempt to convert char
            first_num = charToInt(c);
            if(first_num == -1) continue;
            first_index = j;
            break;
        }
        for(size_t j = line.length() - 1; j >= 0; --j) {
            if(j == first_index) {
                last_num = first_num;
                break;
            }
            char c = line[j];
            last_num = charToInt(c);
            if(last_num == -1) continue;
            break;
        }
        result += (first_num * 10) + last_num;
        std::cout << "Result of line " << i << " : " << (first_num * 10) + last_num << std::endl;
    }
    std::cout << "Total result : " << result << std::endl;
}