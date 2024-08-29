cmake_minimum_required(VERSION 3.27)
project(FinalProjectCPP)

set(CMAKE_CXX_STANDARD 17)

# Add ImGui source files to your project
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/lib/imgui)  # Update with the correct path to ImGui

set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
)

# Add ImGui source files
add_library(ImGui STATIC ${IMGUI_SOURCES})

# Include directories for ImGui
target_include_directories(ImGui PRIVATE ${IMGUI_DIR})

include_directories("/lib/httplib")
include_directories("lib/json/single_include/nlohmann/json.hpp")
include_directories("lib/imgui")
#include_directories("lib/glfw/include/GLFW/glfw3.h")
#include_directories("lib/glfw/include/GLFW/glfw3native.h")

# Link against the Winsock library
add_executable(FinalProjectCPP main.cpp
        weather.cpp
        weather.h
        UI.cpp
        UI.h)

target_link_libraries(FinalProjectCPP PRIVATE ws2_32)
target_link_libraries(FinalProjectCPP PRIVATE ImGui)
#target_link_libraries(FinalProjectCPP PRIVATE glfw)

