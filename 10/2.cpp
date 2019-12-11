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
#include <algorithm>

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
       return std::atan2(pointTwo[1] - pointOne[1], pointOne[0] - pointTwo[0]);
}

int main() {
   
    std::ifstream file("input.txt");
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
             std::cout << angle << std::endl;
             auto angleItr = angles.find(angle);
             if(angleItr == angles.end()) {
                     //std::cout << "Adding to visible asteroids" << std::endl;
                     angles.insert({ angle, 1 });
                     visible++;
             } else {
                std::cout << "Blocked" << std::endl;
             }
                     
       }
       if( visible > maxVisible) {
               maxVisible = visible;
               bestCoord = asteroidCoords[i];
               std::cout << "Overwriting max visible " << maxVisible << " (" << bestCoord[0] << ", " << bestCoord[1] << ")" << std::endl;

       }
       std::cout << asteroidCoords[i][0] << ", " << asteroidCoords[i][1] << std::endl;
    }
    std::cout << maxVisible << std::endl;
    std::cout << bestCoord[0] << ", " << bestCoord[1] << std::endl;
    asteroidCoords.erase(std::remove(asteroidCoords.begin(), asteroidCoords.end(), bestCoord), asteroidCoords.end());

    std::sort(asteroidCoords.begin(), asteroidCoords.end(), std::bind(compareDist, bestCoord, _1, _2));
        int counter = 0;

    std::array<int, 2> twoHCoord;
    while(counter < 200) {
        std::map<double, std::array<int, 2>> angles;
        for(int i=0; i<asteroidCoords.size(); i++) {
                //double angle = getAngle(bestCoord, asteroidCoords[i]);
                double angle = getAngle(asteroidCoords[i], bestCoord);
                std::cout << "(" << asteroidCoords[i][0] << ", " << asteroidCoords[i][1] << ") " << angle << std::endl;
                if (angle > M_PI / 2 ) {
                     angle -= M_PI * 2;
                     std::cout << "Adjusted angle " << angle << std::endl;
                }
                auto angleItr = angles.find(angle);
                if(angleItr == angles.end()) {
                     //std::cout << "Adding to visible asteroids" << std::endl;
                     angles.insert({ angle, asteroidCoords[i] });
                } else {
                     std::cout << "Blocked" << std::endl;
                }
        }
        //std::map<double, std::array<int,2>>::iterator it;
        for( auto it = --angles.end(); it != angles.begin(); it-- ) {
                std::cout << "Deleting at angle " << it->first << " asteroid at (" << it->second[0] << ", " << it->second[1] << ")" << std::endl;
                asteroidCoords.erase(std::remove(asteroidCoords.begin(), asteroidCoords.end(), it->second), asteroidCoords.end());
                counter++;
                if(counter == 200) {
                        twoHCoord = it->second;
                }
        }
    }

    std::cout << counter << std::endl;
    std::cout << twoHCoord[0]*100+twoHCoord[1] << std::endl;
  }
//}

