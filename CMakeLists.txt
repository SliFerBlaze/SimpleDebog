cmake_minimum_required(VERSION 3.20)
project(SimpleDebog LANGUAGES CXX)

# CMake Configuration
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# CMake Options
include(FetchContent)

# Enable Qt features (optional if using .ui or .qrc files)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)

# Find Qt6
# If you uncomment above, you’ll also need this
# find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Fetch external logger
FetchContent_Declare(
    Logger
    GIT_REPOSITORY https://github.com/guigui0246/MyCppLoggerCopy.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(Logger)

# ========== Compiler Flags ==========

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(PROJECT_WARNING_FLAGS
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
    add_compile_options(/W4 /WX /Zi /permissive- /sdl /analyze /wd4100 /wd4201 /wd4505 /wd4251)
endif()

# ========== Sources ==========

# backend/commands/
set(BACKEND_COMMANDS
    src/backend/commands/StepCommand.cpp
    src/backend/commands/BreakpointCommand.cpp
)

# backend/core/
set(BACKEND_CORE
    src/backend/core/DebuggerEngine.cpp
)

# backend/platform/
set(BACKEND_PLATFORM_LINUX
    src/backend/platform/linux/PtraceWrapper.cpp
)

# frontend/
set(FRONTEND
    src/frontend/MainWindow.cpp
    src/frontend/GuiAdapter.cpp
)

# shared/
set(SHARED_UTILS
)

# main entry point
set(MAIN_SRC
    src/main.cpp
)

# ========== Final Build Target ==========

add_executable(SimpleDebog
    ${MAIN_SRC}
    ${BACKEND_CORE}
    # ${BACKEND_COMMANDS}
    # ${BACKEND_PLATFORM_LINUX}
    # ${FRONTEND}
    # ${SHARED_UTILS}
)

target_include_directories(SimpleDebog PRIVATE src/)
target_compile_options(SimpleDebog PRIVATE ${PROJECT_WARNING_FLAGS})

# Link Qt6 and Logger
target_link_libraries(SimpleDebog PRIVATE Qt6::Widgets Logger)

# ========== Testing Setup ==========

enable_testing()
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Test Sources
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

add_executable(SimpleDebogTests
    ${TEST_SOURCES}
    ${BACKEND_CORE}
    # ${BACKEND_COMMANDS}
    # ${SHARED_UTILS}
)

target_include_directories(SimpleDebogTests PRIVATE src/ tests/)
target_compile_options(SimpleDebogTests PRIVATE ${PROJECT_WARNING_FLAGS})

target_link_libraries(SimpleDebogTests
    PRIVATE
    gtest
    gmock
    gtest_main
)

add_test(NAME AllUnitTests COMMAND SimpleDebogTests)
