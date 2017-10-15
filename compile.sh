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
  g++ --std=c++14 -o bin/$output_name $input_file deps/glad/glad.c \
  src/ape/core/detail/world_detail.cpp src/ape/core/defines.cpp \
  src/ape/core/world.cpp \
  src/ape/graphics/detail/window_detail.cpp src/ape/graphics/color.cpp \
  src/ape/graphics/graphics.cpp src/ape/graphics/shader.cpp \
  src/ape/graphics/window.cpp src/ape/ape.cpp \
  src/ape/graphics/detail/graphics_detail.cpp \
  src/ape/graphics/detail/texture_store_detail.cpp \
  src/ape/graphics/texture_store.cpp \
  src/ape/graphics/texture.cpp src/ape/graphics/sprite.cpp \
  src/ape/graphics/renderer.cpp src/ape/core/transform.cpp \
  src/ape/utils/frame_counter.cpp src/ape/scene/scene.cpp \
  src/ape/scene/node.cpp src/ape/scene/detail/scene_detail.cpp \
  -Ideps/  -Iinclude/ -lm -lglfw -lGL -lSOIL
fi
