/*
Code by Michael White, 2024
*/

#include <iostream>
#include <fstream>
#include <vector> 

std::vector<int> pushValueToList(int index, std::vector<std::string> &fileLines) {
    std::vector<int> returnList;
    for(int i = fileLines[index].find(':') + 1; i < fileLines[index].length() - 1; ++i) {
        char c = fileLines[index][i];
        // Skip white space
        while(c == ' ' && i < fileLines[index].length() - 1) {
            ++i;
            c = fileLines[index][i];
        }
        // Build num
        int num = 0;
        while(c >= '0' && c <= '9') {
            num = (10 * num) + (c - '0');
            if(i + 1 > fileLines[index].length() - 1) break;
            ++i;
            c = fileLines[index][i];
        }
        // Push num to list
        returnList.push_back(num);
    }
    return returnList;
}

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
    int RESULT = 1; // Final result for Part 1

    // Time read in 
    std::vector<int> timeList = pushValueToList(0, fileLines);
    // Distance read in
    std::vector<int> distanceList = pushValueToList(1, fileLines);
    for(int i = 0; i < timeList.size(); ++i) {
        int current_time = timeList[i];
        int current_distance = distanceList[i];
        int passing_values = 0;
        for(int j = 1; j < current_time; ++j) {
            if(j * current_time - (j * j) > current_distance) passing_values++;
        }
        RESULT *= passing_values;
    }
    std::cout << RESULT << std::endl;
}