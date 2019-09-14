
CXX = g++
CXXFLAGS = -g -std=c++11 -fPIC -Wall
INCS = -I./ -I../src/

SRC_PATH = ../src/


FILES = $(SRC_PATH)EasyEight.cpp
FILES += $(SRC_PATH)Actor.cpp
FILES += $(SRC_PATH)direction.cpp
FILES += main.cpp
FILES += shortestPathTests.cpp
FILES += MapData.cpp
FILES += attackTests.cpp
FILES += $(SRC_PATH)SimpleAI.cpp
FILES += evadeTests.cpp

main: $(FILES:.cpp=.o)
	$(CXX) $(CXXFLAGS) $(INCS) -o testUnitAll $(FILES:.cpp=.o) 

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c $? -o $@
clean:
	rm -rf testUnitAll *.o 
