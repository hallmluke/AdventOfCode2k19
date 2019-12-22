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
        }

        if(outputDigitValue < 0) {
            outputDigitValue *= -1;
        }
        
        outputDigitValue = outputDigitValue % 10;
        
        output = output + std::to_string(outputDigitValue);

    }

    return output;
}

std::string calculatePhase2(std::string input, int offset) {
    int sum = 0;
    std::string output = input;
    for(int i = offset; i < input.size(); i++) {
        sum += input[i] - '0';
    }
    for(int j = offset; j<input.size(); j++) {
        int outputDigit = sum % 10;
        if(outputDigit < 0) {
            outputDigit *= -1;
        }
        output[j] = '0' + outputDigit;
        
        sum -= input[j] - '0';
    }

    return output;
}

int main(){

    std::ifstream file("input.txt");
    std::string input;
    std::getline(file, input);

    //std::string input = "03036732577212944063491565474664";
    std::string originalInput = input;

    int offset = std::stoi(input.substr(0, 7));

    std::cout << offset << std::endl;

    for(int i=0; i<9999; i++) {
        input = input + originalInput;
    }
    for(int i=0; i< 100; i++) {
        input = calculatePhase2(input, offset);
        std::cout << i << std::endl;
    }

    std::cout << input.size() << std::endl;
    std::cout << input.substr(offset, 8) << std::endl;
}