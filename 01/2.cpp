#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

int fuelForModule(int moduleMass) {
    int totalFuel = std::floor(moduleMass / 3) - 2;
    int currentFuel = totalFuel;
    
    while (currentFuel > 0) {
        currentFuel = std::floor(currentFuel / 3) - 2;
        if (currentFuel < 0) {
            currentFuel = 0;
        }
        std::cout << "Current fuel: " << currentFuel << std::endl;
        totalFuel += currentFuel;
    }
    return totalFuel;
}

int main() {
    int totalMass = 0;

    std::cout << fuelForModule(14) << std::endl;
    std::cout << fuelForModule(1969) << std::endl;
    std::cout << fuelForModule(100756) << std::endl;

    std::ifstream file("input.txt");
    std::string str;
    while(std::getline(file,str)) {
        int moduleMass = fuelForModule(std::stoi(str));
        totalMass += moduleMass;
    }

    std::cout << totalMass << std::endl;
}