cmake_minimum_required(VERSION 3.16.3)
project(Advanced_Programming_DoodleJump)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")


# Extend the CMake module path to find the FindSFML.cmake
# file in {project root}/cmake/Modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# Look for SFML >= 2.0, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

# The source files to compile
SET(SRC main.cpp
        src/Utils/Random.cpp
        src/Entity/Entity.cpp
        src/Entity/Platform.cpp
        src/Entity/Platform.h
        src/Entity/Spring.cpp
        src/Entity/Spring.h
        src/Entity/Jetpack.cpp
        src/Entity/Jetpack.h
        src/Entity/Player.cpp
        src/Entity/Player.h
        src/Observer/IObserver.cpp
        src/Observer/IObserver.h
        src/Observer/Subject.cpp
        src/Observer/Subject.h
        Game.cpp
        Game.h
        src/Utils/Stopwatch.cpp
        src/Utils/Stopwatch.h src/Utils/Transform.cpp src/Utils/Transform.h)

# Add include dirs for SFML
# (The SFML_INCLUDE_DIR variable is defined by FindSFML.cmake, if SFML was found)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

# The program we're compiling with the sources set above
ADD_EXECUTABLE(DoodleJump ${SRC})

# Link target to SFML libs
# (The SFML_LIBRARIES variable is defined by FindSFML.cmake, if SFML was found)
TARGET_LINK_LIBRARIES(DoodleJump ${SFML_LIBRARIES})

INSTALL(TARGETS DoodleJump DESTINATION ${PROJECT_SOURCE_DIR}/bin)
