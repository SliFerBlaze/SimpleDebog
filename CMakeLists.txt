cmake_minimum_required(VERSION 3.20)
project(SimpleDebog LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Enable strict compiler flags (optional)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        -Wall -Wextra -Wpedantic -Werror
        -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
        -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion
        -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough
        -Wstrict-overflow=5 -Wstrict-aliasing=3 -Wuseless-cast -Wlogical-op
        -Wduplicated-cond -Wduplicated-branches -Wrestrict -Wnull-dereference
        -Walloca -Wzero-as-null-pointer-constant -Wswitch-enum -Wstack-protector
        -Wtrampolines -Wvector-operation-performance
        -Wundef -Wredundant-decls -Wfloat-equal -Wcast-qual
        -g
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX /Zi /permissive- /sdl /analyze /wd4100 /wd4201)
endif()

# Main executable
add_executable(SimpleDebog src/main.cpp src/Trace.cpp)
target_include_directories(SimpleDebog PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(SimpleDebog PRIVATE Qt6::Widgets)

