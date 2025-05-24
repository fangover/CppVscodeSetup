cmake_minimum_required(VERSION 3.20)
project(CPPSetup_Project)

# Set C++ standard and compiler flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Add compiler flags
add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wunused-parameter
    -pedantic
    -fexec-charset=UTF-8
    -fdiagnostics-color=always
)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}  # Add project root to includes
    MainApp/include
    ExternalLib/CopyElision/include
    ExternalLib/ModuleExample/include
    # Add other external libraries here
)

# Find all source files
file(GLOB_RECURSE SOURCES
    "MainApp/source/*.cpp"
    "ExternalLib/ModuleExample/source/*.cpp"
    "ExternalLib/FileStream/source/*.cpp"
    # Add other source directories here
)

# Create executable
add_executable(main ${SOURCES})