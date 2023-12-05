#include "../hdr/CommanderRobot.h"
#include <exception>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>

// Нужно ли проверять наличие в списке, пообще этой при необходимости делается методом класса вектор
// Есть предложение проверять наличие Робота в списке подчинений и потом добавлять если его там нет
// Как будто это выгоднее по ресурсам чем написанное ниже
template <typename T>
int cpy(std::vector<T>*V1, const std::vector<T>& V2){
    std::copy(V2.begin(), V2.end(), back_inserter(*V1));
    return 0;
}

CommanderRobot::CommanderRobot(double x, double y, double angle,
        const std::string &name, CommanderRobot* commander,
        const std::vector<WorkingRobot*>& depens={}):
    WorkingRobot(x, y, angle, name, commander){
    cpy(&this->depens, depens);
    };

void CommanderRobot::add_dep(WorkingRobot *new_WR){
    this->depens.push_back(new_WR);
    std::vector<WorkingRobot*>::iterator ip;
    ip = std::unique(this->depens.begin(), this->depens.end());
    this->depens.resize(std::distance(this->depens.begin(), ip));
    new_WR->change_commander(this);
}

template <typename T>
int find_elem(typename std::vector<T>V,T elem){
    int it;
    for (it = 0; it != (int)V.size()-1; it++){
        if (V[it] == elem){
            return it;
        }
    }
return 0;
}
// удаление робота из подчиненности
void CommanderRobot::erase_dep(WorkingRobot* WR){
    if (this->contains_dep(WR)){
        int it = find_elem<WorkingRobot*>(this->depens, WR);
        this->depens.erase(this->depens.begin() + it);  
    }  
}
// проверка на подчиненность робота данному командующему
bool CommanderRobot::contains_dep(WorkingRobot* WR){
    auto it = std::find(this->depens.begin(), this->depens.end(), WR);
    if (it == this->depens.end()){
        return false;
    }
    return true;
}
// перемещение зависимого робота 
void CommanderRobot::move_dep_to(double dx, double dy, WorkingRobot* WR){
    if (this->contains_dep(WR)){
        WR->move_to(dx, dy);
    } else {
        throw NotFountException("");
    };
}
// вращение зависимого робота
void CommanderRobot::rotate_dep(double dangle, WorkingRobot* WR){
    if (this->contains_dep(WR)){
        WR->rotate(dangle);
    } else {
        throw NotFountException();
    }
}

// Вывод вектора с указателями на подчиненных роботов
std::vector<WorkingRobot*> CommanderRobot::get_deps() const{
    return this->depens;
}
