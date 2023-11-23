cmake_minimum_required(VERSION 3.5.0)
project(OpenGLTextures VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(OpenGLTextures 
	src/main.cpp
	hdr/glad.h
	src/glad.c
	hdr/Shader.hpp
	src/Shader.cpp
	hdr/stb_image.h
	src/stb_image.cpp)

target_link_libraries(OpenGLTextures
	glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
