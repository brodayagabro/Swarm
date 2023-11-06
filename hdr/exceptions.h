#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#include <cstring>
#include <exception>
#include <limits>
#include <stdexcept>
// тут описаны исключения, генерируемые в методах WorkingRobot и CommanderRobot
// Полагаю их надо реализовать как классы уеаследованные от std::runtime_exception
class RecursiveException: public std::runtime_error{
    public:
        RecursiveException (const std::string& what="")
       : std::runtime_error(what){}; 

};
struct NotFountException: public std::runtime_error{
    public:
        NotFountException (const std::string& what="")
       : std::runtime_error(what){}; 
};

#endif
