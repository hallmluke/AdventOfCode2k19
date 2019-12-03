#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


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

    return 0;
}