cmake_minimum_required(VERSION 3.13)

project(IMACDream LANGUAGES C CXX)
#add_definitions(-lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi)

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#GLFW
find_package(glfw3 3.3 REQUIRED)
# OpenGL
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
message(STATUS "Glew lib : " ${GLEW_LIBRARY})

# GLM
find_package(glm REQUIRED)
message(STATUS "GLM included at " ${GLM_INCLUDE_DIR})

# ASSIMP
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in " ${ASSIMP_INCLUDE_DIR})

# SDL2
find_package(SDL2 REQUIRED)
if(${SDL2_FOUND})
    message(STATUS "lib SDL2 found")
    message(STATUS "  version " ${SDL2_VERSION_STRING})
    message(STATUS "  include " ${SDL2_INCLUDE_DIR})
else()
    message(FATAL_ERROR "lib SDL2 not found")
endif()

# SDL2_Image
find_package(SDL2_image REQUIRED)
message(STATUS "Found SDL2_Image in " ${SDL2_image})

# SDL2_Image
find_package(SDL2_mixer REQUIRED)
message(STATUS "Found SDL2_mixer in " ${SDL2_mixer})

# Link libraries
link_directories(${CMAKE_SOURCE_DIR}/lib)
set(LIBS assimp SDL2 SDL2_image SDL2_mixer)

# Build Main Project

# Add source files
file(GLOB_RECURSE SRC_FILES 
	${CMAKE_SOURCE_DIR}/src/libs/*.c
	${CMAKE_SOURCE_DIR}/src/libs/*.cpp
	${CMAKE_SOURCE_DIR}/src/impl/*.c
	${CMAKE_SOURCE_DIR}/src/impl/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
${CMAKE_SOURCE_DIR}/src/libs/*.h
${CMAKE_SOURCE_DIR}/src/libs/*.hpp
${CMAKE_SOURCE_DIR}/src/impl/*.h
${CMAKE_SOURCE_DIR}/src/impl/*.hpp)

# Define the executable

file(GLOB EXEC_FILES "${CMAKE_SOURCE_DIR}/src/execs/*.cpp")


foreach(TMP_PATH ${EXEC_FILES})
  get_filename_component(EXEC ${TMP_PATH} NAME_WLE)
  add_executable(${EXEC} ${TMP_PATH} ${HEADER_FILES} ${SRC_FILES})

  #target_compile_features(${EXEC} PRIVATE cxx_std_20)
  target_compile_options(${EXEC} PRIVATE -Wall)
  target_compile_options(${EXEC} PRIVATE -pg)

  target_include_directories(${EXEC}
    PUBLIC "${CMAKE_SOURCE_DIR}/src/"
  )
  target_link_libraries(${EXEC} 
    ${OPENGL_LIBRARIES} 
    ${GLFW_LIBRARIES}
    glfw
    GLEW::GLEW
    ${ASSIMP_LIBRARIES} 
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES})
endforeach()

#sudo apt-get install xorg-dev
#sudo apt-get install wget
