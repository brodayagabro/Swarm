from Robot import Robot

class WorkingRobot(Robot):
    def __init__(self, x, y, angle, name, commander):
        super().__init__(x, y, angle, name)
        self.commander = commander

    def change_com(self, new_com):
        print(f"changing commander from{self.commander} to {com}")
