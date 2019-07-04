CC := g++
CFLAGS := -Wall --std=c++14 -pg -no-pie
HEADER := include
SRC := src/ape
OBJ := obj

ecs: $(wildcard $(SRC)/core/*.cpp) $(wildcard include/ape/core/*.h)
	$(CC) -I$(HEADER) $(CFLAGS) -c $(wildcard src/ape/core/*.cpp) -o $(OBJ)/ecs.o

clean: 
	rm $(OBJ)/*