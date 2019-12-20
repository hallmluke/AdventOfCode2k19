#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <array>
#include <map>

class Point {
    public:
        Point(int _x, int _y) : x(_x), y(_y) {};
        int x;
        int y;
}
class Amp {
    public:
    Amp(std::vector<long long> _numbers, int _position = 0, int _phase = 1, int _input = 0, int _relativeBase = 0) {
        numbers = _numbers;
        position = _position;
        phase = _phase;
        input = _input;
        relativeBase = _relativeBase;
    }
    std::vector<long long> numbers;
    int position;
    int phase;
    int input;
    int relativeBase;
};

long long getIntCodeOutput(std::vector<Amp>& amplifiers, bool debug)
{
    int i = amplifiers[0].position;
    std::cout << "START POSITION (i): " << i << std::endl;
    std::vector<long long> vals = amplifiers[0].numbers;
   // std::cout << "First val" <<
    vals.resize(10000);
    int currentAmplifier = 0;
    long long programOutput = 0;
    int relativeBase = amplifiers[0].relativeBase;

    while (i < vals.size())
    {
        //std::string instruction = vals[i];
        long long instructionVal = vals[i]; //std::stoi(instruction);
        if(debug) {
                std::cout << "Instruction: " << instructionVal << std::endl;
        }
        int opCode = (int) (instructionVal % 100);
        if(debug) {
                std::cout << "Op Code: " << opCode << std::endl;
        }
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
        //std::cout << "Past param modes" << std::endl;
        std::vector<long long> parameters;

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
            long long parameter = 0;
            //std::cout << "Param modes for loop" << std::endl;
            if (parameterModes[k] == 0)
            {
//std::cout << i << " " << k << " " << vals.size() << std::endl;
                if(vals[i + k + 1] < vals.size()) {
                parameter = vals[vals[i + k + 1]];
                }
                else {
                        std::cout << "big param" << std::endl;
                }
                            }
            else if (parameterModes[k] == 1)
            {
//std::cout << 1 << std::endl;
                //std::cout << "Assign param: " << vals[i + k + 1] << " i " << i << " k " << k << std::endl;
                parameter = vals[i + k + 1];
                
            }
            else if (parameterModes[k] == 2) {
 //std::cout << 2 << std::endl;
 //std::cout << i + k + 1 + relativeBase << std::endl;
                parameter = vals[vals[i + k + 1] + relativeBase];
               
            }
            else
            {
                //std::cout << "Something disastrous happened" << std::endl;
            }
            if(debug){
                std::cout << "Parameter: " << parameter << std::endl;
            }
            parameters.push_back(parameter);
        }
        //std::cout << "To opcode switch" << std::endl;
        long long result;
        std::cout << "i: " << i << std::endl;
        switch (opCode)
        {
        case 1:
            result = 0;
            //for (int j = 0; j < parameters.size(); j++)
            //{
                //                   std::cout << "Ading param: " << parameters[j] << "j" << j << std::endl;
                result = parameters[0] + parameters[1];
            //}
            if(parameters.size() > 2){
                vals[vals[i+3]+relativeBase] = result;
            } else {
            if(debug){
                std::cout << "Put " << result << " at " << vals[i+parameters.size()+1] << std::endl;
            }
            vals[vals[i + parameters.size() + 1]] = result;
            }
            i += 4;
            break;
        case 2:
            result = 1;
            //for (int j = 0; j < parameters.size(); j++)
            //{
                result = parameters[0]*parameters[1];
            //}
            if(parameters.size() > 2){
                if(debug){
                        std::cout << "Place at " << vals[i+3]+relativeBase << std::endl;
                }
                vals[vals[i + 3] + relativeBase] = result;
            } else {
                vals[vals[i + parameters.size() + 1]] = result;
                if(debug){
                        std::cout << "Put " << result << " at " << vals[i+parameters.size()+1] << std::endl;
                }
            }
            i+=4;
            //i += parameters.size() + 2;
            break;
        case 3:
            //if(i == 0) {
             //   vals[vals[i + 1]] = phaseSetting;
            //} else {
                if(parameterModes[0] == 2) {
                    vals[vals[i+1]+relativeBase] = amplifiers[currentAmplifier].phase;
                    if(debug) {
                        std::cout << "Put 1 at " << vals[i+1]+relativeBase << std::endl;
                    }
                } else {
                    vals[vals[i+1]] = amplifiers[currentAmplifier].phase;
                    amplifiers[currentAmplifier].phase = amplifiers[currentAmplifier].input;
                    if(debug) {
                        std::cout << "Put 1 at " << vals[i+1] << std::endl;
                    }
                }
            //}
            i += 2;
            break;
        case 4:
            //programOutput = vals[vals[i+1]; // use params
            //std::cout << "Hit 4" << std::endl;
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
                std::cout << programOutput << std::endl;
                return -1;
            }*/ 
            std::cout << std::endl << "OUTPUT" << std::endl << programOutput << std::endl << std::endl;
            i += 2;
            amplifiers[currentAmplifier].position = i;
            amplifiers[currentAmplifier].numbers = vals;
            amplifiers[currentAmplifier].relativeBase = relativeBase;

            currentAmplifier = (currentAmplifier + 1) % 1;
            //std::cout << "Current amplifier " << currentAmplifier << std::endl;
            i = amplifiers[currentAmplifier].position;
            vals = amplifiers[currentAmplifier].numbers;
            //if(debug) {
                    std::cout << "END POSITION (i): " << i << std::endl;

            //if(amplifiers[currentAmplifier].phase == amplifiers[currentAmplifier].input) {
            //    amplifiers[currentAmplifier].phase = programOutput;
            //}
            //amplifiers[currentAmplifier].input = programOutput;
            return programOutput;
            break;
        case 5:
            if (parameters[0] != 0)
            {
                /*if(parameterModes[1] == 2) {
                        i = vals[i+2]+relativeBase;
                        
                        std::cout << "Go to " << vals[i+1]+relativeBase << std::endl;
                } else {*/
                if(debug){
                std::cout << "Go to " << parameters[1] <<  " because " << parameters[0] << " is not 0" << std::endl;
                }
                i = parameters[1];
                //}
                
            }
            else
            {
                if(debug){
                std::cout << "Op code 5 did nothing" << std::endl;
                }
                i += 3;
            }
            break;
        case 6:
            if (parameters[0] == 0)
            {
                /*if(parameterModes[1] == 2){

                        i = vals[i+2] + relativeBase;
                        std::cout << vals[i+1] << std::endl;
                        std::cout << relativeBase << std::endl;
                        std::cout << vals[i+2] << std::endl;
                        std::cout << "Go to " << i << std::endl;
                } else {*/
                if(debug){
                std::cout << "Go to " << parameters[1] <<  " because " << parameters[0] << " is 0" << std::endl;
                }
                i = parameters[1];
                //}
                
            }
            else
            {
                if(debug){
                std::cout << "Op code 6 did nothing" << std::endl;
                }
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
                if(parameters.size() > 2){
                    std::cout << "vals[i+3] " << vals[i+3] << std::endl;
                    std::cout << "Relative base: " << relativeBase;
                    vals[vals[i+3] + relativeBase] = 1;
                    if(debug){
                    std::cout << "Set " << vals[i+3]+relativeBase << " to 1 because " << parameters[0] << " < " << parameters[1] << std::endl;
                    }
                } 
                else {
                vals[vals[i + 3]] = 1;
                if(debug){
                std::cout << "Set " << vals[i+3] << " to 1 because " << parameters[0] << " < " << parameters[1] << std::endl;
                }
                }
            }
            else
            {
                //  if(parameters.size() > 2){
                //          vals[parameters[2]] = 0;
                //  } else {
                if(parameters.size() > 2){
                    vals[vals[i+3] + relativeBase] = 0;
                    if(debug){
                    std::cout << "Set " << vals[i+3]+relativeBase << " to 0 because " << parameters[0] << " < " << parameters[1] << std::endl;
                    }
                }  else {
                vals[vals[i + 3]] = 0;
                if(debug){
                std::cout << "Set " << vals[i+3] << " to 0 because " << parameters[0] << " !< " << parameters[1] << std::endl;
                }
                }
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
                    if(parameters.size() > 2) {
                        vals[vals[i+3] + relativeBase] = 1;
                        if(debug){
                        std::cout << "Set " << vals[i+3]+relativeBase << " to 1 because " << parameters[0] << " == " << parameters[1] << std::endl;
                        }
                    } else {
                vals[vals[i + 3]] = 1;
                if(debug){
                std::cout << "Set " << vals[i+3] << " to 1 because " << parameters[0] << " == " << parameters[1] << std::endl;
                }
                    }
            }
            else
            {
          //      std::cout << "Set " << vals[i+3] << " to 0 because " << parameters[0] << " != " << parameters[1] << std::endl;
                vals[vals[i + 3]] = 0;
            }
            i += 4;
            break;
        case 9:
            relativeBase += parameters[0];
            std::cout << "Relative Base: " << relativeBase << std::endl;
            i += 2;
            break;
        case 99:
            std::cout << "Program end " << programOutput << std::endl;
            return -1;
            break;
        default:
            std::cout << "Messed up, bud" << std::endl;
            return -1;
            break;
        }
    }

    return programOutput;
}


