cmake_minimum_required(VERSION 3.16.3)
project(DoodleJump VERSION 1.0)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-Wall")

# Extend the CMake module path to find the FindSFML.cmake
# file in {project root}/cmake/Modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# Look for SFML >= 2.0, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics audio)

# Add include dirs for SFML
# (The SFML_INCLUDE_DIR variable is defined by FindSFML.cmake, if SFML was found)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

ADD_SUBDIRECTORY(engine)
ADD_SUBDIRECTORY(game)

ADD_EXECUTABLE(DoodleJump src/main.cpp)

TARGET_LINK_LIBRARIES(DoodleJump PUBLIC engine)
TARGET_LINK_LIBRARIES(DoodleJump PUBLIC game)

INSTALL(TARGETS DoodleJump DESTINATION ${PROJECT_SOURCE_DIR}/bin)
