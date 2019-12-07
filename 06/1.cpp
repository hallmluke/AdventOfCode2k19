#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using SolarSystem = std::unordered_map<std::string, std::vector<std::string>>;
class Planet {
    public:
    Planet(std::string _name) {
        name = _name;
        orbit = nullptr;
    }
    Planet(std::string _name, Planet *_orbit) {
        name = _name;
        orbit = _orbit;
    }
    std::string getName() {
        return name;
    }
    Planet *getOrbit() {
        return orbit;
    }
    void setOrbit(Planet *_orbit) {
        orbit = _orbit;
    }
    private:
    std::string name;
    Planet *orbit;
};

int getOrbitCount(Planet planet) {
    int orbits = 0;
    Planet *currentOrbit = planet.getOrbit();
    while(currentOrbit != nullptr) {
        std::cout << currentOrbit->getName() << " is orbiting " << std::endl;
        orbits++;
        currentOrbit = currentOrbit->getOrbit();
    }
    return orbits;
}

int findPlanet(std::vector<Planet> planets, std::string planetName){
        for(int i=0; i<planets.size(); i++){
                if(planets[i].getName() == planetName){
                        return i;
                }
        }
        return -1;
}

int depthFirstSearch(SolarSystem &s, std::string planet, int depth) {
        if (planet == "SAN" || planet=="YOU") {
                return depth;
        }
        auto edges = s.find(planet);
        if( edges == s.end()){
                return 0;
        }
        int initDepth = 0;
        for(auto nextPlanet : edges->second) {
                std::cout << nextPlanet << std::endl;
                int d1 = depthFirstSearch(s, nextPlanet, depth + 1);
                if(d1 != 0) {
                        if(initDepth != 0) {
                                return (initDepth - depth - 1) + (d1 - depth - 1);
                        }
                        initDepth = d1;
                }
        }
        return initDepth;
}

int main(){
    //Planet a = Planet("a");
    //Planet b = Planet("b");
    //Planet c = Planet("c", &b);

    //std::cout << getOrbitCount(a) << std::endl;
    //std::cout << getOrbitCount(b) << std::endl;
    //std::cout << getOrbitCount(c) << std::endl;

    std::ifstream file("input.txt");
    std::string str;
 //   std::vector<Planet> planets;
//    planets.reserve(1000);
    SolarSystem s;
    while(std::getline(file, str)) {
            std::stringstream lineStream(str);
            std::string name;
            std::getline(lineStream, name, ')');
            std::string planetName = name;
            
            std::getline(lineStream, name);
            std::string orbitingPlanetName = name;
            s[planetName].push_back(std::move(orbitingPlanetName));
    }
    for (auto i = s.begin(); i != s.end(); i++){
            std::cout << i->first << ": ";
            for(auto j : i->second){
                    std::cout << j << ", ";
            }
            std::cout << std::endl;
    }
    std::cout << "Finished parsing" << std::endl;
    int depth = depthFirstSearch(s, "COM", 0);
    std::cout << depth << std::endl;
 /*   std::cout << "PLANET NAME: " << planetName << std::endl;
    std::cout << "ORBITING PLANET NAME: " << orbitingPlanetName << std::endl;

    int planetLoc = findPlanet(planets, planetName);
    if(planetLoc == -1){
        planetLoc = planets.size();
        planets.push_back(Planet(planetName));
        std::cout << "create new planet " << planetName << std::endl;
    }

    int orbitingPlanetLoc = findPlanet(planets, orbitingPlanetName);
    if(orbitingPlanetLoc == -1) {
        orbitingPlanetLoc = planets.size();
        std::cout << "planets[planetLoc].getName() " << planets[planetLoc].getName() << std::endl;
        Planet *planetref = &planets[planetLoc];
        std::cout << planetref->getName() << std::endl;
        planets.push_back(Planet(orbitingPlanetName, planetref));
        std::cout << "After push back " << planetref->getName() << std::endl;
    } else {
        planets[orbitingPlanetLoc].setOrbit(&planets[planetLoc]);
    }
    std::cout << "Begin outputs" << std::endl;
    std::cout << planetLoc << " " << planets.size() << std::endl;
    std::cout << planets[planetLoc].getName() << std::endl;
    std::cout << getOrbitCount(planets[planetLoc]) << std::endl;
    std::cout << "Orbiting loc " << orbitingPlanetLoc << " Planets size " << planets.size() << std::endl;
    std::cout << planets[orbitingPlanetLoc].getName() << std::endl;
    std::cout << planets[orbitingPlanetLoc].getOrbit()->getName() << std::endl;
    std::cout << getOrbitCount(planets[orbitingPlanetLoc]) << std::endl;
    }
    
    int totalOrbits = 0;
    for(int i=0; i < planets.size(); i++) {
       totalOrbits += getOrbitCount(planets[i]);
       std::cout << planets[i].getName() << " " << getOrbitCount(planets[i]) << std::endl;
    }
    std::cout << totalOrbits << std::endl; */
}
