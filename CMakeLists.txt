cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(PROGRAM_NAME BCG-PROJECT)
project(BCG-PROJECT)

###################################################################################################

set(CMAKE_CXX_FLAGS "-Wall -g -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_COLOR_MAKEFILE True)

###################################################################################################

add_subdirectory(${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES src/*.cpp)

###################################################################################################

set(SFML_DIR "${PROJECT_SOURCE_DIR}/libs/SFML/lib/cmake/SFML") #firstly we are searching for SFML in our dir tree
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS system window graphics QUIET)

if(NOT SFML_FOUND) #if SFML wasnt found then we search in config
	message(STATUS "[INFO] SFML not found in project tree...")
	include("config.cmake")
endif()
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED QUIET)

###################################################################################################

if(SFML_FOUND)
	message(STATUS "[INFO] SFML found with config file in ${SFML_DIR}")
	add_executable(${PROGRAM_NAME} ${SOURCES} main.cpp)
	target_link_libraries(${PROGRAM_NAME} PUBLIC sfml-system sfml-window sfml-graphics)
else()
	message(STATUS "[INFO] SFML was not found, aborting...")
endif()

###################################################################################################
