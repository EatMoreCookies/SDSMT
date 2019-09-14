#CC=g++

# -03 is for optimization level 3
# -Wall - turn on Warnings all
# -std=c++11 standard coding for c++2011
#CFLAGS = -Wall -O3 -std=c++11


#all: main

#main: main.o functions.o heap.o Nate.o
#	$(CC) main.o functions.o heap.o Nate.o -o main

#main.o: main.cpp
#	$(CC) $(CFLAGS) main.cpp

#functions.o: functions.cpp
#	$(CC) $(CFLAGS) functions.cpp

#heap.o: heap.cpp
#	$(CC) $(CFLAGS) heap.cpp

#Nate.o:	Nate.cpp
#	$(CC) $(CFLAGS) Nate.cpp

#clean: 
#	rm -rf *o main




SOURCE = functions.cpp \
         main.cpp \
	 Nate.cpp \
         heap.cpp \

OBJS = $(SOURCE:.cpp=.o)

#declare the variable
GNU = C++ Compiler
GCC = g++

GNU = C++ Linker
LINK = g++

# Turn of -03(optimization level 3) for debugging purposes
# Compiler flags
CFLAGS = -O3 -std=c++11  
CXXFLAGS = $(CFLAGS)

# Fill in special libraries needed here
# LIBS = 

.PHONY: clean

# Targets include all, clean, debug, tar

all : main

main: $(OBJS)
	$(LINK) -o $@ $^ $(LIBS)

driver: main.cpp
	$(LINK) -o $@ $^ $(LIBS) $(CFLAGS)

clean:
	rm -rf *.o main

debug: CXXFLAGS = -DDEBUG -g -std=c++11
debug: $(SOURCE: .cpp = .o)

help:
	@echo " make main  - same as make all"
	@echo " make all   - builds the main target"
	@echo " make       - same as make all"
	@echo " make clean - remove .o .d core main"
	@echo " make debug - make all with -g and -DDEBUG"
	@echo " make tar   - make a tarball of .cpp and .h files"
	@echo " make help  - this message"
-include $(SOURCE:.cpp=.d)

%.d: %.cpp
	@set -e; /usr/bin/rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@

