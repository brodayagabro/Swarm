#include <malloc.h>
#include <stdexcept>
#include "../hdr/Robot.h"
//  в этом файле генерируются исключения из стандартной библиотеки
Robot::Robot(double x, double y, double angle, std::string name)
{// тут нужно прописать ошибки
    if (x >=0 && y>= 0 && angle >=0 && angle <= 90){
        this->x = x;
        this->y = y;
        this->angle = angle;  
    } else {
        throw std::range_error("Unexpectable format of x, y");
    }

    if (!name.empty()) {
       this->name = name; 
    } else {
        throw std::length_error("Parametr name can't be empty");
    }
} 


point* Robot::get_position() const{
    //std::cout<<"x = "<<this->x<<std::endl;
    //std::cout<<"y = "<<this->y<<std::endl;
    point *pos = (point*)malloc(sizeof(point));
    if ((x >= 0) || (y >= 0)){
        pos->x = this->x;
        pos->y = this->y;
        return pos;
    } else {
        throw std::range_error("Unexpectable format of x, y");
        return NULL;
    }
};

double Robot::get_x() const{
    return this->x;
};

double Robot::get_y() const{
    return this->y;
};

double Robot::get_angle() const{
    return this->angle;
};

std::string Robot::get_name() const{
    return this->name;
};

void Robot::print() const{
    std::cout <<"[ "<< this->name << " : ] | [ x = " << this->x 
        << " ] | [ y = " << this->y << " ] | [ angle = " << this ->angle <<" ]" << std::endl;
};

bool Robot::move_to(double dx, double dy){
    if ((this->x+dx)>=0 && (this->y+dy)>=0){
        this->x += dx;
        this->y += dy;
        return true;
    } else{
        throw std::range_error("Unexpected dx, dy");
        return false;
    }
};

bool Robot::rotate(double dangle){
    if ((angle+dangle)>=0){
        this->angle = fmod((this->angle + dangle), 360.0);  
        return true;
    } else{
        throw std::range_error("Unexpected angle");
        return false;
    }
};

bool Robot::operator< (Robot R){
    return (this->name < R.name);
}

bool Robot::operator<= (Robot R){
    return (this->name <= R.name);
}

bool Robot::operator== (Robot R){
    return (this->name == R.name);
}

bool Robot::operator>= (Robot R){
    return (this->name >= R.name);
}

bool Robot::operator> (Robot R){
    return (this->name > R.name);
}




/*
int test_WorkingRobot(){
    WorkingRobot WR1(1.0, 3.0, 45.0);
    point *pos1 = WR1.get_position(); 
    //printf("x=%f\ny=%f", pos1.x, pos1.y);
    WR1.move_to(2.0, 3.0);
    WR1.get_position();
    WR1.get_angle();
    WR1.get_x();
    WR1.get_y();
    WR1.rotate(20.0);
    WR1.get_angle();
    return 0;
}*/

/*
int main(){
    std::cout << "hello, world!\n";
    WorkingRobot robot1(1, 3, 5, "robot1");
    robot1.get_position();
    robot1.get_name();
    //test_WorkingRobot();
    return 0;
}
*/
