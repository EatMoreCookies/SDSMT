#Makefile for CSC 315 Data Structures & Algorithms programs.
#
#
# Modifications:
#
# C++ compiler flags (add -O to optimize)
CFLAGS += -g -O2 -Wall -fmax-errors=5
CXXFLAGS += $(CFLAGS) -std=c++11

# linker
LINK = g++

#-----------------------------------------------------------------------

# Targets:


# MAKE allows the use of "wildcards", to make writing compilation instructions
# a bit easier. GNU make uses $@ for the target and $^ for the dependencies.

#===========================================

# By default, build (almost) everything:



#all:   $(EXE)

#===========================================
SRC = main.cpp bacon.cpp bacon_map.cpp menu.cpp
OBJ = $(SRC:.cpp=.o)
bacon:	$(OBJ)
	$(LINK) -g -o $@ $^


# code timing routine: do NOT optimize
chrono: chrono.o
	$(LINK) -o $@ $^

#===========================================


clean:
	rm -f *.o *~ core bacon main $(EXE)

cleanall:
	rm -f *.o *~ core a.out $(EXE)



