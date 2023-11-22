#ifndef _SWARM_H_
#define _SWARM_H_

#include "WorkingRobot.h"
#include "CommanderRobot.h"
#include <memory>
#include <vector>


struct Tnode{
    WorkingRobot* node;
    std::vector<Tnode*> childs;
};



class Swarm{
    public:
        std::vector<WorkingRobot*> robots;
    public:
        Swarm(const std::vector<WorkingRobot*>);
        std::vector<WorkingRobot*> get_robots();
        void change_commander(WorkingRobot*, CommanderRobot*);
};




#endif
