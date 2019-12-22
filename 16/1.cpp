#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <array>

std::array<int, 4> pattern = {0, 1, 0, -1};

std::string calculatePhase(std::string input) {

    std::string output = "";
    for(int outputDigit = 0; outputDigit<input.size(); outputDigit++) {
        
        int outputDigitValue = 0;
        for(int inputDigit=0; inputDigit<input.size(); inputDigit++) {
            int inputDigitValue = input[inputDigit] - '0';

            int patternIndex = ((inputDigit + 1) / (outputDigit + 1)) % pattern.size();

            outputDigitValue += inputDigitValue * pattern[patternIndex];
            //std::cout << inputDigitValue << "*" << pattern[patternIndex] << " + ";
        }

        if(outputDigitValue < 0) {
            outputDigitValue *= -1;
        }
        while(outputDigitValue > 9) {
            outputDigitValue = outputDigitValue % 10;
        }
        output = output + std::to_string(outputDigitValue);
        //std::cout << " = " << outputDigitValue << std::endl;
    }

    return output;
}
int main(){
    //std::string input = "12345678";
    //std::string output = calculatePhase(input);
    //std::cout << output << std::endl;

    std::ifstream file("input.txt");
    std::string input;
    std::getline(file, input);
    //std::string input = "80871224585914546619083218645595";

    for(int i=0; i< 100; i++) {
        input = calculatePhase(input);
        std::cout << i << std::endl;
    }

    std::cout << input << std::endl;
}