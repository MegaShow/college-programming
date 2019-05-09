# CMakeList.txt: OpenGL 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required(VERSION 3.8)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
if (DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
    set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}")
endif()

project(OpenGL)

message("CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")

find_package(assimp CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

configure_file("configuration/root_directory.h.in" "configuration/root_directory.h")
file(COPY "OpenGL.vs.glsl" "OpenGL.fs.glsl" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "resources" DESTINATION ${CMAKE_BINARY_DIR})

include_directories("${CMAKE_BINARY_DIR}/configuration")
include_directories("./")

add_executable(OpenGL "OpenGL.cpp" "stb_image.cpp")

target_link_libraries(OpenGL PRIVATE ${ASSIMP_LIBRARIES})
target_link_libraries(OpenGL PRIVATE glad::glad)
target_link_libraries(OpenGL PRIVATE glfw)
target_link_libraries(OpenGL PRIVATE glm)
