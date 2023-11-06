#include "../hdr/WorkingRobot.h"
#include <cmath>
#include <malloc.h>
#include <stdexcept>

//void WorkingRobot::print() const {
//    std::cout << "**************" << std::endl;
//    std::cout << "x = " << this->x << std::endl;
//    std::cout << "y = " << this->y << std::endl;
//    std::cout << "angle = " << this->angle  << std::endl;
//    std::cout << "name = " << this->name << std::endl;
//    std::cout << "**************" << std::endl;
//};

CommanderRobot* WorkingRobot::change_commander(CommanderRobot* new_com){
    if ((WorkingRobot*) new_com != this){
        this->commander = new_com;
    } else {
        throw RecursiveException("Can't depends from this");
    }
    return new_com;
};
 
CommanderRobot* WorkingRobot::get_commander()const{
    return this->commander;
};

