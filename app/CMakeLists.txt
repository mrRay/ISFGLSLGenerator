cmake_minimum_required(VERSION 3.20...3.25)

add_executable(ISFGLSLGeneratorTestApp main.cpp)

target_link_libraries(ISFGLSLGeneratorTestApp PRIVATE ISFGLSLGenerator)

target_compile_features(ISFGLSLGeneratorTestApp PUBLIC cxx_std_20)
