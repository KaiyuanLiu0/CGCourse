cmake_minimum_required(VERSION 3.12)
project(Graphics)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)


set(GLAD_H glad/include)
set(INCLUDE include)
include_directories(${INCLUDE} ${GLAD_H})

aux_source_directory(./src DIR_SRCS)

if (APPLE)
set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3/lib/libglfw.3.3.dylib)
set(ASSIMP_LINK /usr/local/Cellar/assimp/4.1.0/lib/libassimp.4.1.0.dylib)

link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${ASSIMP_LINK})
endif()

if (WIN32)
LINK_DIRECTORIES("./lib")
endif()

set(SOURCE_FILES "main.cpp" "glad/src/glad.c" ${DIR_SRCS} class/block.h class/block.cpp class/map.cpp class/map.h class/type.h class/skybox.cpp class/skybox.h class/box.cpp class/box.h class/light.cpp class/light.h class/plane.cpp class/plane.h)
add_executable(Graphics ${SOURCE_FILES})
if (APPLE)
target_link_libraries(Graphics "-framework OpenGL")
target_link_libraries(Graphics "-framework GLUT")
endif()
if (WIN32)
target_link_libraries(Graphics "glfw3dll")
endif()
 