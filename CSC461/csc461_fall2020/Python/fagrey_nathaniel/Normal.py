from fagrey_nathaniel.Behavior import Behavior

class Normal( Behavior ):
    def __init__(self):
        Behavior.__init__(self)

    # GRADING: NORM
    def travel(self, car_count):
        location: float
        if car_count > 2:
            location = self.calculate_updated_loc(self._speed - 10)
        else:
            location = self.calculate_updated_loc(self._speed)
        return location



