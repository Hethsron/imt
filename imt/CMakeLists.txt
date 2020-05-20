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

# Check operating system
if(UNIX)
    if (CMAKE_COMPILER_IS_GNUCC)
        if(CMAKE_BUILD_TYPE MATCHES DEBUG)
            message(STATUS "Debug mode")
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        else(CMAKE_BUILD_TYPE MATCHES DEBUG)
            message(STATUS "Release mode")
            set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
        endif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
        set(CMAKE_CXX_STANDARD 11)
        set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
    endif (CMAKE_COMPILER_IS_GNUCC)
elseif(APPLE)
    if (MINGW)
        if(CMAKE_BUILD_TYPE MATCHES DEBUG)
            message(STATUS "Debug mode")
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        else(CMAKE_BUILD_TYPE MATCHES DEBUG)
            message(STATUS "Release mode")
            set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
        endif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
        set(CMAKE_CXX_STANDARD 11)
        set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
    endif(MINGW)
endif()

# Automatically add the current source and build directories to the include path
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Searches after the QT library on the system and defines some variables
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# Handle The QT MOC processor automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Define program name
set(BINARY ${CMAKE_PROJECT_NAME})

# Set variable for header directory
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include dynamically directory of headers
include_directories(${INCLUDE_DIR})

# Configure headers dependencies
message(STATUS "Loading ${CMAKE_PROJECT_NAME} headers")
file(GLOB_RECURSE HEADERS CMAKE_CONFIGURE_DEPENDS
        ${INCLUDE_DIR}/core/*.hpp
        ${INCLUDE_DIR}/model/*.hpp
        ${INCLUDE_DIR}/view/*.hpp
        ${INCLUDE_DIR}/controller/*.hpp
        )

if ("${HEADERS}" STREQUAL "")
    message(WARNING "Fatal error - cannot access to ${CMAKE_PROJECT_NAME} headers")
else("${HEADERS}" STREQUAL "")
    message(STATUS "Headers of ${CMAKE_PROJECT_NAME} have been loaded successfully")
endif("${HEADERS}" STREQUAL "")

# Set variable for source directory
set(SRCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Configure sources dependencies
message(STATUS "Loading ${CMAKE_PROJECT_NAME} sources")
FILE(GLOB_RECURSE SRCS CMAKE_CONFIGURE_DEPENDS
        ${SRCS_DIR}/core/*.cpp
        ${SRCS_DIR}/model/*.cpp
        ${SRCS_DIR}/view/*.cpp
        ${SRCS_DIR}/controller/*.cpp
        ${SRCS_DIR}/*.cpp
        )

if ("${SRCS}" STREQUAL "")
    message(WARNING "Fatal error - cannot access to ${CMAKE_PROJECT_NAME} headers")
else("${SRCS}" STREQUAL "")
    message(STATUS "Headers of ${CMAKE_PROJECT_NAME} have been loaded successfully")
endif("${SRCS}" STREQUAL "")

# Set executable output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Adding executable
add_executable(${BINARY} ${SRCS})

# Adding target link libraries
target_link_libraries(${BINARY} PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)

# Check doxygen
find_package(Doxygen QUIET)
if (NOT DOXYGEN_FOUND)
    message(WARNING "Doxygen not found - cannot generate documentation")
elseif (DOXYGEN_FOUND)
    message(STATUS "Doxygen found - generating documentation")
    # Copies a doxygen <input> file to a doxygen <output> file
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in ${CMAKE_SOURCE_DIR}/doc/Doxyfile)

    # Set doxygen <input> and <output> file
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile)

    # Substitutes variable values referenced @ONLY
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message(STATUS "Doxygen build started ...")

    # Adds a target with the given name that executes the given commands
    add_custom_target( doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating ${CMAKE_PROJECT_NAME} documentation with Doxygen" VERBATIM )
endif (NOT DOXYGEN_FOUND)