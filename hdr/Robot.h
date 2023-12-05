#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

typedef struct point{
    double x; double y;
}point;

class Robot{
    /*
    Рабочий робот:
     объект содержит
      строковое название,
      текущие координаты (2 дробных числа, м),
      ориентацию (угол относительно оси 0X),
      указатель на командующего (может быть нулевым).
     Должен уметь регистрировать свои поступательные движения и повороты.

     ???Что значит регистрировать движения и повороты? Запоминать?
    */

    protected:
        std::string name; // robot's name
        double x; double y; // robots position
        double angle; // angle between robot's diriction and OX axes
       // CommanderRobot *commander;
    public:
        // Constructor
        Robot(double x=0, double y=0, double angle=0, const std::string& name="");
        virtual ~Robot(){};
        // get info from private variables
        point* get_position() const;
        double get_angle() const;
        double get_x() const;
        double get_y() const;
        std::string get_name() const;
        void print() const;

        // change robots position (x0, y0) -> (x0+dx, y0+dy)
        bool move_to(double dx, double dy);
        // change robot's diriction angle0 -> angle0 + angle
        bool rotate(double angle);
        // comparing robot names
        bool operator< (Robot);
        bool operator> (Robot);
        bool operator== (Robot);
        bool operator>= (Robot);
        bool operator<= (Robot);
};

#endif 
