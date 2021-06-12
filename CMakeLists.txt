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
# SFML
set(SFML_DIR "${PROJECT_SOURCE_DIR}/libs/SFML/lib/cmake/SFML") #firstly we are searching for SFML in our dir tree
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS system window graphics QUIET)

if(NOT SFML_FOUND) #if SFML wasnt found then we search in config
	include("config.cmake")
	find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED QUIET)
	set(FOUND_WITH_CONFIG True)
else()
	set(FOUND_IN_PROJECT_TREE True)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows") #for compatibility with linux os
	set(LIBS "opengl32" "comdlg32" "ole32")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	set(LIBS "GL")
endif()

if(FOUND_IN_PROJECT_TREE)
	message(STATUS "[INFO] SFML found in project tree!")
elseif(FOUND_WITH_CONFIG)
	message(STATUS "[INFO] SFML found with config file in ${SFML_DIR}")
else()
	message(STATUS "[INFO] SFML was not found, aborting...")
endif()
###################################################################################################
# tinyfiledialogs

include_directories("${PROJECT_SOURCE_DIR}/dep/tinyfiledialogs")
list(APPEND SOURCES "${PROJECT_SOURCE_DIR}/dep/tinyfiledialogs/tinyfiledialogs.cpp")

###################################################################################################

if(SFML_FOUND)
	add_executable(${PROGRAM_NAME} ${SOURCES} main.cpp)
	target_link_libraries(${PROGRAM_NAME} PUBLIC sfml-system sfml-window sfml-graphics ${LIBS})
	target_precompile_headers(${PROGRAM_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/root/Root.h")
endif()

###################################################################################################
