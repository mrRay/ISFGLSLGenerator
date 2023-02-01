cmake_minimum_required(VERSION 3.11-3.18)

project(ISFGLSLGeneratorTestApp)

# this adds a precompiler macro that source code can use to implement platform-specific implementations (getting home directory)
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	add_definitions(-DMAC=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_definitions(-DLINUX=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "MSYS_NT-6.1")
	add_definitions(-DWIN=1)
endif()

add_executable(ISFGLSLGeneratorTestApp main.cpp)

target_link_libraries(ISFGLSLGeneratorTestApp PRIVATE ISFGLSLGenerator)

target_compile_features(ISFGLSLGeneratorTestApp PUBLIC cxx_std_20)
