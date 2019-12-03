#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <bits/stdc++.h>

void moveWire(std::vector<std::array<int, 2>> *wireCoords, std::string move){
    char direction = move[0];
    int magnitude = std::stoi(move.substr(1));
    std::cout << direction << std::endl;
    std::cout << magnitude << std::endl;
    std::array<int, 2> lastPoint = wireCoords->back();
    std::cout << lastPoint[0] << std::endl;
    switch(direction) {
            case 'R':
                std::cout << "Going right!" << std::endl;
                for(int i=1; i<=magnitude; i++) {

                        std::array<int, 2> newPoint = {lastPoint[0] + i, lastPoint[1]};
                        wireCoords->push_back(newPoint);
                }
                break;
            case 'L':
                std::cout << "Going left!" << std::endl;
                for(int i=1; i<=magnitude; i++) {
                        std::array<int, 2> newPoint = {lastPoint[0] - i, lastPoint[1]};
                        wireCoords->push_back(newPoint);
                }

                break;
            case 'U':
                std::cout << "Going up!" << std::endl;
                for(int i=1; i<=magnitude; i++) {

                        std::array<int, 2> newPoint = {lastPoint[0], lastPoint[1] + i};
                        wireCoords->push_back(newPoint);
                }

                break;
            case 'D':
                std::cout << "Going down!" << std::endl;
                for(int i=1; i<=magnitude; i++) {

                        std::array<int, 2> newPoint = {lastPoint[0], lastPoint[1] - i};
                        wireCoords->push_back(newPoint);
                }

                break;
            default:
                break;
    }
}

std::vector<std::array<int,2>> getIntersects(std::vector<std::array<int, 2>> firstWireCoords, std::vector<std::array<int, 2>> secondWireCoords) {
        std::vector<std::array<int, 2>> intersectCoords;
        std::cout << "First size: " << firstWireCoords.size() << std::endl;
        std::cout << "Second size: " << secondWireCoords.size() << std::endl;
        std::sort(firstWireCoords.begin(), firstWireCoords.end());
        std::cout << "First sorted" << std::endl;
        std::sort(secondWireCoords.begin(), secondWireCoords.end());
        std::cout << "Second sorted" << std::endl;
        std::set_intersection(firstWireCoords.begin(), firstWireCoords.end(), secondWireCoords.begin(), secondWireCoords.end(), std::back_inserter(intersectCoords));
        return intersectCoords;
}

int getDist(std::array<int, 2> firstPoint, std::array<int, 2> secondPoint) {
        return std::abs(firstPoint[0] - secondPoint[0]) + std::abs(firstPoint[1] - secondPoint[1]);
}

int main() {


    std::ifstream file("input.txt");
    std::string str;
    std::vector<std::string> firstWirePath;
    std::getline(file,str);
        std::stringstream lineStream(str);
        std::string cell;
        while(std::getline(lineStream,cell,',')) {
            firstWirePath.push_back(cell);
        }

    
    std::vector<std::string> secondWirePath;
    std::getline(file,str);
    std::stringstream lineStream2(str);
    std::string cell2;
        while(std::getline(lineStream2,cell2,',')) {
            secondWirePath.push_back(cell2);
        }

    
    for(int i = 0; i<firstWirePath.size(); i++) {
        std::cout << firstWirePath[i] << std::endl;
    }

    std::cout << "==================" << std::endl;

    for(int j = 0; j<secondWirePath.size(); j++){
        std::cout << secondWirePath[j] << std::endl;
    }
    std::array<int, 2> startPoint = {0, 0};
    std::vector<std::array<int, 2>> firstWireCoords;
    std::vector<std::array<int, 2>> secondWireCoords;

    firstWireCoords.push_back(startPoint);
    secondWireCoords.push_back(startPoint);

for(int i=0; i < firstWirePath.size(); i++) {
        moveWire(&firstWireCoords, firstWirePath[i]);
    }
    for(int j=0; j < secondWirePath.size(); j++) {
        moveWire(&secondWireCoords, secondWirePath[j]);
    }

    firstWireCoords.erase(firstWireCoords.begin());
    secondWireCoords.erase(secondWireCoords.begin());
    std::vector<std::array<int, 2>> intersectCoords = getIntersects(firstWireCoords, secondWireCoords);
    int smallestDist = 999999999;
    int leastSteps = 99999999;
    for(int i=0; i<intersectCoords.size(); i++) {
        int dist = getDist(startPoint, intersectCoords[i]);
        if(dist < smallestDist) {
                smallestDist = dist;
        }
        std::cout << intersectCoords[i][0] << ", " << intersectCoords[i][1] << std::endl;
        int firstSteps = std::distance(firstWireCoords.begin(), std::find(firstWireCoords.begin(), firstWireCoords.end(), intersectCoords[i])) + 1;
        int secondSteps = std::distance(secondWireCoords.begin(), std::find(secondWireCoords.begin(), secondWireCoords.end(), intersectCoords[i])) + 1;
        int totalSteps = firstSteps + secondSteps;
        if(totalSteps < leastSteps) {
                leastSteps = totalSteps;
        }

    }
    std::cout << smallestDist << std::endl; 
    std::cout << leastSteps << std::endl;
    return 0;
}
