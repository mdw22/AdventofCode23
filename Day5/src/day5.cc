/*
Code by Michael White, 2024
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map> 

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
    //Map of all maps
    std::vector<std::vector<int64_t>> mapList;
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
    // Build maps of every relation that is in the file
    // Then, filter every seed in seedList through it to get answer
   std::unordered_map<int64_t, int64_t> current_map;
    for(int i = 1; i < fileLines.size(); ++i) {
        std::string line = fileLines[i];
        if(line.length() == 0 && i != 1) { // Blank line and not first line means it is end of a map
            // mapList.push_back(current_map);
            current_map.clear();
            continue;
        }
        else if(line[0] < '0' || line[0] > '9') continue;   // Word line
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
        // MapRanges has 3 indices
        // 0 is for destination_range_start
        // 1 is for source_range_start
        // 2 is for range_length
        int64_t destination_range_start = mapRanges[0];
        int64_t source_range_start = mapRanges[1];
        int64_t range_length = mapRanges[2];
        // f(t) = c + (d-c/b-a)*(t-a)
        // Use linear slop formula to convert
        
    }  

}