#ifndef _COMMANDER_
#define _COMMANDER_
#include "WorkingRobot.h"
#include "exceptions.h"
#include <vector>


class CommanderRobot: public WorkingRobot{
    private:
        std::vector<WorkingRobot*> depens;
    public:
        CommanderRobot(double, double, double,
                std::string, CommanderRobot*,
                const std::vector<WorkingRobot*>&);
        virtual ~CommanderRobot(){};
        CommanderRobot* change_commander(CommanderRobot*);
        void add_dep(WorkingRobot*);
        void erase_dep(WorkingRobot*);
        bool contains_dep(WorkingRobot*);
        void move_dep_to(double, double, WorkingRobot*);
        void rotate_dep(double dangle, WorkingRobot*);
        std::vector<WorkingRobot*> get_deps() const;
};

#endif
