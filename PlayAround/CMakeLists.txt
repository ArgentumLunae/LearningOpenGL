cmake_minimum_required(VERSION 3.5.0)
project(OpenGLTranslations VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(OpenGLTranslations 
	src/main.cpp
	hdr/glad.h
	src/glad.c
	hdr/Shader.hpp
	src/Shader.cpp
	hdr/stb_image.h
	src/stb_image.cpp
	hdr/Camera.hpp
	src/Camera.cpp)

target_link_libraries(OpenGLTranslations
	glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
