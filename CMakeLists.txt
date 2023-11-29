cmake_minimum_required(VERSION 3.10)
project(translucent-keys)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB_RECURSE KEYLOGGER_SOURCE_FILES "src/keylogger/*.cpp")
file(GLOB_RECURSE CLIENT_SOURCE_FILES "src/client/*.cpp")
file(GLOB_RECURSE SERVER_SOURCE_FILES "src/server/*.cpp")

file(GLOB_RECURSE KEYLOGGER_HEADER_FILES "include/keylogger/*.h")
file(GLOB_RECURSE CLIENT_HEADER_FILES "include/client/*.h")
file(GLOB_RECURSE SERVER_HEADER_FILES "include/server/*.h")

file(GLOB_RECURSE COMMON_HEADER_FILES "include/common/*.h")

# Include directories

#TODO: Create a CMakeLists.txt for kqlog to automate this:
include_directories(dependencies/kqlog/include)
include_directories(dependencies/kqlog/vendor/magic_enum/include)
include_directories(dependencies/kqlog/vendor/fmt/include)

#TODO: Create a CMakeLists.txt for kqnet to automate this:
include_directories(dependencies/kqnet/include)
include_directories(dependencies/kqnet/include/kqlib/include)
include_directories(dependencies/kqnet/include/asio/asio/include)

# Add executables
add_executable(keylogger ${KEYLOGGER_SOURCE_FILES} ${KEYLOGGER_HEADER_FILES} ${COMMON_HEADER_FILES})
add_executable(server ${SERVER_SOURCE_FILES} ${SERVER_HEADER_FILES} ${COMMON_HEADER_FILES})
add_executable(client ${CLIENT_SOURCE_FILES} ${CLIENT_HEADER_FILES} ${COMMON_HEADER_FILES})

target_include_directories(keylogger PUBLIC include/keylogger/)
target_include_directories(keylogger PUBLIC include/common/)

target_include_directories(server PUBLIC include/server/)
target_include_directories(server PUBLIC include/common/)

target_include_directories(client PUBLIC include/client/)
target_include_directories(client PUBLIC include/common/)

# Set the output directory for the executables
set_target_properties(keylogger PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties(server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties(client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)