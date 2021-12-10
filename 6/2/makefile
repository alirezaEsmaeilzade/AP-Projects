CC := g++ -std=c++11

all: 2.out

2.out: functions.o error.o channel.o robots.o massager.o main.o
	$(CC) functions.o error.o channel.o robots.o massager.o main.o -o 2.out
functions.o: massager.hpp functions.cpp
	$(CC) -c functions.cpp

error.o: error.cpp
	$(CC) -c error.cpp

channel.o: channel.hpp channel.cpp
	$(CC) -c channel.cpp


robots.o: robots.hpp robots.cpp
	$(CC) -c robots.cpp

massager.o: robots.hpp channel.hpp error.hpp massager.cpp
	$(CC) -c massager.cpp

main.o: massager.hpp functions.hpp main.cpp
	$(CC) -c main.cpp

clean:
	rm *.o 2.out