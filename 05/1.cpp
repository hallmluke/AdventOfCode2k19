#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int getIntCodeOutput(std::vector<int> input, int userInput) {
    int i = 0;
    std::vector<int> vals = input;
    int programInput = userInput;
    int programOutput = 0;

    while( i < vals.size() ) {
    //std::string instruction = vals[i];
    int instructionVal = vals[i]; //std::stoi(instruction);
    std::cout << "Instruction: " << instructionVal << std::endl;
    int opCode = instructionVal % 100;
    std::cout << "Op Code: " << opCode << std::endl;
    std::vector<int> parameterModes;

        instructionVal = instructionVal / 100;
    //for(int j=0; j<instruction.length()-1; j++) {
    while(instructionVal > 0) {
        std::cout << "Param mode: " << instructionVal % 10 << std::endl;
        parameterModes.push_back(instructionVal % 10);
        instructionVal = instructionVal / 10;

    }

    //parameterModes.pop_back();

    std::vector<int> parameters;

    if(parameterModes.size() == 0){
    //    if(opCode == 1 || opCode == 2) {
                parameterModes = { 0, 0 };
     //   }
    }
    if(parameterModes.size() == 1){// && (opCode == 1 || opCode == 2)){
            parameterModes.push_back(0);
    }
    for(int k=0; k<parameterModes.size(); k++){
        int parameter = 0;
        if(parameterModes[k] == 0){
            parameter = vals[vals[i+k+1]];
        } else if(parameterModes[k] == 1) {
            std::cout << "Assign param: " << vals[i+k+1] << " i " << i << " k " << k << std::endl;
            parameter = vals[i+k+1];
        } else {
            std::cout << "Something disastrous happened" << std::endl;
        }
        std::cout << "Parameter: " << parameter << std::endl;
        parameters.push_back(parameter);
    }

    int result;
    switch(opCode) {
            case 1:
                result = 0;
                for(int j = 0; j < parameters.size(); j++) {
     //                   std::cout << "Ading param: " << parameters[j] << "j" << j << std::endl;
                        result += parameters[j];
                }
                vals[vals[i + parameters.size() + 1]] = result;
                i += parameters.size() + 2;
                break;
            case 2:
                result = 1;
                for(int j =0; j < parameters.size(); j++) {
                        result *= parameters[j];
                }
                vals[vals[i + parameters.size() + 1]] = result;
                i += parameters.size() + 2;
                break;
            case 3:
                vals[vals[i+1]] = programInput; //use params
                i += 2;
                break;
            case 4:
                //programOutput = vals[vals[i+1]; // use params
                if(parameters.size() > 0){
                        programOutput = parameters[0];
                } else {
                        programOutput = vals[vals[i+1]];
                }
                if(vals[i+2] != 99 && programOutput != 0 ){
                        std::cout << "ugh" << std::endl;
                        return -1;
                }
                i += 2;
                break;
            case 5:
                if(parameters[0] != 0){
                        i = parameters[1];
                } else {
                        i += 3;
                }
                break;
            case 6:
                if(parameters[0] == 0){
                        i = parameters[1];
                } else {
                        i += 3;
                }
                break;
            case 7:
                if(parameters[0] < parameters[1]){
                      //  if(parameters.size() > 2){
                      //          vals[parameters[2]] = 1;
                      //  } else {
                      //          vals[vals[i+3]] = 1;
                      //  }
                      vals[vals[i+3]] = 1;
                } else {
                      //  if(parameters.size() > 2){
                      //          vals[parameters[2]] = 0;
                      //  } else {
                                vals[vals[i+3]] = 0;
                 //       }
                }
                i += 4;
                break;
            case 8:
                if(parameters[0] == parameters[1]){
                 //       if(parameters.size() > 2){
                   //             vals[parameters[2]] = 1;
                    //    } else {
                                vals[vals[i+3]] = 1;
                } else {
                        vals[vals[i+3]] = 0;
                }
                i += 4;
                break;
            case 99:
                std::cout << "Program end" << std::endl;
                return programOutput;
                break;
            default:
                std::cout << "Messed up, bud" << std::endl;
                return -1;
                break;
    }
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
    for(int j=0; j<vals.size(); j++){
            std::cout << vals[j] << ", " << std::endl; 
    }
    return programOutput;

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
    
    std::vector<int> testVals = { 3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8};
    std::vector<int> testVals2 = { 3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9 };
    // params: 103, 90
   // int output = getIntCodeOutput(testVals2, 0);
    int output = getIntCodeOutput(parsedCsv, 5);
    std::cout << output << std::endl;
    
}


