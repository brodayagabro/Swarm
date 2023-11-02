from Robot import Robot
from WorkingRobot import WorkingRobot
from ComanderRobot import CommanderRobot

CW = CommanderRobot(1, 2, 3, "B", None, []) 
WR = WorkingRobot(1, 2, 3, "A", CW)

def menu():
    print("Chose the action:")
    print("1) Create WorkingRobot")
    command = input()

if __name__ == "__main__":  
    while (1):
        menu()
