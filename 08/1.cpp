#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main()
{

    std::ifstream file("input.txt");
    std::string str;
    std::getline(file, str);

    std::vector<std::string> layers;
    int width = 25;
    int height = 6;
    int totalPix = width * height;
    std::string finalImage;

    while(str.size() > 0) {
        layers.push_back(str.substr(0, totalPix));
        str = str.substr(totalPix);
    }
    int fewestZeroes = 999;
    int fewestZeroesLayer = 0;
    for(int i=0; i<layers.size(); i++) {
        std::cout << "Layer " << i << ": " << layers[i] << std::endl;
        int zeroes = 0;
        for(int j=0; j<layers[i].size(); j++) {
            if(layers[i][j] == '0') {
                //finalImage = finalImage + '0';
                zeroes++;
                break;
            } else if(layers[i][j] == '1') {
                //finalImage = finalImage
            }
        }
        if(zeroes < fewestZeroes) {
            fewestZeroes = zeroes;
            fewestZeroesLayer = i;
        }
    }

    int ones = 0;
    int twos = 0;

    for(int i=0; i<layers[fewestZeroesLayer].size(); i++) {
        if(layers[fewestZeroesLayer][i] == '1') {
            ones++;
        } else if (layers[fewestZeroesLayer][i] == '2') {
            twos++;
        }
    }

    std::cout << fewestZeroes << std::endl;
    std::cout << fewestZeroesLayer << std::endl;
    std::cout << layers[fewestZeroesLayer].size() << std::endl;
    std::cout << ones * twos << std::endl;
}