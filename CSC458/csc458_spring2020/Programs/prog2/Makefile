# Use the GNU C/C++ compiler:
CC = gcc
CPP = g++

#OBJECT FILES
OBJS = main.o customer.o bank.o

#TARGET FILES
TARGET = bankers

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -pthread -o $(TARGET) $(OBJS)

main.o: main.c bank.h customer.h
	$(CC) -pthread -c main.c

customer.o: customer.h bank.h
	$(CC) -pthread -c customer.c

bank.o: bank.h
	$(CC) -pthread -c bank.c
clean:
	$(RM) *.o *~ $(TARGET)
