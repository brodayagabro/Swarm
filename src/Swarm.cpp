#include "../hdr/Swarm.h"
#include <algorithm>
#include <utility>
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
// параметр comparent для функции сортиовки 
bool CmpByName(WorkingRobot *R1, WorkingRobot *R2){
    return R1->get_name() < R2->get_name();
}

// Конструктор Класса Рой 
Swarm::Swarm(const std::vector<WorkingRobot*> robots){
    this->robots = robots;
    std::sort(this->robots.begin(), this->robots.end(), CmpByName); 
    this->curent_time = 0;
};
Swarm::~Swarm(){};

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
typedef std::pair<WorkingRobot*, CommanderRobot*> CRWR;
typedef std::vector<CRWR> PAIRS;
#ifdef DEBUG
void print_pairs(const PAIRS &VR){
    for (auto it = VR.begin(); it != VR.end(); ++it){
        if ((*it).second != nullptr){
            std::cout << (*it).first->get_name() << ":";
            std::cout << (*it).second->get_name() << std::endl;
        }else{    
            std::cout << (*it).first->get_name()
                << ":nullptr" <<std::endl;
        }
    }
}

template<class T>
void print_robots(const std::vector<T*> &ROBOTS){
    std::cout << " [ ";
    for (auto it = ROBOTS.begin(); it != ROBOTS.end(); ++it){
        if ((*it) != nullptr){
           std::cout << (*it)->get_name() << " ";
        }
        else{
            std::cout << "nullptr" << " ";
        }
    }
    std::cout<<"] "<<std::endl;
}
#endif

PAIRS create_pairs(const std::vector<WorkingRobot*> &ROBOTS){
#ifdef DEBUG
    print_robots(ROBOTS);
#endif
    PAIRS VR{};
    CRWR p;
    DEBUG_PRINT("define pairs\n");
    for (auto it = ROBOTS.begin(); it!=ROBOTS.end(); ++it){ 
    // Такое копирование вызывает разрыв связи между роботами
    //  и нельязя пользоваться методами get_commander и get_deps!!!
        auto R = new WorkingRobot(*(*it));
        CommanderRobot* C;
        if (R->get_commander() != nullptr){
            C = new CommanderRobot(*(*it)->get_commander());
        } else{
            continue;
            //C = nullptr;
        }
        p = std::make_pair(R, C);    
        VR.push_back(p);
    }

#ifdef DEBUG
    fprintf(stderr, "pairs after initilazing:\n");
    print_pairs(VR);
#endif
    return VR;
};

typedef std::pair<WorkingRobot*, std::vector<CommanderRobot*>> ALL_COMS;
typedef std::vector<ALL_COMS> DEPENDENCES;
#ifdef DEBUG
void print_dependences(const DEPENDENCES &dependences){
    for (auto it = dependences.begin(); it != dependences.end(); ++it){
        auto dep = *it;
        std::cout << dep.first->get_name() << " : [ ";
        for (auto C = dep.second.begin(); C != dep.second.end(); ++C){
            if ((*C) != nullptr)
                std::cout << (*C)->get_name() << " ";
            else
                std::cout <<"nullptr";
        } 
        std::cout << "] " << std::endl;
    }
}
#endif
DEPENDENCES create_dependences(PAIRS pairs){
    DEPENDENCES dependences {};
    //dependences.clear();
    std::pair<WorkingRobot*, std::vector<CommanderRobot*>> dep;
    // инициализация развертки графа зависимотей
    DEBUG_PRINT("Declarate dependences\n");
    for (auto it = pairs.begin(); it != pairs.end(); ++it){
        DEBUG_PRINT("Start init R\n");
        auto R = (*it).first;           
#ifdef DEBUG
        std::cout << R->get_name() << std::endl;
        if ((*it).second == nullptr){
            printf("CommanderRobot is nullptr");
        }
        printf("Start init C\n");
#endif          
        CommanderRobot* C;
        C = (*it).second;
        DEBUG_PRINT("Start create a new dep\n");
        std::vector<CommanderRobot*> vc {C};
        dep = std::make_pair(R, vc);
        DEBUG_PRINT("Succes of creation dep\n");
        dependences.push_back(dep);
        DEBUG_PRINT("______________________\n");
    }
#ifdef DEBUG        
        print_dependences(dependences);
#endif
    return dependences;    
}

