CXX := g++
CPPFLAGS := -std=c++14
LDLIBS := -lglfw -lm -lGL
DEPS := ./deps/glad/glad.c
APEWORLD := ./src/ape/ecs/world.cpp ./src/ape/ecs/defines.cpp
APEUTILS := ./src/ape/utils/framecounter.cpp
APEGRAPHICS := ./src/ape/graphics/graphics.cpp ./src/ape/graphics/shader.cpp ./src/ape/graphics/buffer.cpp
INCLUDEDIRS := -Iinclude/ -Ideps/

primitives: ./tests/primitivetest.cpp
	$(CXX) $(CPPFLAGS) -o ./bin/primitivetest ./tests/primitivetest.cpp $(DEPS) $(APEGRAPHICS) $(APEUTILS) $(APEWORLD) $(INCLUDEDIRS) $(LDLIBS)

mousetest: ./tests/mousetest.cpp
	$(CXX) $(CPPFLAGS) -o ./bin/mousetest ./tests/mousetest.cpp $(DEPS) $(APEGRAPHICS) $(APEUTILS) $(APEWORLD) $(INCLUDEDIRS) $(LDLIBS)
