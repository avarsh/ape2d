CXX := g++
CPPFLAGS := -std=c++14
LDLIBS := -lglfw -lm -lGL -lSOIL
DEPS := ./deps/glad/glad.c
APEWORLD := ./src/ape/ecs/world.cpp ./src/ape/ecs/defines.cpp
APEUTILS := ./src/ape/utils/framecounter.cpp
APEGRAPHICS := ./src/ape/graphics/graphics.cpp ./src/ape/graphics/static.cpp \
	./src/ape/graphics/shader.cpp ./src/ape/graphics/sprite_batcher.cpp \
	./src/ape/graphics/texture.cpp ./src/ape/graphics/buffer.cpp
INCLUDEDIRS := -Iinclude/ -Ideps/

window: ./tests/window.cpp
	$(CXX) $(CPPFLAGS) -o ./bin/window ./tests/window.cpp $(DEPS) $(APEGRAPHICS) $(APEUTILS) $(APEWORLD) $(INCLUDEDIRS) $(LDLIBS)

sprite: ./tests/sprite.cpp
	$(CXX) $(CPPFLAGS) -o ./bin/sprite ./tests/sprite.cpp $(DEPS) $(APEGRAPHICS) $(APEUTILS) $(APEWORLD) $(INCLUDEDIRS) $(LDLIBS)
