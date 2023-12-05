#include "../hdr/Task.h"
#include <string>
#include <stdexcept>
#include <exception>
#include "../hdr/exceptions.h"
Task::Task(const std::string &name, CommanderRobot* LiableCommander, district<float>* feild, int time, int count_of_robots){
    if (name==""){
       throw  std::range_error("Name can't be null len!");
    }
    this->task_name = name;
    
    if (LiableCommander==nullptr){
        throw std::runtime_error("There must be Liable commander!");
    };
    this->LiableCommander = LiableCommander;
    
    if (time <= 0){
        throw std::range_error("Uncorreted format of time! must be time>0");
    }
    this->time = time;
    
    if (count_of_robots <= 0){
        throw std::range_error("Uncorrect format of countR... countR >= 0!!!");
    }
    this->count_of_robots = count_of_robots;
   
    if (feild == nullptr){
        throw std::runtime_error("Incorrect feild");
    }
    this->feild = feild;

    this->curr_time = 0;
};

Task::~Task(){
}
std::string Task::get_name()const{
    return this->task_name;
}

int Task::get_time()const{
    return this->time;
}

int Task::get_countR()const{
    return this->count_of_robots;
}

district<float>* Task::get_feild()const{
    return this->feild;
}
