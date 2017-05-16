CXX := g++
CPPFLAGS := -std=c++14
LDLIBS := -lglfw -lm -lGL
DEPS := ./deps/glad/glad.c
APEWORLD := ./src/ape/ecs/world.cpp ./src/ape/ecs/defines.cpp
APEGRAPHICS := ./src/ape/graphics/graphics.cpp ./src/ape/graphics/shader.cpp ./src/ape/graphics/buffer.cpp
INCLUDEDIRS := -Iinclude/ -Ideps/

primitives: ./tests/primitivetest.cpp
	$(CXX) $(CPPFLAGS) -o ./bin/primitivetest ./tests/primitivetest.cpp $(DEPS) $(APEGRAPHICS) $(APEWORLD) $(INCLUDEDIRS) $(LDLIBS)
