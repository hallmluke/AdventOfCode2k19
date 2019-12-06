#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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
        orbits++;
        currentOrbit = currentOrbit->getOrbit();
    }
    return orbits;
}


int main(){
    Planet a = Planet("a");
    Planet b = Planet("b", &a);
    Planet c = Planet("c", &b);

    std::cout << getOrbitCount(a) << std::endl;
    std::cout << getOrbitCount(b) << std::endl;
    std::cout << getOrbitCount(c) << std::endl;
}