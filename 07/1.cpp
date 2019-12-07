#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
std::vector<std::string> permutations;
void permute(std::string a, int l, int r) {
    std::vector<std::string> v;
    if(l == r) {
        permutations.push_back(a);
    } else {
        for(int i = l; i<= r; i++) {
            std::swap(a[l], a[i]);

            permute(a, l+1, r);

            std::swap(a[l], a[i]);
        }
    }
}

class Amp {
    public:
    Amp(std::vector<int> _numbers, int _position = 0, int _phase = 0, int _input = 0) {
        numbers = _numbers;
        position = _position;
        phase = _phase;
        input = _input;
    }
    std::vector<int> numbers;
    int position;
    int phase;
    int input;
};

int getIntCodeOutput(std::vector<Amp> amplifiers)//, int userInput, int phaseSetting)
{
    int i = 0;
    std::vector<int> vals = amplifiers[0].numbers;
    int currentAmplifier = 0;
    int programOutput = 0;

    while (i < vals.size())
    {
        //std::string instruction = vals[i];
        int instructionVal = vals[i]; //std::stoi(instruction);
        std::cout << "Instruction: " << instructionVal << std::endl;
        int opCode = instructionVal % 100;
        std::cout << "Op Code: " << opCode << std::endl;
        std::vector<int> parameterModes;

        instructionVal = instructionVal / 100;
        //for(int j=0; j<instruction.length()-1; j++) {
        while (instructionVal > 0)
        {
            //std::cout << "Param mode: " << instructionVal % 10 << std::endl;
            parameterModes.push_back(instructionVal % 10);
            instructionVal = instructionVal / 10;
        }

        //parameterModes.pop_back();

        std::vector<int> parameters;

        if (parameterModes.size() == 0)
        {
            //    if(opCode == 1 || opCode == 2) {
            parameterModes = {0, 0};
            //   }
        }
        if (parameterModes.size() == 1)
        { // && (opCode == 1 || opCode == 2)){
            parameterModes.push_back(0);
        }
        for (int k = 0; k < parameterModes.size(); k++)
        {
            int parameter = 0;
            if (parameterModes[k] == 0)
            {
                parameter = vals[vals[i + k + 1]];
            }
            else if (parameterModes[k] == 1)
            {
                //std::cout << "Assign param: " << vals[i + k + 1] << " i " << i << " k " << k << std::endl;
                parameter = vals[i + k + 1];
            }
            else
            {
                //std::cout << "Something disastrous happened" << std::endl;
            }
            //std::cout << "Parameter: " << parameter << std::endl;
            parameters.push_back(parameter);
        }

        int result;
        switch (opCode)
        {
        case 1:
            result = 0;
            for (int j = 0; j < parameters.size(); j++)
            {
                //                   std::cout << "Ading param: " << parameters[j] << "j" << j << std::endl;
                result += parameters[j];
            }
            vals[vals[i + parameters.size() + 1]] = result;
            i += parameters.size() + 2;
            break;
        case 2:
            result = 1;
            for (int j = 0; j < parameters.size(); j++)
            {
                result *= parameters[j];
            }
            vals[vals[i + parameters.size() + 1]] = result;
            i += parameters.size() + 2;
            break;
        case 3:
            //if(i == 0) {
             //   vals[vals[i + 1]] = phaseSetting;
            //} else {
                vals[vals[i+1]] = amplifiers[currentAmplifier].phase;
                amplifiers[currentAmplifier].phase = amplifiers[currentAmplifier].input;
            //}
            i += 2;
            break;
        case 4:
            //programOutput = vals[vals[i+1]; // use params
            std::cout << "Hit 4" << std::endl;
            if (parameters.size() > 0)
            {
                programOutput = parameters[0];
            }
            else
            {
                programOutput = vals[vals[i + 1]];
            }
            /*if (vals[i + 2] != 99 && programOutput != 0)
            {
                std::cout << "ugh" << std::endl;
                return -1;
            } */
            i += 2;
            amplifiers[currentAmplifier].position = i;
            amplifiers[currentAmplifier].numbers = vals;

            currentAmplifier = (currentAmplifier + 1) % 5;
            std::cout << "Current amplifier " << currentAmplifier << std::endl;
            i = amplifiers[currentAmplifier].position;
            vals = amplifiers[currentAmplifier].numbers;

            if(amplifiers[currentAmplifier].phase == amplifiers[currentAmplifier].input) {
                amplifiers[currentAmplifier].phase = programOutput;
            }
            amplifiers[currentAmplifier].input = programOutput;
            break;
        case 5:
            if (parameters[0] != 0)
            {
                i = parameters[1];
            }
            else
            {
                i += 3;
            }
            break;
        case 6:
            if (parameters[0] == 0)
            {
                i = parameters[1];
            }
            else
            {
                i += 3;
            }
            break;
        case 7:
            if (parameters[0] < parameters[1])
            {
                //  if(parameters.size() > 2){
                //          vals[parameters[2]] = 1;
                //  } else {
                //          vals[vals[i+3]] = 1;
                //  }
                vals[vals[i + 3]] = 1;
            }
            else
            {
                //  if(parameters.size() > 2){
                //          vals[parameters[2]] = 0;
                //  } else {
                vals[vals[i + 3]] = 0;
                //       }
            }
            i += 4;
            break;
        case 8:
            if (parameters[0] == parameters[1])
            {
                //       if(parameters.size() > 2){
                //             vals[parameters[2]] = 1;
                //    } else {
                vals[vals[i + 3]] = 1;
            }
            else
            {
                vals[vals[i + 3]] = 0;
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
    for (int j = 0; j < vals.size(); j++)
    {
        std::cout << vals[j] << ", " << std::endl;
    }
    return programOutput;
}

int main()
{

    std::ifstream file("input.txt");
    std::string str;
    std::vector<int> parsedCsv;
    while (std::getline(file, str))
    {
        std::stringstream lineStream(str);
        std::string cell;
        while (std::getline(lineStream, cell, ','))
        {
            int cellVal = std::stoi(cell);
            parsedCsv.push_back(cellVal);
        }
    }

    std::vector<int> testVals = {3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8};
    std::vector<int> testVals2 = {3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9};
    // params: 103, 90
    // int output = getIntCodeOutput(testVals2, 0);

std::string phases = "56789";
permute(phases, 0, 4);
int maxThrust = 0;
int ptr = 0;
std::vector<Amp> amplifiers(5, parsedCsv);

for(int i=0; i<permutations.size(); i++){
    std::string permVal = permutations[i];
    std::cout << "Perm val " << permVal << std::endl;
    int input = 0;
    //while(permVal.size() > 0) {
    for(int j = 0; j < permVal.size(); j++) {
        std::cout << "Perm val in loop" << permVal[j] << std::endl;
        int phase = permVal[j] - '0';
        //std::cout << "Phase " << phase << std::endl;
        //std::cout << "Input " << input << std::endl;
        //std::vector<int> ampProgram = parsedCsv;
        //std::cout << "Phase " << phase << std::endl;
        amplifiers[j].phase = phase;
        std::cout << "After phase assign" << std::endl;
        
    }
    input = getIntCodeOutput(amplifiers);
    //std::cout << "Finished Amp" << std::endl;
    if(input > maxThrust) {
        maxThrust = input;
        ptr = i;
    }
}
std::cout << maxThrust << std::endl;
    /*
    std::vector<int> ampProgram = parsedCsv;
    int Aoutput = getIntCodeOutput(ampProgram, 0, 4);
    std::vector<int> ampProgram2 = parsedCsv;
    int Boutput = getIntCodeOutput(ampProgram2, Aoutput, 3);
    std::vector<int> ampProgram3 = parsedCsv;
    int Coutput = getIntCodeOutput(ampProgram3, Boutput, 2);
    std::vector<int> ampProgram4 = parsedCsv;
    int Doutput = getIntCodeOutput(ampProgram4, Coutput, 1);
    std::vector<int> ampProgram5 = parsedCsv;
    int Eoutput = getIntCodeOutput(ampProgram5, Doutput, 0); */
    //std::cout << Eoutput << std::endl;
}


