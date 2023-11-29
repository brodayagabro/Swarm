# Swarm

Чтобы поднять проект у себя необходимо:

```bash
git clone https://github.com/brodayagabro/Swarm.git
```

Автоматически клонируется ветка master. Ветка develop на данный момент может немного отличаться. Но после master находится на конечной стадии после слияния.

## В проекте реализованы следующие классы:

Robot->WorkingRobot->CommanderRobot

Swarm

Task

Script


## Организация проекта:

./src -  файлы с определениями методов классов и тестов *.cpp

./gtestd - здесь определны файлы с тестами классов.

./obj - дирректория с объектными файлами.

./hdr -заголовочные файлы

./deps - файлы зависимостей

Конечный файл с тестами bin/ggtest*
## Сборка, запуск

### Сборки под Линукс

```bash
make all
```

### Запуск тестов

```bash
make test
```

### Запуск python интерфейса

```bash
make console
```

## Вопросы по проекту:
1) Как реализовать алгоритм поиска зацикливаний в Рое? По хорошему нужно рой представлять в виде графа зависимостей и в случае, если в графе возвникают циклы генерировать исключение. Но ни список ни бинарное дерево вроде бы так не умеют.
2) Рой ведь представляет из себя только контейнер, который умеет менять зависимости?
3) Как реализовать взаимодействие задпния с частью роя? Ведь командир должен брать по свое командование роботов рядом с область, а задание не знает о существовании роя получается?
