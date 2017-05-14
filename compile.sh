#!/bin/bash

input_file=""

OPTIND=1

while getopts hf: opt; do
  case $opt in
    f)
      input_file=$OPTARG
      ;;
  esac
done

output_name="$(basename $input_file .cpp)"

g++ --std=c++14 -o bin/$output_name $input_file ./deps/glad/glad.c ./src/graphics/shader.cpp ./src/graphics/graphics.cpp -I./deps/ -I./include/ -lglfw -lm -lGL
