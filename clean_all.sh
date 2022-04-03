#!/bin/bash

cd bin

rm CMakeFiles -rf 2>/dev/null
rm cmake_install.cmake -f 2>/dev/null
rm CMakeCache.txt -f 2>/dev/null
rm Makefile -f 2>/dev/null
rm lib* -f 2>/dev/null
rm v2g-guru-exi -f 2>/dev/null

cd ..
