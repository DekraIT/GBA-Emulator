# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (hello_cmake)

file(GLOB SOURCES "src/*.c")

# Add an executable
add_executable(gba-emu ${SOURCES})

target_include_directories(gba-emu
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)