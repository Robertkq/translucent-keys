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

file(GLOB_RECURSE KEYBOARD_MANAGER_HEADER_FILES "include/keyboardManager/*.h")
file(GLOB_RECURSE KEYBOARD_MANAGER_SOURCE_FILES "src/keyboardManager/*.cpp")

file(GLOB_RECURSE COMMON_HEADER_FILES "include/common/*.h")

file(GLOB_RECURSE KQNET_HEADER_FILES "dependencies/kqnet/*.h*")
file(GLOB_RECURSE KQLOG_HEADER_FILES "dependencies/kqlog/*.h*")

set(IMGUI_SOURCE_FILES
"dependencies/imgui/imgui.cpp"
"dependencies/imgui/imgui_draw.cpp"
"dependencies/imgui/imgui_tables.cpp"
"dependencies/imgui/imgui_widgets.cpp"
)
set(IMGUI_HEADER_FILES 
"dependencies/imgui/imconfig.h"
"dependencies/imgui/imgui_internal.h"
"dependencies/imgui/imgui.h"
)

add_executable(keylogger ${KEYLOGGER_SOURCE_FILES}  ${KEYLOGGER_HEADER_FILES}   ${COMMON_HEADER_FILES})
add_executable(server ${SERVER_SOURCE_FILES}        ${SERVER_HEADER_FILES}      ${KEYBOARD_MANAGER_HEADER_FILES} ${KEYBOARD_MANAGER_SOURCE_FILES} ${COMMON_HEADER_FILES})
add_executable(client ${CLIENT_SOURCE_FILES}        ${CLIENT_HEADER_FILES}      ${KEYBOARD_MANAGER_HEADER_FILES} ${KEYBOARD_MANAGER_SOURCE_FILES} ${COMMON_HEADER_FILES})

add_library(kqnet INTERFACE ${KQNET_HEADER_FILES})
target_include_directories(kqnet INTERFACE 
dependencies/kqnet/include/
dependencies/kqnet/include/kqlib/include/
dependencies/kqnet/include/asio/asio/include
)

add_library(kqlog INTERFACE ${KQLOG_HEADER_FILES})
target_include_directories(kqlog INTERFACE
dependencies/kqlog/include
dependencies/kqlog/vendor/magic_enum/include
dependencies/kqlog/vendor/fmt/include
)

add_library(imgui_lib STATIC ${IMGUI_SOURCE_FILES} ${IMGUI_HEADER_FILES})
target_include_directories(imgui_lib PUBLIC dependencies/imgui/)

target_include_directories(keylogger PUBLIC include/keylogger/)
target_include_directories(keylogger PUBLIC include/common/)

target_include_directories(server PUBLIC include/keyboardManager/)
target_include_directories(server PUBLIC include/server/)
target_include_directories(server PUBLIC include/common/)

target_include_directories(client PUBLIC include/keyboardManager/)
target_include_directories(client PUBLIC include/client/)
target_include_directories(client PUBLIC include/common/)

target_link_libraries(keylogger PUBLIC kqnet)
target_link_libraries(keylogger PUBLIC kqlog)

target_link_libraries(server PUBLIC kqnet)
target_link_libraries(server PUBLIC kqlog)

target_link_libraries(client PUBLIC kqnet)
target_link_libraries(client PUBLIC kqlog)

target_link_libraries(client PUBLIC imgui_lib)
target_link_libraries(server PUBLIC imgui_lib)

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