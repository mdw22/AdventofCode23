/* 
Code by Michael White, 2024
*/

#include <iostream>
#include <fstream>
#include <tuple>

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

// Method to return a tuple of a word translated to Int
// Usuage wordToInt(input, reverseString?)
// Outputs tuple of <int, index> 
std::tuple<int, int> wordToInt(std::string input, bool reverse) {
    if(!reverse) {
        for(int i = 0; i < input.length(); ++i) {
            if(i + 1 < input.length() && i + 2 < input.length()) {
                switch (input[i])
                {
                case 'o':
                    if(input[i+1] == 'n' && input[i+2] == 'e') {
                        return {1, i};
                    }
                    break;
                case 't':
                    if(input[i+1] == 'w' && input[i+2] == 'o') {
                        return {2, i};
                    }
                    else if(i + 3 < input.length() && i + 4 < input.length() && input[i+1] == 'h' &&
                    input[i+2] == 'r' && input[i+3] == 'e' && input[i+4] == 'e') {
                        return {3, i};
                    }
                    break;
                case 'f':
                    if(i + 3 < input.length() && input[i+1] == 'o' && input[i+2] == 'u' && input[i+3] == 'r') {
                        return {4, i};
                    }
                    else if(i + 3 < input.length() && input[i+1] == 'i' && input[i+2] == 'v' && input[i+3] == 'e') {
                        return {5, i};
                    }
                    break;
                case 's':
                    if(input[i+1] == 'i' && input[i+2] == 'x') {
                        return {6, i};
                    }
                    else if(i + 3 < input.length() && i + 4 < input.length() && input[i+1] == 'e' && 
                    input[i+2] == 'v' && input[i+3] == 'e' && input[i+4] == 'n') {
                        return {7, i};
                    }
                    break;
                case 'e':
                    if(i + 3 < input.length() && i + 4 < input.length() && input[i+1] == 'i' && input[i+2] == 'g' &&
                    input[i+3] == 'h' && input[i+4] == 't') {
                        return {8, i};
                    }
                    break;
                case 'n':
                    if(i + 3 < input.length() && input[i+1] == 'i' && input[i+2] == 'n' && input[i+3] == 'e') {
                        return {9, i};
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    else {
        for(int i = input.length() - 1; i >= 0; --i) {
            if(i - 1 >= 0 && i - 2 >= 0) {
                switch (input[i])
                {
                case 'e':
                    if(input[i-1] == 'n' && input[i-2] == 'o') {
                        return {1, i-2};
                    }
                    else if (i - 3 >= 0 && i - 4 >= 0 && input[i-1] == 'e' && input[i-2] == 'r' && input[i-3] == 'h' && input[i-4] == 't') {
                        return {3, i-4};
                    }
                    else if(i - 3 >= 0 && input[i-1] == 'v' && input[i-2] == 'i' && input[i-3] == 'f') {
                        return {5, i-3};
                    }
                    else if (i - 3 >= 0 && input[i-1] == 'n' && input[i-2] == 'i' && input[i-3] == 'n') {
                        return {9, i-3};
                    }
                    break;
                case 'o':
                    if(input[i-1] == 'w' && input[i-2] == 't') {
                        return {2, i-2};
                    }
                    break;
                case 'r':
                    if(i - 3 >= 0 && input[i-1] == 'u' && input[i-2] == 'o' && input[i-3] == 'f') {
                        return {4, i-3};
                    }
                    break;
                case 'x':
                    if(input[i-1] == 'i' && input[i-2] == 's') {
                        return {6, i-2};
                    }
                    break;
                case 'n':
                    if(i - 3 >= 0 && i - 4 >= 0 && input[i-1] == 'e' && input[i-2] == 'v' && input[i-3] == 'e' && input[i-4] == 's') {
                        return {7, i-4};
                    }
                    break;
                case 't':
                    if(i - 3 >= 0 && i - 4 >= 0 && input[i-1] == 'h' && input[i-2] == 'g' && input[i-3] == 'i' && input[i-4] == 'e') {
                        return {8, i-4};
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    return {-1, -1};
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
        auto [word , word_index] = wordToInt(line, false);
        // Iterate forwards
        for(size_t j = 0; j < line.length(); ++j) {
            char c = line[j];
            // Attempt to convert char
            int current_num = charToInt(c);
            if(current_num == -1 && word == -1) continue;
            if(current_num != -1 && word != -1) {
                if(j < word_index) {
                    first_index = j;
                    first_num = current_num;
                    break;
                }
                else {
                    first_index = word_index;
                    first_num = word;
                    break;
                }
            }
            else if(current_num == -1 && word != -1) {
                if(j < word_index) continue;
                else {
                    first_index = word_index;
                    first_num = word;
                    break;
                }
            }
            else {
                first_index = j;
                first_num = current_num;
                break;
            }
        }
        auto [lword, lword_index] = wordToInt(line, true);
        // Iterate backwards
        for(size_t j = line.length() - 1; j >= 0; --j) {
            if(j == first_index) {
                last_num = first_num;
                break;
            }
            char c = line[j];
            int current_num = charToInt(c);
            if(current_num == -1 && lword == -1) continue;
            else if(current_num != -1 && lword != -1) {
                if(j > lword_index) {
                    last_num = current_num;
                    break;
                }
                else {
                    last_num = lword;
                    break;
                }
            }
            else if(current_num == -1 && lword != -1) {
                if(j > lword_index) continue;
                else {
                    last_num = lword;
                    break;
                }
            }
            else {
                last_num = current_num;
                break;
            }
        }
        result += (first_num * 10) + last_num;
        std::cout << "Line " << i << " Result : " << (first_num * 10) + last_num << std::endl;
    }
    std::cout << "Total result : " << result << std::endl;
}