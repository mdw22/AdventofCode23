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
    
    // Hardcoded variables
    static int RED_CUBES = 12;
    static int GREEN_CUBES = 13;
    static int BLUE_CUBES = 14;

    // Return variables
    int RESULT = 0;
    int POWER_RESULT = 0;

    std::vector<std::string> file = fileToVector(argv[1]);
    for(size_t i = 0; i < file.size(); ++i) {
        // Vector for cube list
        std::vector<Cube> cubeList;
        std::vector<Cube> minCubeList;

        // Bool to store if cube list passes 
        bool pass = true;

        // Min int for green, blue, red cubes
        int min_green = 0;
        int min_blue = 0; 
        int min_red = 0;

        // First, find instance of : 
        int cur_index = file[i].find(':') + 2;
        for(;cur_index < file[i].length() - 1; cur_index+=2) {
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
                    if(!pass) {
                        // pass has been set to false at least once
                        break;
                    }
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
                }
                // Add cubelist to min list
                for(size_t j = 0; j < cubeList.size(); ++j) {
                    minCubeList.push_back(Cube{.color = cubeList[j].color, .size = cubeList[j].size});
                }
                cubeList.clear();
            }
        }
        // Check for min cubes
        for(size_t j = 0; j < minCubeList.size(); ++j) {
            int color = minCubeList[j].color;
            int size = minCubeList[j].size;
            switch (color)
            {
            case 0:
                if(min_green == 0) min_green = size;
                else if(size > min_green) min_green = size;
                break;
            case 1:
                if(min_blue == 0) min_blue = size;
                else if(size > min_blue) min_blue = size;
                break;
            case 2:
                if(min_red == 0) min_red = size;
                else if(size > min_red) min_red = size;
                break;
            default:
                break;
            }
        }
        if(pass) {
            RESULT += (i + 1);
        }
        POWER_RESULT += (min_green * min_blue * min_red);
    }
    std::cout << RESULT << std::endl;
    std::cout << POWER_RESULT << std::endl;
}