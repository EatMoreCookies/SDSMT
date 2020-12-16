class Track:

    def __init__(self, line):
        self.__cars = []
        self.__length = 0.75
        self.__speed = 30
        self.__line = line
        self.__right_station = None
        self.__left_station = None

    def update(self):
        if self.__line.get_direction() == "RIGHT":
            next_station = self.__right_station

        else:
            next_station = self.__left_station

        car_count = len(self.__cars)

        list_index = []

        for i in range(0, car_count):
            if self.__cars[i].update(car_count) >= self.__length:
                self.__cars[i].reset_location()
                next_station.add_car(self.__cars[i])
            else:
                list_index.append(i)

        copy = []
        for i in list_index:
            copy.append(self.__cars[i])

        self.__cars = copy

    def add_car(self, car):
        self.__cars.append(car)

    def __str__(self):
        return_string = "    "
        for c in self.__cars:
            return_string += str(c) + "  "

            if c.get_id() < 10:
                return_string += " "

        return return_string

    def set_right_station(self, station):
        self.__right_station = station

    def set_left_station(self, station):
        self.__left_station = station



