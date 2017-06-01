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
  g++ --std=c++14 -o bin/$output_name $input_file src/ape/ape.cpp \
  src/ape/core/world.cpp src/ape/core/defines.cpp src/ape/utils/frame_counter.cpp \
  src/ape/graphics/color.cpp src/ape/graphics/graphics.cpp src/ape/graphics/shader.cpp \
  src/ape/graphics/vertex_attributes.cpp src/ape/graphics/window.cpp \
  src/ape/graphics/batch_renderer.cpp src/ape/graphics/mesh.cpp src/ape/graphics/texture.cpp \
  deps/glad/glad.c \
  -Ideps/  -Iinclude/ -lm -lglfw -lGL -lSOIL
fi
