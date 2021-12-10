CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: FieldRunners.out

FieldRunners.out: Tower.o Enemy.o Shot.o Player.o Screen.o main.o rsdl.o
	$(CC) Tower.o Enemy.o Shot.o Player.o Screen.o main.o rsdl.o $(CCFLAGS) -o FieldRunners.out

Tower.o: Enemy.h Shot.h RSDL/rsdl.hpp Tower.cpp
	$(CC) -c Tower.cpp

Enemy.o: RSDL/rsdl.hpp Enemy.cpp
	$(CC) -c Enemy.cpp

Shot.o: Enemy.h RSDL/rsdl.hpp Shot.cpp
	$(CC) -c Shot.cpp

Player.o: Enemy.h Tower.h Screen.h RSDL/rsdl.hpp Player.cpp
	$(CC) -c Player.cpp

Screen.o: RSDL/rsdl.hpp Screen.cpp
	$(CC) -c Screen.cpp

main.o: Screen.h Player.h RSDL/rsdl.hpp main.cpp
	$(CC) -c main.cpp

rsdl.o: RSDL/rsdl.hpp RSDL/rsdl.cpp
	$(CC) -c RSDL/rsdl.cpp -o rsdl.o	


clean:
	rm *.o FieldRunners.out