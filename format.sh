#!/bin/sh

clang-format -style=Google -i src/*.cpp include/Pano/*.h color/*/src/*.cpp color/*/include/*/*.h icon/*/src/*.cpp icon/*/include/*/provider.h font/*/src/*.cpp font/*/include/*/provider.h test/src/*.cpp test/include/*/*.h samples/*/*.cpp samples/*/include/*/*.h
