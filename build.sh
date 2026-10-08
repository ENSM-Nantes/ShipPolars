#!/bin/bash

mkdir -p bin
g++ -Iinclude/ src/*.cpp src/*.c src/*.o -o ShipPolars `pkg-config --cflags --libs gtk4` -lm -lnetcdf -lenet
mv ShipPolars bin/
