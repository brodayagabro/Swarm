#ifndef _COMMANDER_
#define _COMMANDER_
#include "WorkingRobot.h"
#include "exceptions.h"
#include <vector>


class CommanderRobot: public WorkingRobot{
    private:
        std::vector<WorkingRobot*> depens;
    public:
        CommanderRobot(double x=0.0, double y=0.0, double angle = 0.0,
                std::string name="", CommanderRobot* commander=NULL,
                const std::vector<WorkingRobot*>& depens={}):
            WorkingRobot(x, y, angle, name, commander), depens(depens){};
        virtual ~CommanderRobot(){};
        //void set_depens(const std::set<WorkingRobot*> *depens);
        virtual CommanderRobot* change_commander(CommanderRobot*);
        void add_dep(WorkingRobot*);
        void erase_dep(WorkingRobot*);
        bool contains_dep(WorkingRobot*);
        void move_dep_to(double, double, WorkingRobot*);
        void rotate_dep(double dangle, WorkingRobot*);
        std::vector<WorkingRobot*> get_deps() const;
};

#endif
