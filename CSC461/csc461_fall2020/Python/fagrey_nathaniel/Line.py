from fagrey_nathaniel.Station import Station
from fagrey_nathaniel.Cautious import Cautious
from fagrey_nathaniel.Normal import Normal
from fagrey_nathaniel.Rush import Rush
from fagrey_nathaniel.Track import Track
from fagrey_nathaniel.TimeStation import TimeStation

class Line:

    class IterStation:
        def __init__(self, stations_tracks):
            self.__stations = stations_tracks
            self.__index = None

        # GRADING: INTER_STATION
        def __iter__(self):
            self.__index = -2
            return self

        def __next__(self):
            try:
                self.__index += 2
                return self.__stations[self.__index]

            except:
                raise StopIteration()
    car_ids = 1

    def __init__(self):
        self.__init_function()

    def __init_function(self):
        self.__index = -1
        self.__stations_tracks = []
        self.__direction = "RIGHT"
        self.__time = 0
        self.__car_count = 0
        self.__flipped = False

        start = Station("Start", self)
        track1 = Track(self)
        end = Station("End", self)

        track1.set_left_station(start)
        track1.set_right_station(end)

        start.add_next_track(track1)
        end.add_next_track(track1)

        self.__stations_tracks.append(start)
        self.__stations_tracks.append(track1)
        self.__stations_tracks.append(end)



    def print_line(self):

        print("Time: " + self.__print_float(self.__time) + " min")
        print("Count: " + str(self.__car_count) + " Direction: " + self.__direction)
        print("-----------------------------------")

        self.__print_stations_tracks()

    def __print_stations_tracks(self):
        itr = self.__iter__()

        # GRADING: LOOP_ALL
        for st in itr:
            print(st)

    def add_car(self):
        print("Which type: 0-->Cautious, 1-->Normal, 2-->Rush hour: ", end='')
        choice = input()

        if choice == '0':
            self.__stations_tracks[0].create_car(Line.car_ids, Cautious())

        elif choice == '1':
            self.__stations_tracks[0].create_car(Line.car_ids, Normal())

        elif choice == '2':
            self.__stations_tracks[0].create_car(Line.car_ids, Rush())

        else:
            print("Invalid Option")
            return

        self.__car_count += 1
        Line.car_ids += 1

    def update(self):
        self.__time += 0.5

        itr = self.__iter__()

        for st in itr:
            st.update()

        print("Time:  " + self.__print_float(self.__time))

        self.__print_stations_tracks()

        if self.__stations_tracks[0].get_car_count() == self.__car_count:
            self.__direction = "RIGHT"

        if self.__stations_tracks[-1].get_car_count() == self.__car_count:
            self.__direction = "LEFT"

    def show_stations(self):
        itr = self.IterStation(self.__stations_tracks)

        # GRADING: LOOP_STATION
        for station in itr:
            print(station)

    def make_test_line(self):
        self.__insert_station("1", 1.5)

    def __insert_station(self, name, time):
        station = station = TimeStation(name, time, self)
        track = Track(self)

        station.add_left_track(self.__stations_tracks[-2])
        station.add_right_track(track)

        self.__stations_tracks[-2].set_right_station(station)

        track.set_left_station(station)
        track.set_right_station(self.__stations_tracks[-1])

        self.__stations_tracks[-1].add_next_track(track)

        self.__stations_tracks.insert(-1, track)
        self.__stations_tracks.insert(-2, station)


    def add_station(self):
        self.__init_function()

        choice = input("Number of stations: ")

        index = 1
        while index <= int(choice):
            print("\n----Station " + str(index) + "----")
            length = input("   Length of stop time in minutes: ")

            try:
                length = float(length)
            except:
                print("Stop time must be a number. Got:", length)
                return

            if length < 0 or length % 0.5 != 0:
                print("Stop time must be positive and an increment of 0.5 min. Got:", length)
                return

            name = input("   Name of Station: ")

            self.__insert_station(name, length)

            index += 1

    def __print_float(self, num):
        string_num = str(num)

        if string_num == '0' or string_num == '0.00':
            return '0'
        else:
            return string_num

    # GRADING: INTER_ALL
    def __iter__(self):
        self.__index = -1
        return self

    def __next__(self):
        try:
            self.__index += 1
            return self.__stations_tracks[self.__index]

        except:
            raise StopIteration()

    def get_direction(self):
        return self.__direction

    def get_time(self):
        return self.__time





