/*
Code by Michael White, 2024
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map> 

struct Almanac {
    std::vector<std::tuple<int64_t, int64_t, int64_t>> ruleList;

    int64_t transform(int64_t x) {
        int64_t destination_start = 0;
        int64_t source_start = 0;
        int64_t range = 0;
        for(int i = 0; i < ruleList.size(); ++i) {
            std::tuple<int64_t, int64_t, int64_t> currentTuple = ruleList[i];
            destination_start = std::get<0>(currentTuple);
            source_start = std::get<1>(currentTuple);
            range = std::get<2>(currentTuple);
            if(x <= source_start + range && x >= source_start) {
                return destination_start + (x - source_start);
            }
        }
        return x;
    }

    int64_t reverseTransform(int64_t x) {
        int64_t destination_start = 0;
        int64_t source_start = 0;
        int64_t range = 0;
        for(int i = 0; i < ruleList.size(); ++i) {
            std::tuple<int64_t, int64_t, int64_t> currentTuple = ruleList[i];
            destination_start = std::get<1>(currentTuple);
            source_start = std::get<0>(currentTuple);
            range = std::get<2>(currentTuple);
            if(x <= source_start + range && x >= source_start) {
                return destination_start + (x - source_start);
            }
        }
        return x;
    }

    void clear() {
        ruleList.clear();
    }
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

    std::vector<int64_t> seedList;
    // Vector for Part 2 answer
    std::vector<std::tuple<int64_t, int64_t>> updatedSeedList;
    //Map of all map relations
    std::vector<Almanac> mapList;
    // TODO
    // Read and store seed ID's
    // Iterate through the first line after : to find numbers
    bool second_num_flag = false;
    int64_t first_num = 0;
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
        seedList.push_back(num);
        if(second_num_flag) {
            updatedSeedList.push_back({first_num, num});
            second_num_flag = false;
        }
        else {
            first_num = num;
            second_num_flag = true;
        }
    }
    // Build maps of every relation that is in the file
    // Then, filter every seed in seedList through it to get answer
    Almanac currentAlmanac;  
    for(int i = 1; i < fileLines.size(); ++i) {
        std::string line = fileLines[i];
        if(line.length() == 0 && i != 1) { // Blank line and not first line means it is end of a map
            mapList.push_back(currentAlmanac);
            currentAlmanac.clear();
            continue;
        }
        else if(line[0] < '0' || line[0] > '9') continue;   // Word line or first blank line
        std::vector<int64_t> mapRanges;
        for(int j = 0; j < line.length(); ++j) {
            char c = line[j];
            int64_t current_num = 0;
            while(c >= '0' && c <= '9') {
                current_num = (10 * current_num) + (c - '0');
                if(j + 1 > line.length()) break;
                ++j;
                c = line[j];
            }
            mapRanges.push_back(current_num);
        }
        // MapRanges has 3 indices, 0 is for destination_range_start, 1 is for source_range_start, 2 is for range_length
        int64_t destination_range_start = mapRanges[0];
        int64_t source_range_start = mapRanges[1];
        int64_t range_length = mapRanges[2];
        currentAlmanac.ruleList.push_back({destination_range_start, source_range_start, range_length});
        if(i + 1 >= fileLines.size()) mapList.push_back(currentAlmanac);    // Last line
    }

    // Part 1 answer
    int64_t lowest_num = -1;
    for(int64_t current_seed : seedList) {
        int64_t current_number = current_seed;
        for(Almanac current_almanac : mapList) {
            current_number = current_almanac.transform(current_number);
        }
        if(lowest_num == -1) lowest_num = current_number;
        else if(current_number < lowest_num) lowest_num = current_number;
    }
    std::cout << lowest_num << std::endl;

    // Part 2 answer
    int64_t next_lowest_num = -1;
    int64_t index = 0; 
    bool break_flag = false;
    while(true) {
        int64_t current_seed_value = index;
        for(int i = mapList.size() - 1; i >= 0; --i) {
            Almanac a = mapList[i];
            current_seed_value = a.reverseTransform(current_seed_value);
        }
        // Found seed value for location index, check if present
        for(int i = 0; i < updatedSeedList.size(); ++i) {
            std::tuple<int64_t, int64_t> currentPair = updatedSeedList[i];
            int64_t start = std::get<0>(currentPair);
            int64_t range = std::get<1>(currentPair);
            if(current_seed_value >= start && current_seed_value <= start + range) {
                next_lowest_num = index;
                break_flag = true;
                break;
            }
        }
        // If found, break
        if(break_flag) break;
        ++index;
    }

    int64_t temp = next_lowest_num;
    for(int i = mapList.size() - 1; i >= 0; --i) {
        Almanac a = mapList[i];
        temp = a.reverseTransform(temp);
    }
    std::cout << temp << std::endl;
    std::cout << next_lowest_num << std::endl;
}