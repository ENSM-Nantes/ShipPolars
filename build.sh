#!/bin/bash

mkdir -p bin
g++ -Iinclude/ src/*.cpp src/*.c -o PolarManager `pkg-config --cflags --libs gtk4` -lm -lnetcdf -lenet
mv PolarManager bin/
