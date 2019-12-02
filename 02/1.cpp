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

    

    parsedCsv[1] = 12;
    parsedCsv[2] = 2;

    for(int i = 0; i < parsedCsv.size(); i++){
        std::cout << "parsedCsv[i]: " << parsedCsv[i] << std::endl;
        std::cout << "parsedCsv[i+3]: " << parsedCsv[i+3] << std::endl;
        std::cout << "parsedCsv[parsedCsv[i+3]]: " << parsedCsv[parsedCsv[i+3]] << std::endl;
        if(parsedCsv[i] == 1){
            parsedCsv[parsedCsv[i+3]] = parsedCsv[i+1] + parsedCsv[i+2];
            i += 4;
        } else if (parsedCsv[i] == 2){
            parsedCsv[parsedCsv[i+3]] = parsedCsv[i+1] * parsedCsv[i+2];
            i += 4;
        } else if (parsedCsv[i] == 99){
            break;
        } else {
            std::cout << "Something went wrong!" << std::endl;
            break;
            
        }
    }
    
    std::cout << parsedCsv[0] << std::endl;
}