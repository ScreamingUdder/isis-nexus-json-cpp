cmake_minimum_required(VERSION 3.5)
project(nexus_json_cpp)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

SET(CONAN_PROFILE "default" CACHE STRING "Name of conan profile to use, uses default by default")
include(${CMAKE_MODULE_PATH}/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt
        PROFILE ${CONAN_PROFILE}
        BASIC_SETUP
        BUILD_TYPE "None"
        BUILD outdated)

add_executable(nexus_json_cpp main.cpp)
