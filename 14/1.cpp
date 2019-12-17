#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <array>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>

class Reaction {
    public:
    Reaction(){};
    std::vector<std::string> materials;
    std::vector<int> materialQuantities;
    std::string chemical;
    int chemicalQuantity;
    void print() {
        for(int i=0; i<materials.size(); i++) {
                std::cout << materialQuantities[i] << " " << materials[i] << ", ";
        }
        std::cout << "=> " << chemicalQuantity << " " << chemical << std::endl;
    }
};

void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !std::isspace(ch);
        }));
}
void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
        }).base(), s.end());
}
void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
}


void parseInput(std::map<std::string, Reaction>& reactions){
    std::ifstream file("input.txt");
    std::string str;
    while (std::getline(file, str))
    {
        Reaction reaction = Reaction();
        std::stringstream lineStream(str);
        std::string materials;
        std::getline(lineStream, materials, '=');

        std::stringstream materialsStream(materials);
        std::string material;
        while(std::getline(materialsStream, material, ',')){
                if(material[0] == ' ') {
                        material = material.substr(1);
                }
                std::stringstream quantStream(material);
                std::string quant;
                std::getline(quantStream, quant, ' ');
                std::string mat;
                std::getline(quantStream, mat);
                std::cout << "Quantity: " << quant << std::endl;
                std::cout << "Material: " << mat << std::endl;
                trim(mat);
                reaction.materials.push_back(mat);
                reaction.materialQuantities.push_back(std::stoi(quant));
        }

        std::string output;
        std::getline(lineStream, output);
        output = output.substr(2);
        std::stringstream quantStream(output);
        std::string quant;
        std::getline(quantStream, quant, ' ');
        std::string mat;
        std::getline(quantStream, mat);
        std::cout << "Output Quantity: " << quant << std::endl;
        std::cout << "Output Material: " << mat << std::endl;
        trim(mat);
        reaction.chemical = mat;
        reaction.chemicalQuantity = std::stoi(quant);
        reactions[mat] = reaction;
       }

}

int getOreCount(std::map<std::string, Reaction> reactions, std::string chemical, int quantity, std::map<std::string, int>& stockpile) {
        std::string ore = "ORE";

        auto pileItr = stockpile.find(chemical);
        int stockpiledChem = 0;
        if(pileItr != stockpile.end()) {
                stockpiledChem = pileItr->second;
        } else {
                stockpile[chemical] = 0;
        }


        //std::cout << reactions[chemical].materials[0] << std::endl;
        Reaction scaledReaction = reactions[chemical];
                while(quantity > scaledReaction.chemicalQuantity + stockpiledChem) {
                     scaledReaction.chemicalQuantity += reactions[chemical].chemicalQuantity;
                     for(int i=0; i<scaledReaction.materials.size(); i++) {
                        scaledReaction.materialQuantities[i] += reactions[chemical].materialQuantities[i];
                     }
                }
                std::cout << "Scaled Reaction: ";
                scaledReaction.print();
                stockpile[chemical] = scaledReaction.chemicalQuantity + stockpile[chemical] - quantity;
                std::cout << "Stockpile of " << chemical << ": " << stockpile[chemical] << std::endl;

        if(reactions[chemical].materials[0] == ore) {
          //      std::cout << "Found ore" << std::endl;
                                
                return scaledReaction.materialQuantities[0];
        } else {
                int count = 0;
                for(int i=0; i<scaledReaction.materials.size(); i++) {
                        if(scaledReaction.materialQuantities[i] > stockpile[scaledReaction.materials[i]] ) {
                                count += getOreCount(reactions, scaledReaction.materials[i], scaledReaction.materialQuantities[i], stockpile);
                        } else {
                                stockpile[scaledReaction.materials[i]] = stockpile[scaledReaction.materials[i]] - scaledReaction.materialQuantities[i];
                        }
                }
                return count;
        }
}

int main() {
        std::map<std::string, Reaction> reactions;
        std::map<std::string, int> stockpile;
        parseInput(reactions);
        reactions["FUEL"].print();
        int oreCount = getOreCount(reactions, "FUEL", 1, stockpile);
        std::cout << oreCount << std::endl;
}

