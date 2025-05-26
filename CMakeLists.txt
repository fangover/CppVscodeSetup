cmake_minimum_required(VERSION 3.20)
project(CPPSetup_Project)

# Set C++ standard and compiler flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set a clean base output directory
set(CLEAN_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)

# Set specific output folders for different types of targets
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CLEAN_OUTPUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CLEAN_OUTPUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CLEAN_OUTPUT_DIR}/bin)

# Optional: handle multi-config generators (like Visual Studio)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CLEAN_OUTPUT_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CLEAN_OUTPUT_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CLEAN_OUTPUT_DIR}/bin)
endforeach()



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
    ExternalLib/EResult/include
    ExternalLib/FileStream/include
    ExternalLib/Logs/include
    # Add other external libraries here
)

# Find all source files
file(GLOB_RECURSE SOURCES
    "MainApp/source/*.cpp"
    "ExternalLib/FileStream/source/*.cpp"
    "ExternalLib/Logs/source/*.cpp"
    "CppExamples/ModuleExample/source/*.cpp"

    # Add other source directories here
)

# Create executable
add_executable(main ${SOURCES})