#!/bin/bash
#### compile cpp programs

g++ -c -I./include/ src/*.cc
g++ -o bin/try *.o
rm -f *.o
#g++ -o bin/try -Iinclude/ src/*.cc
