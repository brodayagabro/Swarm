from WorkingRobot import WorkingRobot

class CommanderRobot(WorkingRobot):
    depens = []

    def __init__(self, x=0, y=0, angle=0, name="", commander=None, depens=[]):
        super().__init__(x, y, angle, name, commander)
        self.depens = depens
        
    # проверка подчиненности робота
    def is_depend(self, R):
        if R in self.depens:
            return 1
        return 0

    def add_dep(self, R):
        self.depens.append(R)

    def move_dep_to(self, dx, dy, R):
        if R in self.depens:
            R.move_to(dx, dy)

    def rotate_dep(self, da, R):
        if R in self.depens:
            R.rotate(da)
