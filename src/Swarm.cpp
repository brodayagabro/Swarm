#include "../hdr/Swarm.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "../hdr/Swarm.h"

#ifdef DEBUG
#define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif


#define DEBUG
// class describes dependence tree of the swarm
struct commanders{
    std::vector<CommanderRobot*> commanders;
};
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
    this->robots = robots;
    std::sort(this->robots.begin(), this->robots.end(), CmpByName); 
    this->curent_time = 0;
};

// Метод для получения Списка Роботов в Рое
std::vector<WorkingRobot*> Swarm::get_robots(){
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
        std::sort(this->robots.begin(), this->robots.end(), CmpByName);
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

// Метод изменения зависимостей роботов Роя

void Swarm::change_commander(WorkingRobot* WR, CommanderRobot* CR){
#ifdef DEBUG
    printf("start changing\n");
#endif
    if (!this->is_included(WR) or !this->is_included((WorkingRobot*)CR)){
        throw std::runtime_error("Unknown robots! Include these in swarm...");
    }
    // проверим не является ли этот робот уже подчиенным 
#ifdef DEBUG
    std::printf("CR and WR are in swarm\n");
#endif
    if ((WR->get_commander() != CR) and !(CR->contains_dep(WR))){
        // Построение "развертки графа" зависимостей и поиск циклов
    #ifdef DEBUG
        std::cout << "define pairs" << std::endl;
    #endif
        std::vector<std::pair<WorkingRobot*, CommanderRobot*>*> pairs{};
        //pairs.clear();
#ifdef DEBUG
        std::cout << "define p" << std::endl;
#endif
        std::pair<WorkingRobot*, CommanderRobot*>* p;
#ifdef DEBUG
printf("robots in swarm: \n");
        for (auto it = this->robots.begin(); it != this->robots.end(); ++it){
            std::cout << (*it)->get_name() << std::endl;
        }
        printf("declarate pairs\n");
#endif
        // Пары робот -> командир
        for (auto it = this->robots.begin(); it!=this->robots.end(); ++it){
            
            // Такое копирование вызывает разрыв связи между роботами и нельязя пользоваться методами get_commander и get_deps!!!
            auto R = new WorkingRobot(*(*it));
#ifdef DEBUG
            std::cout << R->get_name()<< "\n:: pointer of copy comander ::" << R->get_commander() << std::endl;
            std::cout<<":: pointer of origin comander::"<<(*it)->get_commander()<<std::endl;
#endif      
            CommanderRobot* C;
            if (R->get_commander() != nullptr){
                C = new CommanderRobot(*(*it)->get_commander());
            } else{
                C = nullptr;
            }
            p = new std::pair<WorkingRobot*, CommanderRobot*>(R, C);    
            pairs.push_back(p);
        }
#ifdef DEBUG
        std::cout << "pairs after initilazing:" << std::endl;
        for (auto it = pairs.begin(); it != pairs.end(); ++it){
            if ((*it)->second != nullptr){
                std::cout << (*it)->first->get_name() << ":";
                std::cout << (*it)->second->get_name() << std::endl;
            }else{    
                std::cout << (*it)->first->get_name() << ":nullptr" <<std::endl;
            }
        }
#endif
        // Робот : командиры
        // Лучше было использовать map наверное...
#ifdef DEBUG
    printf("Init dependences\n");
#endif
        std::vector<std::pair<WorkingRobot*, std::vector<CommanderRobot*>>*> dependences{};
        //dependences.clear();
        std::pair<WorkingRobot*, std::vector<CommanderRobot*>>* dep;
        // инициализация развертки графа зависимотей
#ifdef DEBUG
        std::cout << "Declarate dependences" <<std::endl;
#endif
        for (auto it = pairs.begin(); it != pairs.end(); ++it){
#ifdef DEBUG
            if ((*it)==nullptr){
                printf("%i nullptr", __LINE__);
            }
            printf("Start init R\n");
#endif
            auto R = (*it)->first;           
#ifdef DEBUG
            std::cout << R->get_name() << std::endl;
            if ((*it)->second == nullptr){
                printf("CommanderRobot is nullptr");
            }
            printf("Start init C\n");
    
#endif  
            CommanderRobot* C;
            if (*it == nullptr){
                C = nullptr;
            } else {
                C = (*it)->second;
            }
#ifdef DEBUG
            printf("Start create a new dep\n");
#endif
            //std::vector<CommanderRobot*> vc {C};
            dep = new std::pair<WorkingRobot*, std::vector<CommanderRobot*>>(R, {C});
#ifdef DEBUG
    printf("Succes of creation dep\n");
#endif
            dependences.push_back(dep);
#ifdef DEBUG
            printf("______________________");
            //std::cout << dep->first->get_name() << " : [ " << dep->second[0]->get_name() << " ]" << std::endl;
#endif
        }
#ifdef DEBUG        
        for (auto it = dependences.begin(); it != dependences.end(); ++it){
            auto dep = *it;
            std::cout << dep->first->get_name() << " : [ ";
            for (auto C = dep->second.begin(); C != dep->second.end(); ++C){
                if ((*C) != nullptr){
                    std::cout << (*C)->get_name() << " ";
                } else{ std::cout <<"nullptr"; }
            } 
            std::cout << "] " << std::endl;
        }
#endif
          
        bool changed_deps = true; 
        while (changed_deps){
            changed_deps = false;
            for (auto dep = dependences.begin(); dep != dependences.end(); ++dep){
                auto comanders = (*dep)->second;// список Комантиров для робота
#ifdef DEBUG
                printf("|len = %d |", (int)comanders.size());
#endif
                WorkingRobot* R;
                for (auto C = comanders.begin(); C != comanders.end(); ++ C){
                    if ((*C) != nullptr){
                    R = (WorkingRobot*)(*C);
                    } else{
                        continue;
                    }// Этого робота будем искать в списке зависимостей
#ifdef DEBUG
                    std::cout <<R->get_name();
#endif
                    // Поиск пары по ключу
                    auto pair = std::find_if(pairs.begin(), pairs.end(), [R](auto& el){ return *(el->first) == *R; });
                    // Если пара нашлась
                    if (pair != pairs.end()){
                    #ifdef DEBUG
                        printf(" <1> ");
                    #endif
                        // Проверим наличие командира в списке командиров для робота
                        auto comander = (*pair)->second;
                        //std::cout << comander->get_name();
                        auto it = std::find_if(comanders.begin(), comanders.end(), [comander](auto& el){ if (el == nullptr || comander == nullptr) return false; else return *(el) == *comander;});
                        if (it == comanders.end()){
                    #ifdef DEBUG 
                           printf(" <2> ");
                    #endif
                            // Если его там нет, то добавим его в список
                            (*dep)->second.push_back(comander);
                            changed_deps = true;
                        }    
                    }
                #ifdef DEBUG
                    std::cout << std::endl;
                #endif
                }
                //std::cout<< "Robot" << (*dep)->first->get_name()<<std::endl;
                comanders=(*dep)->second;
                auto Robot=(CommanderRobot*)((*dep)->first);
                auto is_in_comanders = std::find_if(comanders.begin(), comanders.end(), [Robot](auto& el){ if (el == nullptr) return false; else return *(el) == *Robot;});
                if (is_in_comanders != comanders.end()){
                    throw RecursiveException("Loop was find...");
                };    
            }
         #ifdef DEBUG
            std::cout << "Updated dependences" << std::endl; 
            for (auto it = dependences.begin(); it != dependences.end(); ++it){
                auto dep = *it;
                std::cout << dep->first->get_name() << " : [ ";
                for (auto C = dep->second.begin(); C != dep->second.end(); ++C){
                    if (*C != nullptr)
                    std::cout << (*C)->get_name() << " ";
                } 
                std::cout << "] " << std::endl;
            }
        #endif
            WR->change_commander(CR);
            CR->add_dep(WR);
            dependences.clear();
            pairs.clear();
        }
    } else {
        throw std::runtime_error("already in depends");
   }

}

