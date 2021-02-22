cmake_minimum_required(VERSION 3.0.0)
project(remote-controller VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED 14)

enable_testing()

# set(GCC_COMPILE_FLAGS "-Werror -Wall -Wextra")

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt PROFILE rpi3 ARCH armv7 BASIC_SETUP CMAKE_TARGETS BUILD missing)

link_libraries(stdc++fs)

add_subdirectory(app)
add_subdirectory(lib)