#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int getIntCodeOutput(std::vector<int> input) {
    int i = 0;
    std::vector<int> parsedCsv = input;
    while(i < parsedCsv.size()){
        if(parsedCsv[i] == 1){
            parsedCsv[parsedCsv[i+3]] = parsedCsv[parsedCsv[i+1]] + parsedCsv[parsedCsv[i+2]];
            i += 4;
        } else if (parsedCsv[i] == 2){
            parsedCsv[parsedCsv[i+3]] = parsedCsv[parsedCsv[i+1]] * parsedCsv[parsedCsv[i+2]];
            i += 4;
        } else if (parsedCsv[i] == 99){
            break;
        } else {
            std::cout << "Something went wrong!" << std::endl;
            break;
            
        }
    }

    return parsedCsv[0];

}

int main() {


    std::ifstream file("input.txt");
    std::string str;
    std::vector<int> parsedCsv;
    while(std::getline(file,str)) {
        std::stringstream lineStream(str);
        std::string cell;
        while(std::getline(lineStream,cell,',')) {
            std::cout << cell << std::endl;
            std::cout << std::stoi(cell) << std::endl;
            int cellVal = std::stoi(cell);
            parsedCsv.push_back(cellVal);
        }

    }
    
    for(int i=0; i<100; i++) {
        int result = 0;
        for(int j=0; j<100; j++) {
             std::vector<int> inputTry = parsedCsv;
             inputTry[1] = i;
             inputTry[2] = j;
             result = getIntCodeOutput(inputTry);
             if(result == 19690720) {
                std::cout << "Success! " << i << " " << j << std::endl;
                break;
             }
        }
        if(result == 19690720) {
                break;
        }
    }
    std::cout << parsedCsv[0] << std::endl;
}


