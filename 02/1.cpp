#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


int main() {


    std::ifstream file("input.txt");
    std::string str;
    std::vector<int> parsedCsv;
    while(std::getline(file,str)) {
        std::stringstream lineStream(str);
        std::string cell;
        while(std::getline(lineStream,cell,',')) {
            parsedCsv.push_back(std::stoi(cell));
        }

    }

    for(int i : parsedCsv) {
        std::cout << i << std::endl;
    }
    
}