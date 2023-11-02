#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#include <cstring>
#include <exception>
// тут описаны исключения, генерируемые в методах WorkingRobot и CommanderRobot
// Полагаю их надо реализовать как классы уеаследованные от std::runtime_exception
class RecursiveException: public std::exception {
};
class NotFountException: public std::exception{
};

#endif
