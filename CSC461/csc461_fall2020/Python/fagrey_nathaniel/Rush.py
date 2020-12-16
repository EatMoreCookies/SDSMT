from fagrey_nathaniel.Behavior import Behavior

class Rush(Behavior):

    def __init__(self):
        Behavior.__init__(self)

    # GRADING: RUSH
    def travel(self, car_count):
        return self.calculate_updated_loc(self._speed)

