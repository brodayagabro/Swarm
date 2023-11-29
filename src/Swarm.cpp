#include "../hdr/Swarm.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "../hdr/Swarm.h"


// параметр comparent для функции сортиовки 
bool CmpByName(WorkingRobot *R1, WorkingRobot *R2){
    return R1->get_name() < R2->get_name();
}

// Шаблон копирования вектора, не думаю, что он особо нужен
template<typename T>
std::vector<T> create_copy(std::vector<T> const &vec)
{
    std::vector<T> v(vec);
    return v;
}

// Конструктор Класса Рой 
Swarm::Swarm(const std::vector<WorkingRobot*> robots){
    this->robots = create_copy(robots);
    std::sort(this->robots.begin(), this->robots.end(), CmpByName); 
    this->curent_time = 0;
};

// Метод для получения Списка Роботов в Рое
std::vector<WorkingRobot*> Swarm::get_robots(){
    std::vector<WorkingRobot*> robots(this->robots);
    return robots;
}

// Проверка наличия Робота в рое
bool Swarm::is_included(WorkingRobot* R){ 
    auto it = std::find(this->robots.begin(), this->robots.end(), R);
    if (it == this->robots.end()){
        return false;
    }
    return true;
}

// добавление робота в рой
int Swarm::add_robot(WorkingRobot* R){
    if (!this->is_included(R)){
        this->robots.push_back(R);
        return 0; // succefully include
    }
    else{
        return 1; // already include
    }
}


// функция выключения робота из Роя
int Swarm::exclude_robot(WorkingRobot* R){
    if (this->is_included(R)){
        auto it = std::find(this->robots.begin(), this->robots.end(), R);
        this->robots.erase(it);
        delete R;
        return 0;  
    }
    return 1;
}

// получение текущего времени симуляции
int Swarm::get_time() const{
    return this->curent_time;
}

// Метод изменения зависимостей роботов Роя
void Swarm::change_commander(WorkingRobot* WR, CommanderRobot* CR){
    //if (!this->is_included(WR) or !this->is_included((WorkingRobot*)CR)){
    //    throw std::runtime_error("Unknown robots! Include these in swarm...");
    //}
    // проверим не является ли этот робот уже подчиенным 
    //std::printf("yes1\n");
    if ((WR->get_commander() != CR) and !(CR->contains_dep(WR))){
        //std::printf("yes2\n"); 
        // Проверка лежит ли по этому указателю Робот командующий
        // Проверим, является ли этот робот командующим низшего ранга
        CommanderRobot* CR_WR = dynamic_cast<CommanderRobot*>(WR);
        if (CR_WR != nullptr){
            //std::cout << "yes3" << std::endl;
            // Проверка есть ли Новый командующий в зависимостях у данного
            if (CR_WR->contains_dep((WorkingRobot*)CR)){
                //std::cout << "yes4" << std::endl;
                throw RecursiveException("New commander depends from this");
            } else {
                try{
                    // Если нет то сделаем замену командующего
                    CR_WR->change_commander(CR);
                    CR->add_dep(WR);
                } catch(const RecursiveException& e){
                    throw RecursiveException("Can't depend's from myself");
                }
            }
        }
        WR->change_commander(CR);
        CR->add_dep(WR);
   } else {
        throw std::runtime_error("already in depends");
   }

}

