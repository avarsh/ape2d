CC := g++
CFLAGS := -Wall --std=c++17 -pg -no-pie
SHAREDFLAGS := -fPIC
HEADER := include
DEPS := deps
SRC := src/ape
TEST := tests/
BIN := bin
OBJ := obj
LIB := lib
LINKER_FLAGS := -lSDL2

core.o: $(wildcard $(SRC)/core/*.cpp) $(wildcard $(SRC)/core/detail/*.cpp) \
	 $(wildcard $(INCLUDE)/ape/core/*.h) $(wildcard $(INCLUDE)/ape/core/detail/*.h)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) $(SHAREDFLAGS) -c $(wildcard $(SRC)/core/*.cpp) $(wildcard $(SRC)/core/detail/*.cpp)
	mv *.o ./$(OBJ)/core/

ecs_test.o: $(wildcard $(TEST)/ecs/*.cpp) $(wildcard $(OBJ)/ecs/*.o)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) -c $(wildcard $(TEST)/ecs/*.cpp)
	mv *.o ./$(OBJ)/core/

ecs_test: core.o ecs_test.o
	$(CC) -o $(BIN)/ecs_test $(wildcard $(OBJ)/core/*.o)

graphics.o: $(wildcard $(SRC)/graphics/*.cpp) $(wildcard $(INCLUDE)/graphics/*.h) \
			$(wildcard $(SRC)/graphics/detail/*.cpp) $(wildcard $(INCLUDE)/graphics/detail/*.h)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) $(SHAREDFLAGS) -c $(wildcard $(SRC)/graphics/*.cpp) $(wildcard $(TEST)/graphics/detail/*.cpp) $(LINKER_FLAGS)
	mv *.o ./$(OBJ)/graphics/

scene.o: $(wildcard $(SRC)/scene/*.cpp) $(wildcard $(INCLUDE)/scene/*.h) \
			$(wildcard $(SRC)/scene/detail/*.cpp) $(wildcard $(INCLUDE)/scene/detail/*.h)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) $(SHAREDFLAGS) -c $(wildcard $(SRC)/scene/*.cpp) $(wildcard $(SRC)/scene/detail/*.cpp) $(LINKER_FLAGS)
	mv *.o ./$(OBJ)/scene/

ape.o: $(wildcard $(SRC)/*.cpp) $(wildcard $(INCLUDE)/*.h) \
			$(wildcard $(SRC)/detail/*.cpp) $(wildcard $(INCLUDE)/detail/*.h)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) $(SHAREDFLAGS) -c $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/detail/*.cpp) $(LINKER_FLAGS)
	mv *.o ./$(OBJ)/

ape_shared: core.o graphics.o scene.o ape.o
	$(CC) -shared -o $(LIB)/shared/libape2d.so $(wildcard $(OBJ)/*.o) $(wildcard $(OBJ)/core/*.o) $(wildcard $(OBJ)/graphics/*.o) $(wildcard $(OBJ)/scene/*.o)

# TODO: Static library for use in game deployment. We don't 
# need the position independent code, so must get rid of 
# SHAREDFLAGS during compilation

clean: 
	rm -r $(OBJ)
	rm -r $(BIN)
	rm -r $(LIB)

structure:
	mkdir $(OBJ)
	mkdir $(BIN)
	mkdir $(LIB)
	mkdir $(OBJ)/core
	mkdir $(OBJ)/graphics
	mkdir $(OBJ)/scene 
	mkdir $(LIB)/shared