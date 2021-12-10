CC := g++ -std=c++11
 
all: utrip.out

utrip.out: trip.o hotel.o filter.o functions.o room.o command_line.o comment.o rating.o reserve.o user.o date.o error.o sort.o manual_weight.o main.o
	$(CC) trip.o hotel.o filter.o functions.o room.o command_line.o comment.o rating.o reserve.o user.o date.o error.o sort.o manual_weight.o main.o -o utrip.out

trip.o: user.hpp filter.hpp date.hpp functions.hpp hotel.hpp error.hpp sort.hpp trip.hpp trip.cpp
	$(CC) -c trip.cpp

hotel.o: comment.hpp room.hpp functions.hpp rating.hpp user.hpp error.hpp hotel.hpp hotel.cpp
	$(CC) -c hotel.cpp

filter.o: hotel.hpp date.hpp filter.hpp filter.cpp
	$(CC) -c filter.cpp

room.o: date.hpp room.hpp room.cpp
	$(CC) -c room.cpp

command_line.o: trip.hpp command_line.hpp command_line.cpp
	$(CC) -c command_line.cpp

user.o: error.hpp reserve.hpp rating.hpp manual_weight.hpp user.hpp user.cpp
	$(CC) -c user.cpp

reserve.o: date.hpp room.hpp reserve.hpp reserve.cpp
	$(CC) -c reserve.cpp

date.o: error.hpp date.hpp date.cpp
	$(CC) -c date.cpp

error.o: error.hpp error.cpp
	$(CC) -c error.cpp

functions.o: functions.hpp functions.cpp
	$(CC) -c functions.cpp

comment.o: user.hpp comment.hpp comment.cpp
	$(CC) -c comment.cpp

main.o: command_line.hpp trip.hpp main.cpp
	$(CC) -c main.cpp

rating.o: error.hpp user.hpp rating.hpp rating.cpp
	$(CC) -c rating.cpp

sort.o: error.hpp hotel.hpp sort.cpp
	$(CC) -c sort.cpp

manual_weight.o: error.hpp manual_weight.hpp manual_weight.cpp
	$(CC) -c manual_weight.cpp
clean:
	rm *.o utrip.out