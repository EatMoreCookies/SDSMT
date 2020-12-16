from fagrey_nathaniel.Behavior import Behavior
from fagrey_nathaniel.Car import Car
from fagrey_nathaniel.Track import Track

class Station:

    def __init__(self, name, line):
        self._name = name
        self._cars = []
        self.__next_track = None
        self._line = line

    def create_car(self, car_id: int, behavior: Behavior):
        self._cars.append(Car(car_id, behavior))

    def add_car(self, car):
        self._cars.append(car)

    def update(self):
        if self._name == "Start":
            if self._line.get_direction() == "RIGHT":
                try:
                    self.__next_track.add_car(self._cars.pop(0))
                except:
                    pass

        elif self._name == "End":
            if self._line.get_direction() == "LEFT":
                try:
                    self.__next_track.add_car(self._cars.pop(0))
                except:
                    pass


    def __str__(self):
        return_string = "----Station: " + self._name + "---- Cars: "
        for c in self._cars:
            return_string += str(c) + "   "

            if c.get_id() < 10:
                return_string += " "

        return return_string

    def add_next_track(self, track):
        self.__next_track = track

    def get_car_count(self):
        return len(self._cars)
