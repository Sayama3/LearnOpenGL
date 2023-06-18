cmake_minimum_required(VERSION 3.24)
project(LearnOpenGL)

add_subdirectory(glfw)
target_link_libraries(OpenGL PUBLIC glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(OpenGL PUBLIC OpenGL::GL)

add_subdirectory(glm)
target_link_libraries(OpenGL PUBLIC glm)

# set variables that are needed
set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS ON)
#set(ASSIMP_WARNINGS_AS_ERRORS OFF)
set(USE_SYSTEM_ASSIMP ON)

add_subdirectory(assimp)
target_link_libraries(OpenGL PUBLIC assimp)