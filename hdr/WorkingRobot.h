#ifndef _WORKINGROBOT_H
#define _WORKINGROBOT_H

#include "Robot.h"
#include "exceptions.h"

class CommanderRobot;

class WorkingRobot: public Robot {
    protected:
        CommanderRobot* commander;    
    public:
        WorkingRobot(double x, double y, double angle,const std::string &name,
                CommanderRobot* commander): Robot(x, y, angle, name),
                commander(commander){};
        // Конструктор копирования по указателю
        WorkingRobot& operator=(const WorkingRobot&)=default;
        virtual ~WorkingRobot(){};
        //void print() const;
        CommanderRobot* get_commander() const;
        CommanderRobot* change_commander(CommanderRobot* com);
};

#endif