std::vector<long long> parseInput(){
    std::ifstream file("input.txt");
    std::string str;
    std::vector<long long> parsedCsv;
    while (std::getline(file, str))
    {
        std::stringstream lineStream(str);
        std::string cell;
        while (std::getline(lineStream, cell, ','))
        {
            long long cellVal = std::stoll(cell);
            std::cout << cellVal << std::endl;
            parsedCsv.push_back(cellVal);
        }
    }
return parsedCsv;

}

class RepairDroid {
    public:
       Point position;
       std::vector<Amp> amplifiers;
       std::set<Point> wallsHit;
       std::set<Point> visited;
       int move(int direction) {
                Point target = position;
                amplifiers[0].phase = direction;
                int statusCode = getIntCodeOutput(amplifiers, false);
                switch(direction) {
                           case 1:
                                target.y++;
                                break;
                           case 2:
                                target.y--;
                                break;
                           case 3:
                                target.x--;
                                break;
                           case 4:
                                target.x++;
                                break;
                           default:
                                std::cout << "Invalid move direction" << std::endl;
                                throw;
                                break;
                        }

                if(statusCode == 0) {
                      wallsHit.insert(target);
                }
                if(statusCode == 1 || statusCode == 2) {
                      visited.insert(target);                        
                }
                return statusCode;
       }
}

