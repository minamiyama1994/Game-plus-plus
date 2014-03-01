#! /bin/sh

clang-format -i $(find -name '*.h') $(find -name '*.hpp') $(find -name '*.c') $(find -name '*.cpp')