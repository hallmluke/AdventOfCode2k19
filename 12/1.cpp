#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <bits/stdc++.h>
#include <functional>
#include <map>


class Moon {
    public:
      Moon(std::array<int, 3> _position = {0, 0, 0}, std::array<int, 3> _velocity = {0, 0, 0}) : position(_position), velocity(_velocity) {};
      std::array<int, 3> position;
      std::array<int, 3> velocity;
      void ApplyGravity(Moon& oppositeMoon) {
         for(int i=0; i<position.size(); i++) {
                if(position[i] > oppositeMoon.position[i]) {
                        velocity[i]--;
                        oppositeMoon.velocity[i]++;
                } else if(position[i] < oppositeMoon.position[i]) {
                        velocity[i]++;
                        oppositeMoon.velocity[i]--;
                }
         }
      }
      void ApplyVelocity() {
        for(int i=0; i<position.size(); i++) {
                position[i] += velocity[i];
        }
      }
      void Print() {
        std::cout << "pos=<x=" << position[0] << ", y=" << position[1] << ", z=" << position[2] << ">, vel=<x=" << velocity[0] << ", y=" << velocity[1] << ", z=" << velocity[2] << ">" << std::endl;
      }
      int getPotentialEnergy(){
        return std::abs(position[0])+std::abs(position[1])+std::abs(position[2]);
      }
      int getKineticEnergy() {
        return std::abs(velocity[0])+std::abs(velocity[1])+std::abs(velocity[2]);
      }
      int getTotalEnergy() {
        return Moon::getPotentialEnergy() * Moon::getKineticEnergy();
      }
};

void TimeStep(int steps, std::vector<Moon>& moons){
    for(int step=0; step<steps; step++){
        //std::cout << "After " << step+1 << " step(s):" << std::endl;
        for(int i=0; i<moons.size(); i++) {
                for(int j=i+1; j<moons.size(); j++){
                        moons[i].ApplyGravity(moons[j]);
                }
                moons[i].ApplyVelocity();
          //      moons[i].Print();
        }
        //std::cout << std::endl;
    }
}

bool checkPeriod(int axis, std::vector<Moon> initial, std::vector<Moon> current) {
        //for(int axis = 0; axis<3; axis++) {
        //bool samePositionAsInitial = true;
        for(int i=0; i<initial.size(); i++) {
                if((initial[i].position[axis] != current[i].position[axis]) || current[i].velocity[axis] != 0){
                        return false;
                }
        }

        return true;
        //}
}

int main() {
/*
        Moon moon1 = Moon({-1, 0, 2});
        Moon moon2 = Moon({2, -10, -7});
        Moon moon3 = Moon({4, -8, 8});
        Moon moon4 = Moon({3, 5, -1});
*/
        Moon moon1 = Moon({14, 9, 14});
        Moon moon2 = Moon({9, 11, 6});
        Moon moon3 = Moon({-6, 14, -4});
        Moon moon4 = Moon({4, -4, -3});

        std::vector<Moon> moons;
        moons.push_back(moon1);
        moons.push_back(moon2);
        moons.push_back(moon3);
        moons.push_back(moon4);
        std::vector<Moon> initial = moons;
        std::vector<int> periods = {0, 0, 0};
        int stepsTaken = 0;
        while(periods[0] == 0 || periods[1] == 0 || periods[2] == 0) {
                TimeStep(1, moons);
                stepsTaken++;
                for(int axis=0; axis<periods.size(); axis++){
                        if(periods[axis] == 0) {
                                if(checkPeriod(axis, initial, moons)) {
                                        periods[axis] = stepsTaken;
                                        std::cout << axis << std::endl;
                                        std::cout << stepsTaken << std::endl;
                                        moons[0].Print();
                                        moons[1].Print();
                                        moons[2].Print();
                                        moons[3].Print();
                                }
                        }
                }
        }
        //TimeStep(10000000, moons);
        int totalEnergy = 0;
        for(int i=0; i<moons.size(); i++){
                totalEnergy += moons[i].getTotalEnergy();
        }

        std::cout << totalEnergy << std::endl;
        std::cout << periods[0] << ", " << periods[1] << ", " << periods[2] << std::endl;
       }