bool Update_dependences(ALL_COMS &dep, const PAIRS &pairs){
    bool was_updated = false;
    auto comanders = dep.second;// список Комантиров для робота
    DEBUG_PRINT("|len = %d |", (int)dep.second.size());
    WorkingRobot* R;
    for (auto C = comanders.begin(); C != comanders.end(); ++ C){
        if ((*C) != nullptr){
            R = (WorkingRobot*)(*C);
        } else{
            continue;
        }// Этого робота будем искать в списке зависимостей
        // Поиск пары по ключу
        auto pair = std::find_if(pairs.begin(), pairs.end(), 
                [R](auto& el){if ((el.first) == nullptr) return false; 
                              else return *(el.first) == *R; });
        // Если пара нашлась
        if (pair != pairs.end()){        
            DEBUG_PRINT("[ Pair was found ]");
            // Проверим наличие командира в списке командиров для робота
            auto comander = (*pair).second;
            //std::cout << comander->get_name();
            auto it = std::find_if(comanders.begin(), comanders.end(),
                    [comander](auto& el){
                    if (el == nullptr || comander == nullptr)
                        return false;
                    else
                        return *(el) == *comander;
                     });
            if (it == comanders.end() && (comander != nullptr)){
               DEBUG_PRINT("[ comander was found ]");
                // Если его там нет, то добавим его в список
                dep.second.push_back(comander);
                was_updated = true;
            }    
        }
        DEBUG_PRINT("\n");
    }
   return was_updated;
}

void Swarm::change_commander(WorkingRobot* WR, CommanderRobot* CR){
    DEBUG_PRINT("start changing\n");
    if (!this->is_included(WR) ||
            !this->is_included((WorkingRobot*)CR)){
        throw std::runtime_error
            ("Unknown robots! Include these in swarm...");
    }else {DEBUG_PRINT("CR and WR are in swarm\n");}
    // проверим не является ли этот робот уже подчиенным 
   
    if ((WR->get_commander() != CR) && !(CR->contains_dep(WR))){
        // Построение "развертки графа" зависимостей и поиск циклов
        auto old_comander = WR->get_commander();
        WR->change_commander(CR);
        CR->add_dep(WR);
        DEBUG_PRINT("define pairs\n");
        std::vector<std::pair<WorkingRobot*, CommanderRobot*>>
            pairs(create_pairs(robots));
// ---------------------------------------------------------------------
        // Робот : командиры
        // Лучше было использовать map наверное...
        DEBUG_PRINT("Init dependences\n");
        DEPENDENCES dependences(create_dependences(pairs));
          
        bool changed_deps = true; 
        while (changed_deps){
            changed_deps = false;
            for (auto dep = dependences.begin(); dep != dependences.end(); ++dep){
                DEBUG_PRINT("COME IN LOOP\n");
                changed_deps = Update_dependences((*dep), pairs);
                DEBUG_PRINT("DEPENDENCES was changed = %d\n", (int)changed_deps);
                auto comanders=(*dep).second;
#ifdef DEBUG
                print_robots(comanders);
#endif
                auto Robot=(CommanderRobot*)((*dep).first);
                auto is_in_comanders = std::find_if(comanders.begin(),
                        comanders.end(),
                        [Robot](auto& el){
                            if (el == nullptr)
                                return false;
                            else    
                                return *(el) == *Robot;});

                if (is_in_comanders != comanders.end()){
                    WR->change_commander(old_comander);
                    CR->erase_dep(WR);
                    DEBUG_PRINT("---->LOOP IN TREE<----\n");
                    throw RecursiveException("Loop was find...");
                };    
            }
#ifdef DEBUG
            std::cout << "Last Updated dependences" << std::endl; 
            print_pairs(pairs);
            DEBUG_PRINT("*************************\n");
            print_dependences(dependences);
#endif
        }
        dependences.clear();
        pairs.clear();
        DEBUG_PRINT("Succesfelly changed...\n");
    } else 
        throw std::runtime_error("already in depends");

}

