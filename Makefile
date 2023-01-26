CC=g++
EXE_FILE = prog

all: $(EXE_FILE)

$(EXE_FILE): driver.cpp game.o adventurer.o room.o event.o bats.o gold.o pit.o wumpus.o
	$(CC) driver.cpp game.o adventurer.o room.o event.o bats.o gold.o pit.o wumpus.o -g -o $(EXE_FILE)

game.o: game.h game.cpp
	$(CC) -c game.cpp

adventurer.o: adventurer.h adventurer.cpp
	$(CC) -c adventurer.cpp

room.o: room.h room.cpp
	$(CC) -c room.cpp

event.o: event.h event.cpp
	$(CC) -c event.cpp

bats.o: bats.h bats.cpp
	$(CC) -c bats.cpp

gold.o: gold.h gold.cpp
	$(CC) -c gold.cpp

pit.o: pit.h pit.cpp
	$(CC) -c pit.cpp

wumpus.o: wumpus.h wumpus.cpp
	$(CC) -c wumpus.cpp

clean:
	rm -f *.o $(EXE_FILE)