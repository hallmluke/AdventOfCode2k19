#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <array>
#include <map>

class Robot {
        public:
           Robot(int _facing = 90, std::array<int, 2> _position = {0, 0}) {
                facing = _facing;
                position = _position;
           }
           int facing;
           std::array<int, 2> position;
           std::map<std::array<int, 2>, int> paintedPanels;

           void MoveForward() {
                switch(facing) {
                   case 90:
                      position[1] += 1;
                      break;
                   case 0:
                      position[0] += 1;
                      break;
                   case 180:
                      position[0] -= 1;
                      break;
                   case 270:
                      position[1] -= 1;
                      break;
                   default:
                      std::cout << "Invalid direction to move forward: " << facing << std::endl;
                      throw;
                      break;
                }
           }
           void Rotate(int direction){
                   switch(direction) {
                     case 0:
                        facing = (facing + 90) % 360;
                        break;
                     case 1:
                        facing = facing - 90;
                        while(facing < 0) {
                                facing += 360;
                        }
                        facing = facing % 360;
                        break;
                     default:
                        std::cout << "Invalid direction to rotate: " << direction << std::endl;
                        throw;
                        break;
                   }
           }
           void PaintAndMove(int color, int direction){
                paintedPanels[position] = color;
                Robot::Rotate(direction);
                Robot::MoveForward();
           }
};

int main() {

        Robot paintingRobot = Robot();
        paintingRobot.PaintAndMove(1, 0);
        paintingRobot.PaintAndMove(0, 0);
        paintingRobot.PaintAndMove(1, 0);
        paintingRobot.PaintAndMove(1, 0);

        auto panels = paintingRobot.paintedPanels;
        for(auto it = panels.begin(); it != panels.end(); it++) {
                std::cout << "(" << it->first[0] << ", " << it->first[1] << "): " << it->second << std::endl;
        }
}
