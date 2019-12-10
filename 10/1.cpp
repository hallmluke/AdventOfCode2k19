#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <bits/stdc++.h>
#include <functional>
#include <map>

using namespace std::placeholders;

double getDist(std::array<int, 2> pointOne, std::array<int, 2> pointTwo) {
 //       std::cout << pointOne[0] << ", " << pointOne[1] << std::endl;
   //     std::cout << pointTwo[0] << ", " << pointTwo[1] << std::endl;

        return std::pow((pointOne[0]-pointTwo[0]),2) + std::pow((pointOne[1]-pointTwo[1]),2);
}

bool compareDist(std::array<int, 2> originPoint, std::array<int, 2> pointOne, std::array<int, 2> pointTwo) {
 //               std::cout << getDist(originPoint, pointOne) << std::endl;
//        std::cout << getDist(originPoint, pointTwo) << std::endl;
        return getDist(originPoint, pointOne) < getDist(originPoint, pointTwo);
}

double getAngle(std::array<int, 2> pointOne, std::array<int, 2> pointTwo) {
       return std::atan2(pointOne[1] - pointTwo[1], pointOne[0] - pointTwo[0]);
}

int main() {
   
    std::ifstream file("testinput1.txt");
    std::string str;
    int row;
    std::vector<std::array<int, 2>> asteroidCoords;
    while(std::getline(file,str)) {
       for(int i=0; i<str.size(); i++) {
                if(str[i] == '#') {
                        std::array<int, 2> coord = { i, row };
//                        std::cout << coord[0] << ", " << coord[1] << std::endl;
                        asteroidCoords.push_back(coord);
                }
       }
       row++;
    }

    double testDist = getDist(asteroidCoords[0], asteroidCoords[2]);
    double testDist2 = getDist(asteroidCoords[0], asteroidCoords[3]);
    //std::cout << testDist << " " << testDist2 << std::endl;
    std::sort(asteroidCoords.begin(), asteroidCoords.end(), std::bind(compareDist, asteroidCoords[0], _1, _2));

    int maxVisible = 0;
    std::array<int, 2> bestCoord;
    std::vector<std::array<int,2>> iterAsteroids;
    std::copy(asteroidCoords.begin(), asteroidCoords.end(), back_inserter(iterAsteroids));
    for(int i=0; i<asteroidCoords.size(); i++){
       std::sort(iterAsteroids.begin(), iterAsteroids.end(), std::bind(compareDist, asteroidCoords[i], _1, _2));
       std::map<double, int> angles;
       int visible = 0;
       for(int j=1; j<iterAsteroids.size(); j++) {
             double angle = getAngle(asteroidCoords[i], iterAsteroids[j]);
             std::cout << "Angle between (" << asteroidCoords[i][0] << ", " << asteroidCoords[i][1] << ") and (" << iterAsteroids[j][0] << ", " << iterAsteroids[j][1] << ")" << std::endl;
          //   std::cout << angle << std::endl;
             auto angleItr = angles.find(angle);
             if(angleItr == angles.end()) {
                     angles.insert({ angle, 1 });
                     visible++;
             } else {
                std::cout << "Blocked" << std::endl;
             }
                     
       }
       if( visible > maxVisible) {
               maxVisible = visible;
               bestCoord = asteroidCoords[0];
       }
       std::cout << asteroidCoords[i][0] << ", " << asteroidCoords[i][1] << std::endl;
    }
    std::cout << maxVisible << std::endl;
    std::cout << bestCoord[0] << ", " << bestCoord[1] << std::endl;
}
