CC := g++
CFLAGS := -Wall --std=c++17 -pg -no-pie
HEADER := include
DEPS := deps
SRC := src/ape
TEST := tests/
BIN := bin/
OBJ := obj

ecs.o: $(wildcard $(SRC)/core/*.cpp) $(wildcard $(SRC)/core/detail/*.cpp) \
	 $(wildcard $(INCLUDE)/ape/core/*.h) $(wildcard $(INCLUDE)/ape/core/detail/*.h)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) -c $(wildcard $(SRC)/core/*.cpp) -c $(wildcard $(SRC)/core/detail/*.cpp)
	mv *.o ./$(OBJ)/ecs/

ecs_test.o: $(wildcard $(TEST)/ecs/*.cpp) $(wildcard $(OBJ)/ecs/*.o)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) -c $(wildcard $(TEST)/ecs/*.cpp)
	mv *.o ./$(OBJ)/ecs

ecs_test: ecs.o ecs_test.o
	$(CC) -o $(BIN)/ecs_test $(wildcard $(OBJ)/ecs/*.o)

clean: 
	rm -r $(OBJ)/*

structure:
	mkdir $(OBJ)/ecs