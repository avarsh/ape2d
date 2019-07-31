CC := g++
CFLAGS := -Wall --std=c++17 -pg -no-pie
SHAREDFLAGS := -fPIC
HEADER := include
DEPS := deps
SRC := src/ape
INCLUDE := include/ape
TEST := tests/
BIN := bin
OBJ := obj
LIB := lib
LINKER_FLAGS := -lSDL2 -lSDL2_image

core.o: $(wildcard $(SRC)/core/*.cpp) $(wildcard $(SRC)/core/detail/*.cpp) \
	 $(wildcard $(INCLUDE)/core/*.h) $(wildcard $(INCLUDE)/core/detail/*.h)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) $(SHAREDFLAGS) -c $(wildcard $(SRC)/core/*.cpp) $(wildcard $(SRC)/core/detail/*.cpp)
	mv *.o ./$(OBJ)/core/

ecs_test.o: $(wildcard $(TEST)/ecs/*.cpp) $(wildcard $(OBJ)/ecs/*.o)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) -c $(wildcard $(TEST)/ecs/*.cpp)
	mv *.o ./$(OBJ)/core/

ecs_test: core.o ecs_test.o
	$(CC) -o $(BIN)/ecs_test $(wildcard $(OBJ)/core/*.o)

graphics.o: $(wildcard $(SRC)/graphics/*.cpp) $(wildcard $(INCLUDE)/graphics/*.h) \
			$(wildcard $(SRC)/graphics/detail/*.cpp) $(wildcard $(INCLUDE)/graphics/detail/*.h)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) $(SHAREDFLAGS) -c $(wildcard $(SRC)/graphics/*.cpp) $(wildcard $(SRC)/graphics/detail/*.cpp)
	mv *.o ./$(OBJ)/graphics/

scene.o: $(wildcard $(SRC)/scene/*.cpp) $(wildcard $(INCLUDE)/scene/*.h) \
			$(wildcard $(SRC)/scene/detail/*.cpp) $(wildcard $(INCLUDE)/scene/detail/*.h)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) $(SHAREDFLAGS) -c $(wildcard $(SRC)/scene/*.cpp) $(wildcard $(SRC)/scene/detail/*.cpp)
	mv *.o ./$(OBJ)/scene/

input.o: $(wildcard $(SRC)/input/*.cpp) $(wildcard $(INCLUDE)/input/*.h)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) $(SHAREDFLAGS) -c $(wildcard $(SRC)/input/*.cpp)
	mv *.o ./$(OBJ)/input/

file.o: $(wildcard $(SRC)/file/*.cpp) $(wildcard $(INCLUDE)/file/*.h)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) $(SHAREDFLAGS) -c $(wildcard $(SRC)/file/*.cpp)
	mv *.o ./$(OBJ)/file/

ape.o: $(wildcard $(SRC)/*.cpp) $(wildcard $(INCLUDE)/*.h) \
			$(wildcard $(SRC)/detail/*.cpp) $(wildcard $(INCLUDE)/detail/*.h)
	$(CC) -I$(HEADER) -I$(DEPS) $(CFLAGS) $(SHAREDFLAGS) -c $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/detail/*.cpp)
	mv *.o ./$(OBJ)/

ape_shared: core.o graphics.o scene.o ape.o file.o input.o
	$(CC) -shared -o $(LIB)/shared/libape2d.so $(wildcard $(OBJ)/*.o) $(wildcard $(OBJ)/core/*.o) $(wildcard $(OBJ)/graphics/*.o) $(wildcard $(OBJ)/scene/*.o) $(wildcard $(OBJ)/file/*.o) $(wildcard $(OBJ)/input/*.o) $(LINKER_FLAGS)

platformer: examples/platformer/platformer.cpp
	$(CC) -I$(HEADER) -L./lib/shared $(CFLAGS) -o $(BIN)/platformer examples/platformer/platformer.cpp -lSDL2 -lape2d 

install:
	sudo cp ./lib/shared/libape2d.so /usr/lib/libape2d.so

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
	mkdir $(OBJ)/file 
	mkdir $(OBJ)/input
	mkdir $(LIB)/shared

rebuild:
	make clean 
	make structure
	make ape_shared 
	sudo make install 
	make platformer
	./bin/platformer