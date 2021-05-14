cmake_minimum_required(VERSION 3.10)
project(BCG-PROJECT)

include_directories(root)
include_directories(gui)
include_directories(program)

message(STATUS "[INFO] Searching for header directories...")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "[INFO] Found ${dir}")
endforeach()