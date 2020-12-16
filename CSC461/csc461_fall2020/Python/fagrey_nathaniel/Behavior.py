class Behavior:

    def __init__(self):
        self._speed = 30

    def travel(self):
        pass

    def calculate_updated_loc(self, speed_mph):
        speed_min = speed_mph / 60
        return speed_min / 2