cmake_minimum_required(VERSION 3.12)
project(Graphics)

set(CMAKE_CXX_STANDARD 14)

set(GLEW_H /usr/local/Cellar/glew/2.1.0/include)
set(GLFW_H /usr/local/Cellar/glfw/3.3/include)
set(GLAD_H glad/include)
set(GLM_H /usr/local/Cellar/glm/0.9.9.5/include)
set(ASSIMP_H /usr/local/Cellar/assimp/4.1.0/include)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${GLM_H} ${ASSIMP_H})

aux_source_directory(./aux DIR_SRCS)

set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3/lib/libglfw.3.3.dylib)
set(ASSIMP_LINK /usr/local/Cellar/assimp/4.1.0/lib/libassimp.4.1.0.dylib)

link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${ASSIMP_LINK})

set(SOURCE_FILES "main.cpp" "glad/src/glad.c" ${DIR_SRCS} class/block.h class/block.cpp)
add_executable(Graphics ${SOURCE_FILES})
if (APPLE)
target_link_libraries(Graphics "-framework OpenGL")
target_link_libraries(Graphics "-framework GLUT")
endif()
 