##/////////////////////////////////////////////////////////////////////////////////////////////////////////
## AUTHOR: Hethsron Jedaël BOUEYA
##
##                                          LICENSE AGREEMENT
##                              Copyright (c) 2020, Université de Haute Alsace
##                            Ecole Nationale Supérieure d'Ingénieurs Sud-Alsace
##                                          68200 Mulhouse, France
##
## Redistribution and use in source and binary form, with or without modification, are in no way permitted.
##                  Any violation could lead to prosecution and criminal conviction.
##/////////////////////////////////////////////////////////////////////////////////////////////////////////
cmake_minimum_required (VERSION 3.16)

# Define project name
project(imt
        VERSION 1.0.1
        HOMEPAGE_URL "https://github.com/Hethsron/imt.git"
        DESCRIPTION "Ahora in C++")

# Set project version
set(CMAKE_CXX_STANDARD 11)

# Set variable for directories
set(LIBS_GOOGLETEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/googletest)
set(SRCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME})
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Include this directories to find the headers files
include_directories(${LIBS_GOOGLETEST_DIR})
include_directories(${SRCS_DIR})

# Adding project subdirectories
add_subdirectory(${SRCS_DIR})
add_subdirectory(${TESTS_DIR})
add_subdirectory(${LIBS_GOOGLETEST_DIR})