
all: Goodreads.out

Goodreads.out: main.o functions.o Goodread.o Review.o Book.o User.o Author.o Shelf.o
	g++ -std=c++11 main.o functions.o Goodread.o Review.o Book.o User.o Author.o Shelf.o -o Goodreads.out
	

main.o: main.cpp
	g++ -std=c++11 -c main.cpp


functions.o: functions.cpp functions.h 
	g++ -std=c++11 -c functions.cpp
	



Author.o: Author.cpp Author.h functions.h
	g++ -std=c++11 -c Author.cpp

Book.o: Book.cpp Book.h functions.h Author.h
	g++ -std=c++11 -c Book.cpp

Shelf.o: Shelf.cpp Shelf.h functions.h Book.h
	g++ -std=c++11 -c Shelf.cpp

User.o: User.cpp User.h functions.h Shelf.h Author.h Book.h
	g++ -std=c++11 -c User.cpp


Review.o: Review.cpp Review.h functions.h Book.h User.h
	g++ -std=c++11 -c Review.cpp
	
	
Goodread.o: Goodread.cpp Goodread.h functions.h Review.h Book.h User.h Author.h
	g++ -std=c++11 -c Goodread.cpp


clean:
	rm *.o Goodreads.out
