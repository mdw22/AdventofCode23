/*
    Code by Michael White, 2024
*/

#include <iostream>
#include <fstream>
#include <vector> 

struct Cube {
    // Color represented by int, 0 = green, 1 = blue, 2 = red
    int color;
    int size;
};

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
        std::cout << "Incorrect format. Please use ./day2 <textfile>" << std::endl;
        return 0;
    }
    
    int RED_CUBES = 12;
    int GREEN_CUBES = 13;
    int BLUE_CUBES = 14;
    int RESULT = 0;
    std::vector<std::string> file = fileToVector(argv[1]);
    for(size_t i = 0; i < file.size(); ++i) {
        // Vector for cube list
        std::vector<Cube> cubeList;

        // Bool to store if cube list passes 
        bool pass = true;

        // First, find instance of : 
        int cur_index = file[i].find(':') + 2;
        for(;cur_index < file[i].length() - 1; ++cur_index) {
            // Read in number
            int num = file[i][cur_index] - '0';
            cur_index++;
            while(file[i][cur_index] != ' ') {
                num = (10 * num) + (file[i][cur_index] - '0');
                cur_index++;
            }
            cur_index++;
            std::string color = "";
            while(file[i][cur_index] != ',' && file[i][cur_index] != ';') {
                color += file[i][cur_index];
                if(cur_index >= file[i].length() - 1) {
                    break;
                }
                cur_index++;
            }
            // Create cube object and add to list
            if(color == "green") {
                cubeList.push_back(Cube{.color = 0, .size = num});
            }
            else if(color == "blue") {
                cubeList.push_back(Cube{.color = 1, .size = num});
            }
            else if(color == "red") {
                cubeList.push_back(Cube{.color = 2, .size = num});
            }
            if(file[i][cur_index] == ';' || cur_index >= file[i].length() - 1) {
                for(size_t j = 0; j < cubeList.size(); ++j) {
                    int color = cubeList[j].color;
                    int size = cubeList[j].size;
                    switch (color)
                    {
                    case 0:
                        pass = size <= GREEN_CUBES ? true : false;
                        break;
                    case 1:
                        pass = size <= BLUE_CUBES ? true : false;
                        break;
                    case 2:
                        pass = size <= RED_CUBES ? true : false;
                        break;
                    default:
                        break;
                    }
                    if(!pass) {
                        // pass has been set to false at least once
                        break;
                    }
                }
                cubeList.clear();
            }
            cur_index++;
            if(!pass) {
                break;
            }
        }
        if(pass) {
            RESULT += (i + 1);
        }
    }
    std::cout << RESULT << std::endl;
}