#!/bin/bash

input_file=""
parsed_success=false

OPTIND=1

while getopts hf: opt; do
  case $opt in
    f)
      input_file=$OPTARG
      parsed_success=true
      ;;
  esac
done

if [ "$parsed_success" = true ]
then
  output_name="$(basename $input_file .cpp)"
  g++ --std=c++14 -pg $input_file src/ape/ape.cpp \
  src/ape/core/world.cpp src/ape/core/defines.cpp src/ape/utils/frame_counter.cpp \
  src/ape/graphics/color.cpp src/ape/graphics/graphics.cpp src/ape/graphics/shader.cpp \
  src/ape/graphics/window.cpp src/ape/graphics/texture.cpp src/ape/graphics/sprite.cpp \
  src/ape/graphics/renderer.cpp src/ape/graphics/texture_store.cpp \
  src/ape/core/transform.cpp deps/glad/glad.c \
  -Ideps/  -Iinclude/ -lm -lglfw -lGL -lSOIL
fi
