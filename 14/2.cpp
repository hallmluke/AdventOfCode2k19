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
    std::vector<long long> materialQuantities;
    std::string chemical;
    long long chemicalQuantity;
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
                reaction.materialQuantities.push_back(std::stoll(quant));
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
        reaction.chemicalQuantity = std::stoll(quant);
        reactions[mat] = reaction;
       }

}

long long getOreCount(std::map<std::string, Reaction> reactions, std::string chemical, long long quantity, std::map<std::string, long long>& stockpile) {
        std::string ore = "ORE";

        auto pileItr = stockpile.find(chemical);
        long long stockpiledChem = 0;
        if(pileItr != stockpile.end()) {
                stockpiledChem = pileItr->second;
        } else {
                stockpile[chemical] = 0;
        }


        //std::cout << reactions[chemical].materials[0] << std::endl;
        Reaction scaledReaction = reactions[chemical];
                while(quantity > scaledReaction.chemicalQuantity + stockpiledChem) {
                     long long ratio = std::ceil(((long double) (quantity - stockpiledChem) / ((long double) scaledReaction.chemicalQuantity)));
                     if (ratio < 1) {
                        scaledReaction.print();
                        std::cout << "Ratio: " << ratio << std::endl;
                        std::cout << "Quanity: " << quantity << std::endl;
                        std::cout << "Stockpiled chem: " << stockpiledChem << std::endl;
                        throw;
                     }
                     std::cout << "Ratio: " << ratio << std::endl;
                     scaledReaction.chemicalQuantity = ratio * reactions[chemical].chemicalQuantity;
                     //std::cout << scaledReaction.chemicalQuantity << std::endl;
                     for(int i=0; i<scaledReaction.materials.size(); i++) {
                        scaledReaction.materialQuantities[i] = ratio * reactions[chemical].materialQuantities[i];
                     }
                     scaledReaction.print();
                }
                //std::cout << "Scaled Reaction: ";
                //scaledReaction.print();
                stockpile[chemical] = scaledReaction.chemicalQuantity + stockpile[chemical] - quantity;
                if(stockpile[chemical] < 0) {
                        scaledReaction.print();
                        std::cout << "Quantity: " << quantity << std::endl;
                        std::cout << "Chemical: " << chemical << std::endl;
                        throw;
                }
                std::cout << "Stockpile of " << chemical << ": " << stockpile[chemical] << std::endl;

        if(reactions[chemical].materials[0] == ore) {
          //      std::cout << "Found ore" << std::endl;
                                
                return scaledReaction.materialQuantities[0];
        } else {
                long long count = 0;
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
        std::map<std::string, long long> stockpile;
        parseInput(reactions);
        reactions["FUEL"].print();
        long long oreCount = getOreCount(reactions, "FUEL", 1, stockpile);
        long long target = 1000000000000;
        std::cout << oreCount << std::endl;
        std::cout << target / oreCount << std::endl;
        long long low = target / oreCount;
        long long high = low * 2;
        while(low + 1 < high) {
                std::map<std::string, long long> testpile;
                long long mid = (low + high)/2;
                oreCount = getOreCount(reactions, "FUEL", mid, testpile);
                if(oreCount > target) {
                        high = mid;
                } else if(oreCount < target) {
                        low = mid;
                } else {
                        std::cout << "Exactly ore count" << std::endl;
                }
                std::cout << oreCount << std::endl;
                std::cout << mid << std::endl;
                //std::cout << getOreCount(reactions, "FUEL", high, testpile) << std::endl;
        }
        std::map<std::string, int> testpile;
        //std::cout << getOreCount(reactions, "FUEL", 1, testpile) << std::endl;
        std::cout << low << " " << high << std::endl;
}

