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

# Automatically add the current source and build directories to the include path
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (WIN32)
    if(MINGW)
        # Set prefix path
        set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.0\\mingw81_64")
    endif(MINGW)
endif(WIN32)

# Searches after the library on the system and defines some variables
find_package(Qt5 REQUIRED COMPONENTS Core DBus Gui Help Multimedia MultimediaWidgets PrintSupport UiTools Widgets)

# Handle The QT MOC processor automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Define program name
set(BINARY ${CMAKE_PROJECT_NAME}_test)

# Set variable for header directory
set(TESTS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set variable for framework header directory
set(EXTERNAL_INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}/include)

# Include dynamically directory of headers
include_directories(${TESTS_INCLUDE_DIR})
include_directories(${EXTERNAL_INCLUDES_DIR})

# Configure headers dependencies
message(STATUS "Loading tests headers")
file(GLOB_RECURSE TESTS_HEADERS CMAKE_CONFIGURE_DEPENDS
        ${TESTS_INCLUDE_DIR}/*.hpp
        )

if ("${TESTS_HEADERS}" STREQUAL "")
    message(WARNING "Fatal error - cannot access to tests headers")
else("${TESTS_HEADERS}" STREQUAL "")
    message(STATUS "Headers of tests have been loaded successfully")
endif("${TESTS_HEADERS}" STREQUAL "")

# Set variable for source directory
set(TESTS_SRCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Configure sources dependencies
message(STATUS "Loading tests sources")
FILE(GLOB_RECURSE TESTS_SRCS CMAKE_CONFIGURE_DEPENDS
        ${TESTS_SRCS_DIR}/*.cpp
        )

if ("${TESTS_SRCS}" STREQUAL "")
    message(WARNING "Fatal error - cannot access to tests headers")
else("${TESTS_SRCS}" STREQUAL "")
    message(STATUS "Headers of tests have been loaded successfully")
endif("${TESTS_SRCS}" STREQUAL "")

# Set executable output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Adding executable
add_executable(${BINARY} ${TESTS_SRCS})

# Adding test
add_test(NAME ${BINARY} COMMAND ${BINARY})

# Check operating system
if(UNIX)
    if (CMAKE_COMPILER_IS_GNUCC)
        # Set variable for framework library
        set(EXTERNAL_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}/lib/lib${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}.so)
    endif (CMAKE_COMPILER_IS_GNUCC)
elseif(APPLE)
    if (MINGW)
        # Set variable for framework library
        set(EXTERNAL_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}/lib/lib${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}.dylib)
    endif(MINGW)
elseif(WIN32)
    if (MINGW)
        # Set variable for framework library
        set(EXTERNAL_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}/lib/lib${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}.dll)
    endif(MINGW)
endif()

# Adding target link libraries
target_link_libraries(${BINARY} PRIVATE ${EXTERNAL_LIBS} gtest Qt5::Core Qt5::DBus Qt5::Gui Qt5::Help Qt5::Multimedia Qt5::MultimediaWidgets Qt5::PrintSupport Qt5::UiTools Qt5::Widgets)