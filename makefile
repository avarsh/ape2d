CXX := g++
CPPFLAGS := -std=c++14
LDLIBS := -lglfw -lm -lGL 
DEPS := ./deps/glad/glad.c 
APEFILES := ./src/ape/ecs/world.cpp ./src/ape/ecs/defines.cpp ./src/ape/graphics/graphics.cpp ./src/ape/graphics/shader.cpp
INCLUDEDIRS := -Iinclude/ -Ideps/

primitives: ./tests/primitivetest.cpp 
	$(CXX) $(CPPFLAGS) -o ./bin/primitivetest ./tests/primitivetest.cpp $(DEPS) $(APEFILES) $(INCLUDEDIRS) $(LDLIBS)

