from fagrey_nathaniel.Station import Station

class TimeStation(Station):
    def __init__(self, name, release_time, line):
        Station.__init__(self, name, line)
        self.__release_time = release_time
        self.__line = line
        self.__timer = self.__release_time
        self.__right_track = None
        self.__left_track = None
        self.__first_car = True

    def update(self):
        if self.__line.get_direction() == "RIGHT":
            next = self.__right_track

        else:
            next = self.__left_track

        length = len(self._cars)

        if len(self._cars) > 0:
            if self.__first_car is True:
                self.__first_car = False
                self.__timer -= 0.5
            else:
                self.__timer -= 0.5
                if self.__timer <= 0:
                    next.add_car(self._cars.pop(0))
                    self.__timer = self.__release_time
                    self.__first_car = True

    def __str__(self):
        return_string = "----Station: " + self._name + "---- Cars: "
        for c in self._cars:
            return_string += str(c) + "   "

            if c.get_id() < 10:
                return_string += " "

        return_string += "<<-release: " + str(self.__timer)

        return return_string

    def add_right_track(self, track):
        self.__right_track = track

    def add_left_track(self, track):
        self.__left_track = track