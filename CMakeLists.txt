cmake_minimum_required(VERSION 3.1)

project(ImacGL)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(Freetype REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")


#Pour gérer un bug a la fac, a supprimer sur machine perso:
#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR} ${SDL_MIXER_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR}
glimac/include third-party/include)
include_directories (/usr/include/freetype2)
set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES} ${GLEW_LIBRARY} ${ASSIMP_LIBRARIES} ${GLFW_LIBRARIES} ${SDL_MIXER_LIBRARY} glfw)

add_subdirectory(glimac)

file(GLOB TP_DIRECTORIES "project")

add_subdirectory(project)

