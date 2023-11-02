#ifndef _SWARM_H_
#define _SWARM_H_

#include "WorkingRobot.h"
#include "CommanderRobot.h"
#include <vector>
class Swarm{
    private:
        std::vector<WorkingRobot*> robots;
    public:
        Swarm(){};
};




#endif
