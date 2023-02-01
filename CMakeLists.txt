cmake_minimum_required(VERSION 3.11-3.18)

project(
	ISFGLSLGeneratorProject
	VERSION 0.1
	DESCRIPTION "Test rig for some ISF GLSL functionality"
)

#	look in 'libISFGLSLGenerator' and then 'apps' subdirectories for CMakeLists.txt to process
add_subdirectory(libISFGLSLGenerator)
add_subdirectory(app)
