cmake_minimum_required(VERSION 3.20...3.25)

project(
	ISFGLSLGeneratorProject
	VERSION 0.1
	DESCRIPTION "Test rig for some ISF GLSL functionality"
)

# this adds a precompiler macro that source code can use to implement platform-specific implementations (getting home directory)
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	add_definitions(-DMAC=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_definitions(-DLINUX=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "MSYS_NT-6.1")
	add_definitions(-DWIN=1)
endif()

#	look in 'libISFGLSLGenerator' and then 'apps' subdirectories for CMakeLists.txt to process
add_subdirectory(libISFGLSLGenerator)
add_subdirectory(app)
