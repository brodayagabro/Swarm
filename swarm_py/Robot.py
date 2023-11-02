class Robot:
    x = 0.0
    y = 0.0
    angle = 0.0
    name = ""

    def __init__(self, x, y, angle, name):
        self.x = x; self.y = y;
        self.angle = angle
        self.name = name
    # тут еще нужны проверки на корректность аргументов
    def move_to(self, dx, dy):
        self.x += dx; self.y += dy

    def rotate(self, da):
        self.angle += da

    