int main() {
        auto vals = parseInput();
        vals[0] = 2;
        std::vector<Amp> amplifiers(1, vals);
        //long long output = getIntCodeOutput(amplifiers);
        //std::cout << output << std::endl;
        std::map<std::array<int, 2>, int> tiles;
        int output = 0;
        while(output != -1){
                output = getIntCodeOutput(amplifiers, false);
                if(output == -1){
                        break;
                }
                int xPos = output;
                std::cout << "xPos: " << xPos << std::endl;
                output = getIntCodeOutput(amplifiers, false);
                if(output == -1){
                        break;
                }
                int yPos = output;
                std::cout << "yPos: " << yPos << std::endl;

                std::array<int, 2> tilePos = { xPos, yPos };
                output = getIntCodeOutput(amplifiers, false);
                int tile = output;
                tiles[tilePos] = tile;
                std::cout << "Tile: " << tile << std::endl;
                if(tile == 3) {
                        std::cout << "Block added" << std::endl;
                }
                if(tile > 4) {
                        std::cout << "Something is not right" << std::endl;
                        break;
                }
           }
           int blockCount = 0;
        for (auto it = tiles.begin(); it != tiles.end(); ++it) {
                std::cout << "(" << it->first[0] << "," << it->first[1] << "): " << it->second << std::endl;
                if(it -> second == 2) {
                        blockCount++;
                }
        }

        std::cout << blockCount << std::endl;
        }

