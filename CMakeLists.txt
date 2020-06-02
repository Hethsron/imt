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
project(vera
        VERSION 1.0.1
        HOMEPAGE_URL "https://github.com/Hethsron/imt.git"
        DESCRIPTION "Vera in C++")

# Set project version
set(CMAKE_CXX_STANDARD 11)

# Set variable for directories
set(LIBS_GOOGLETEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/googletest)
set(SRCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME})
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Compress html files
find_program(GENERATOR qhelpgenerator)
if(NOT GENERATOR)
    message(FATAL_ERROR "Generator not found - cannot compress ${CMAKE_PROJECT_NAME} html files")
else(NOT GENERATOR)
	message(STATUS "Generator found - compressing ${CMAKE_PROJECT_NAME} html files")

	# Set qcollectiongenerator <input> and <output> file
	set(GENERATOR_IN ${CMAKE_CURRENT_SOURCE_DIR}/resources/assets/qhc/summary.qhcp)
	set(GENERATOR_OUT ${CMAKE_CURRENT_SOURCE_DIR}/resources/assets/qhc/summary.qhc)

	add_custom_target(qhc ALL
		COMMAND ${GENERATOR} ${GENERATOR_IN} -o ${GENERATOR_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Compress ${CMAKE_PROJECT_NAME} the html files"
	)
endif(NOT GENERATOR)

# Include this directories to find the headers files
include_directories(${LIBS_GOOGLETEST_DIR})
include_directories(${SRCS_DIR})

# Adding project subdirectories
add_subdirectory(${SRCS_DIR})
add_subdirectory(${TESTS_DIR})
add_subdirectory(${LIBS_GOOGLETEST_DIR})