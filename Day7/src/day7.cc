/*
Code by Michael White, 2024
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

// Returns 0 for High Card, 1 for 1 pair, 2 for 2 pair, 3 for three of a kind, 4 for full house, 5 for four of a kind, and 6 for five of a kind (all equal)
int handType(std::vector<int> &handList) {
    std::vector<int> currentHand = handList;
    std::sort(currentHand.begin(), currentHand.end());
    std::vector<int>::iterator it = std::unique(currentHand.begin(), currentHand.end());
    currentHand.erase(it, currentHand.end());
    int high_card = 0;
    int low_card = 0;
    int high_matches = 0;
    int low_matches = 0;
    switch (currentHand.size())
    {
        case 1:
            return 6;
            break;

        case 2:
            // Four of a kind or full house
            high_card = currentHand[1];
            low_card = currentHand[0];
            for(int card : handList) {
                if(card == high_card) high_matches++;
                else if(card == low_card) low_matches++;
            }
            if(high_matches == 4 || low_matches == 4) return 5;
            else return 4;
            break;
        
        case 3:
            // Three of a kind or 2 pair
            high_card = currentHand[2];
            low_card = currentHand[0];
            for(int card : handList) {
                if(card == high_card) high_matches++;
                else if(card == low_card) low_matches++;
            }
            if(high_matches == 2 || low_matches == 2) return 2;
            else return 3;
            break;
        
        case 4:
            // One pair
            return 1;
            break;
        
        case 5:
            // High Card
            return 0;
            break;
        
        default:
            return -1;
            break;
    }
}

std::vector<std::string> fileToVector(const std::string &fileName) {
    std::vector<std::string> returnList;
    std::string line;
    std::fstream source;
    source.open(fileName);
    while(std::getline(source, line)) {
        returnList.push_back(line);
    }
    source.close();
    return returnList;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Incorrect format used. Please use ./day7 <inputfile.txt>" << std::endl;
        return 0;
    }
    int RETURN_SUM = 0;
    std::vector<std::string> fileLines = fileToVector(argv[1]);

    // Map Cards to Values, with char as key
    char cardList[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    std::map<char, int> charValueMap; 
    for(int i = 0; i < 14; ++i) {
        charValueMap[cardList[i]] = i + 1;
    }
    
    // Vectors to store list of hand values and bet value
    std::vector<std::vector<int>> handList;
    std::vector<int> betList;
    for(int i = 0; i < fileLines.size(); ++i) {
        std::string line = fileLines[i];
        // Read Hand Value
        std::vector<int> handValues;
        for(int j = 0; j < line.find(' '); ++j) {
            char c = line[j];
            handValues.push_back(charValueMap[c]);
        }
        // Read Bet Value
        int num = 0;
        for(int j = line.find(' ') + 1; j < line.length(); ++j) {
            char c = line[j];
            num = (10 * num) + (c - '0');
        }
        handList.push_back(handValues);
        betList.push_back(num);
    }

    // Cycle through handList/betList. If equal, branch off
    // 7 times for each handtype
    int rank = 1;
    for(int i = 0; i < 7; ++i) {
        std::vector<int> equalIndex;
        for(int j = 0; j < handList.size(); ++j) {
            if(i == handType(handList[j])) equalIndex.push_back(j);
        }
        // If only one hand of this type exists, we can just add it to rank and continue
        if(equalIndex.size() == 1) {
            RETURN_SUM += (betList[equalIndex[0]] * rank);
            rank++;
            continue;
        }
        // Else, we need to put the hands in order of strength
        // Find the lowest hand, then find the next lowest, etc.
        for(int j = 0; j < equalIndex.size(); ++j) {
            int lowest_value = handList[equalIndex[0]][0];
            int lowest_index = equalIndex[0];
            for(int k = 1; j < equalIndex.size(); ++k) {
                if(handList[equalIndex[k]][0] < lowest_value) {
                    lowest_value = handList[equalIndex[k]][0];
                    lowest_index = k;
                }
                else if(handList[equalIndex[k]][0] == lowest_value) {

                }
            }
        }

    }
    std::cout << handType(handList[16]) << " " << betList[16] << " " << RETURN_SUM << std::endl;
}