cmake_minimum_required(VERSION 3.20)
project(SimpleDebog LANGUAGES CXX)

# CMake Configuration
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# CMake Options
include(FetchContent)

# Enable Qt features
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)

# Find Qt6
# find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Find Logger
FetchContent_Declare(
    Logger
    GIT_REPOSITORY https://github.com/guigui0246/MyCppLoggerCopy.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(Logger)

# Enable strict compiler flags
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

# backend/events/

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
    # ${BACKEND_COMMANDS}
    # ${BACKEND_CORE}
    # ${BACKEND_PLATFORM_LINUX}
    # ${FRONTEND}
    # ${SHARED_UTILS}
)

# Include full source tree for includes
target_include_directories(SimpleDebog PRIVATE src/)

# Link Qt
# target_link_libraries(SimpleDebog PRIVATE Qt6::Widgets)

# Link Logger
target_link_libraries(SimpleDebog PRIVATE Logger)
# get_target_property(LOGGER_DLL_PATH Logger LIBRARY_OUTPUT_DIRECTORY)
# message(STATUS "Logger DLL Path: ${LOGGER_DLL_PATH}")
# message(STATUS "Logger DLL Path: $<BUILD_INTERFACE:${LOGGER_DLL_PATH}>")
# set_target_properties(SimpleDebog PROPERTIES
#     INSTALL_RPATH "$<BUILD_INTERFACE:${LOGGER_DLL_PATH}>"
#     BUILD_RPATH "$<BUILD_INTERFACE:${LOGGER_DLL_PATH}>"
# )
