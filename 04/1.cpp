#include <string>
#include <iostream>

bool adjacentDigits(std::string password) {
    for(int i=0; i<password.length() - 1; i++) {
        if(password[i] == password[i+1]) {
            if(i > 0) {
                if (i+2 >= password.length()) {
                    if(password[i-1] != password[i]) {
                        return true;
                    }
                } else {
                    if(password[i-1] != password[i]  && password[i+1] != password[i+2]) {
                        return true;
                    }
                }
            } else {
                if(password[i+1] != password[i+2]) {
                    return true;
                }
            }
            
        }
    }
    return false;
}

bool increasingDigits(std::string password) {
    for(int i=0; i<password.length() - 1; i++) {
        if(password[i] - '0' > password[i+1] - '0') {
            return false;
        }
    }
    return true;
}

int main() {
    int lowerBound = 240920;
    int upperBound = 789857;

    std::cout << adjacentDigits("123444") << increasingDigits("123789") << std::endl;
    std::cout << adjacentDigits("111122") << increasingDigits("123789") << std::endl;

    int matches = 0;
    for(int i=lowerBound; i<=upperBound; i++) {
        std::string str = std::to_string(i);
        if(adjacentDigits(str) && increasingDigits(str)){
            matches++;
        }
    }

    std::cout << matches << std::endl;
}