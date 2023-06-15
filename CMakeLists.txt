cmake_minimum_required(VERSION 3.25)

# set enable the debugger (when the debug mode is enable?)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

# for visual studio : enable the math define
# Remove because assimp already include the "_USE_MATH_DEFINES" preprocessor
#add_definitions(-D_USE_MATH_DEFINES)

# we use the c++ 20
set(CMAKE_CXX_STANDARD 20)

project(LearnOpenGL)

add_executable(OpenGL include/SystemHelper.hpp)

# remark the c++ version to the 20 one
target_compile_features(OpenGL PUBLIC cxx_std_20)

# add the .hpp to the projects
include_directories(include)
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(resources)