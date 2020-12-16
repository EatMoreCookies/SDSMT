from fagrey_nathaniel.Behavior import Behavior

class Car:
    def __init__(self, car_id, behavior):
        self.__behavior = behavior
        self.__id = car_id
        self.__location = 0.00

    def update(self, car_count):
        # GRADING: USE_BEHAVIOR
        self.__location += self.__behavior.travel(car_count)
        return self.__location

    def reset_location(self):
        self.__location = 0.00

    def get_id(self):
        return self.__id

    # GRADING: SET_BEHAVIOR
    def set_behavior(self, behavior):
        self.__behavior = behavior

    def __str__(self):
        return str(self.__id) + ": " + "{:.2f}".format(self.__location)