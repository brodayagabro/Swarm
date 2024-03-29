#ifndef _TASK_H_
#define _TASK_H_

#include <algorithm>
#include <cstring>
#include <memory>
#include <utility>
#include <vector>
#include <stdexcept>
#include "exceptions.h"
#include "WorkingRobot.h"
#include "CommanderRobot.h"
#include "Swarm.h"


template<typename T>
class district{
    private:
        std::pair<T, T> X_limits;
        std::pair<T, T> Y_limits;

    public:
        district(T x_min, T x_max, T y_min, T y_max){
            if ((x_min == x_max) or (y_min == y_max)){
                throw std::range_error("Invalid range!");
            }
            
            if (x_min>x_max){
                T x = x_max; x_max=x_min; x_min = x;
            }
            if (y_min>y_max){
                T y = y_max; y_max = y_min; y_min = y;
            }
            this->X_limits = std::make_pair(x_min, x_max);
            this->Y_limits = std::make_pair(y_min, y_max);   
            };

        ~district(); 
        std::pair<T, T> get_X_lims()const{
            return this->X_limits;
        };
        
        std::pair<T, T> get_Y_lims()const{
            return this->Y_limits;
        };
        
        point* get_center()const{
            point* center = new point();
            T x_c = (X_limits.second + X_limits.first)/2;
            T y_c = (Y_limits.second + Y_limits.first)/2;
            center->x = x_c;
            center->y = y_c;
            return center;
        };
};
template<class T>
district<T>::~district(){};
typedef std::vector<struct point> POINTS;
typedef std::vector<float> ANGLES;
class Task{
    std::string task_name;
    int time; int curr_time;
    int count_of_robots;
    CommanderRobot* LiableCommander;
    std::vector<WorkingRobot*> robots;
    district <float>* feild;

    public:
        // Constructor
        Task(const std::string&,
                CommanderRobot*,
                district <float>*, int time,
                int count_of_robots,
                Swarm swarm);
        ~Task();
        // Methods to get status of private variables
        std::string get_name()const;
        int get_time()const;
        int get_countR()const;
        CommanderRobot* get_liable()const;
        district<float>* get_feild()const;
        // Method to get status of Robots in the task
        POINTS get_status()const; 
        ANGLES get_angles()const;
        void make_step();
        void run();


};


#endif
