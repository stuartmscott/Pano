#!/bin/sh

xcrun run-clang-tidy -p build -checks="-clang-analyzer-optin.core.EnumCastOutOfRange"
#clang-tidy src/*.cpp include/Pano/*.h color/*/src/*.cpp color/*/include/*/*.h icon/*/src/*.cpp icon/*/include/*/provider.h font/*/src/*.cpp font/*/include/*/provider.h test/src/*.cpp test/include/*/*.h samples/*/*.cpp samples/*/include/*/*.h
