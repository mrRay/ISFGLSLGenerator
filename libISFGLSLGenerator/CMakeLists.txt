cmake_minimum_required(VERSION 3.11-3.18)

project (ISFGLSLGenerator)

# this adds a precompiler macro that source code can use to implement platform-specific implementations (getting home directory)
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	add_definitions(-DMAC=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_definitions(-DLINUX=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "MSYS_NT-6.1")
	add_definitions(-DWIN=1)
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS True)

#add_compile_options("-stdlib=libc++" "-v" "-DLLVM_ENABLE_PROJECTS=\"clang\"" "-DLLVM_ENABLE_RUNTIMES=\"libcxx;libcxxabi\"")
#add_compile_options("-stdlib=libc++" "-std=c++20" "-v" "-DLLVM_ENABLE_PROJECTS=clang" "-DLLVM_ENABLE_RUNTIMES=libcxx,libcxxabi")
#add_compile_options ("-Wall")
add_compile_options ("-v")

add_library(ISFGLSLGenerator STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/ISFAttr.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ISFDoc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ISFPassTarget.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ISFVal.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/VVISF_Base.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/VVISF_StringUtils.cpp
)

#target_include_directories(ISFGLSLGenerator PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_include_directories(ISFGLSLGenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_include_directories(ISFGLSLGenerator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/exprtk)
#target_include_directories(ISFGLSLGenerator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann_json)

#target_include_directories( ISFGLSLGenerator PUBLIC
#	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#	$<INSTALL_INTERFACE:include>
#	)

target_compile_features(ISFGLSLGenerator PUBLIC cxx_std_20)
