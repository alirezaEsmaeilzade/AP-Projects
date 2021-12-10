CC := g++ -std=c++11

all: 1.out

1.out: JsonBuilder.o Element.o Container.o Object.o Data_with_name.o Data_without_name.o Array.o error.o main.o
	$(CC) JsonBuilder.o Element.o Container.o Object.o Data_with_name.o Data_without_name.o Array.o error.o main.o -o 1.out

JsonBuilder.o: Element.hpp Container.hpp Object.hpp Data_with_name.hpp Data_without_name.hpp Array.hpp error.hpp JsonBuilder.cpp
	$(CC) -c JsonBuilder.cpp

main.o: Element.hpp Container.hpp Object.hpp Data_with_name.hpp Data_without_name.hpp Array.hpp JsonBuilder.hpp error.hpp main.cpp
	$(CC) -c main.cpp

Object.o: Element.hpp Data_with_name.hpp Data_without_name.hpp Container.hpp Object.cpp
	$(CC) -c Object.cpp

Array.o: Element.hpp Data_with_name.hpp Data_without_name.hpp Container.hpp Array.cpp
	$(CC) -c Array.cpp

Container.o: Element.hpp Data_with_name.hpp Data_without_name.hpp Container.cpp
	$(CC) -c Container.cpp

Data_with_name.o: Element.hpp Data_with_name.cpp
	$(CC) -c Data_with_name.cpp

Data_without_name.o: Element.hpp Data_without_name.cpp
	$(CC) -c Data_without_name.cpp

Element.o: Element.cpp
	$(CC) -c Element.cpp

error.o: error.cpp
	$(CC) -c error.cpp
clean:
	rm *.o 1.out