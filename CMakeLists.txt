cmake_minimum_required(VERSION 3.3)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
project(GloVe)

option(GLOVE_BUILD_STATIC "Build static library"    ON)
option(GLOVE_BUILD_SHARED "Build shared library"    ON)
option(GLOVE_BUILD_TESTS  "Build tests"             ON)

if(WIN32)
   message(WARNING "cmaking for windows")
else()
   set(CMAKE_C_FLAGS " -fPIC -lm -pthread -Ofast -march=native -funroll-loops -Wno-unused-result")
endif()

add_subdirectory("./src")

IF(GLOVE_BUILD_TESTS)
    add_subdirectory("demo")
ENDIF()