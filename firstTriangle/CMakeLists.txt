cmake_minimum_required(VERSION 3.5.0)
project(openglTutorial VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

include(CTest)
enable_testing()

find_package(OpenGL REQUIRED)

add_executable(openglTutorial 
	src/main.cpp 
	hdr/glad.h 
	src/glad.c)

target_link_libraries(openglTutorial 
	glfw
	OpenGL::GL)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
