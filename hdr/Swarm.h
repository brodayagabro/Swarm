#ifndef _SWARM_H_
#define _SWARM_H_

#include "WorkingRobot.h"
#include "CommanderRobot.h"
#include <memory>
#include <vector>



class Swarm{
    private:
        std::vector<WorkingRobot*> robots;
        int curent_time;
    public:
        Swarm(const std::vector<WorkingRobot*>);
        std::vector<WorkingRobot*> get_robots();
        void change_commander(WorkingRobot*, CommanderRobot*);
        bool is_included(WorkingRobot*);
        int add_robot(WorkingRobot*);
        int exclude_robot(WorkingRobot*);
        int get_time()const;
};




#endif
