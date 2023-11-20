cmake_minimum_required(VERSION 3.10)
project(translucent-keys)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Include directories
include_directories(include)

# Add executable
add_executable(translucent-keys ${SOURCE_FILES})

# Set the output directory for the executable
set_target_properties(translucent-keys PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)