#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int getIntCodeOutput(std::vector<int> input) {
    int i = 0;
    std::vector<int> vals = input;
    int instruction = vals[i];
    std::cout << "Instruction: " << instruction << std::endl;
    int opCode = instruction % 10;
    std::cout << "Op Code: " << opCode << std::endl;
    std::vector<int> parameterModes;

    while(instruction > 0) {
        instruction = instruction / 10;
        std::cout << "Param mode: " << instruction % 10 << std::endl;
        parameterModes.push_back(instruction % 10);
    }
    /*while(i < vals.size()){
        if(vals[i] == 1){
            vals[vals[i+3]] = vals[vals[i+1]] + vals[vals[i+2]];
            i += 4;
        } else if (vals[i] == 2){
            vals[vals[i+3]] = vals[vals[i+1]] * vals[vals[i+2]];
            i += 4;
        } else if (vals[i] == 99){
            break;
        } else {
            std::cout << "Something went wrong!" << std::endl;
            break;
            
        }
    }*/

    return vals[0];

}

int main() {


    std::ifstream file("input.txt");
    std::string str;
    std::vector<int> parsedCsv;
    while(std::getline(file,str)) {
        std::stringstream lineStream(str);
        std::string cell;
        while(std::getline(lineStream,cell,',')) {
            int cellVal = std::stoi(cell);
            parsedCsv.push_back(cellVal);
        }

    }
    
    std::vector<int> testVals;
    testVals.push_back(1003);
    getIntCodeOutput(testVals);
    
}


