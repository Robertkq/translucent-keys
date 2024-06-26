cmake_minimum_required(VERSION 3.10)
project(translucent-keys)

file(TO_CMAKE_PATH "$ENV{KQLOG_LIBRARY_PATH}" KQLOG_PATH )
file(TO_CMAKE_PATH "$ENV{KQNET_LIBRARY_PATH}" KQNET_PATH )
file(TO_CMAKE_PATH "$ENV{IMGUI_LIBRARY_PATH}" IMGUI_PATH )

message(STATUS "KQLOG_PATH: ${KQLOG_PATH}")
message(STATUS "KQNET_PATH: ${KQNET_PATH}")
message(STATUS "IMGUI_PATH: ${IMGUI_PATH}")

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

file(GLOB_RECURSE NAME_TAKER_HEADER_FILES "include/nameTaker/*.h")
file(GLOB_RECURSE NAME_TAKER_SOURCE_FILES "src/nameTaker/*.cpp")

file(GLOB_RECURSE COMMON_HEADER_FILES "include/common/*.h")

file(GLOB_RECURSE KQNET_HEADER_FILES "${KQNET_PATH}/*.h*")
file(GLOB_RECURSE KQLOG_HEADER_FILES "${KQLOG_PATH}/*.h*")

set(IMGUI_SOURCE_FILES
"${IMGUI_PATH}/imgui.cpp"
"${IMGUI_PATH}/imgui_draw.cpp"
"${IMGUI_PATH}/imgui_tables.cpp"
"${IMGUI_PATH}/imgui_widgets.cpp"
"${IMGUI_PATH}/backends/imgui_impl_win32.cpp"
"${IMGUI_PATH}/backends/imgui_impl_dx11.cpp"
"src/common/imgui_init.cpp"
)

add_executable(keylogger ${KEYLOGGER_SOURCE_FILES} ${NAME_TAKER_SOURCE_FILES})
add_executable(server ${SERVER_SOURCE_FILES})
add_executable(client ${CLIENT_SOURCE_FILES})

set_target_properties(keylogger PROPERTIES
    LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
    LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE"
)

add_library(kqnet INTERFACE ${KQNET_HEADER_FILES})
target_include_directories(kqnet INTERFACE 
${KQNET_PATH}/include/
${KQNET_PATH}/include/kqlib/include/
${KQNET_PATH}/include/asio/asio/include
)

add_library(imgui STATIC ${IMGUI_SOURCE_FILES})
target_include_directories(imgui PUBLIC ${IMGUI_PATH}/)
target_include_directories(imgui PUBLIC ${IMGUI_PATH}/backends/)
target_include_directories(imgui PUBLIC include/common/)
target_link_libraries(imgui PUBLIC d3d11)

target_include_directories(keylogger PUBLIC include/keylogger/)
target_include_directories(keylogger PUBLIC include/nameTaker/)
target_include_directories(keylogger PUBLIC include/common/)

target_include_directories(server PUBLIC include/keyboardManager/)
target_include_directories(server PUBLIC include/server/)
target_include_directories(server PUBLIC include/common/)

target_include_directories(client PUBLIC include/keyboardManager/)
target_include_directories(client PUBLIC include/client/)
target_include_directories(client PUBLIC include/common/)

target_link_libraries(keylogger PUBLIC kqnet)
target_link_libraries(server PUBLIC kqnet)
target_link_libraries(client PUBLIC kqnet)

target_link_libraries(client PUBLIC imgui)

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