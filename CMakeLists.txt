cmake_minimum_required(VERSION 3.21)
project(CoordinatorAssistant LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# wxWidgets via vcpkg
find_package(wxWidgets CONFIG REQUIRED COMPONENTS core base)

add_executable(CoordinatorAssistant WIN32
    src/App.cpp
    src/App.h
    src/MainFrame.cpp
    src/MainFrame.h
 "src/core/Helpers.cpp" "src/core/Helpers.h"  "src/core/Defaults.h" "src/core/Defaults.cpp")

target_link_libraries(CoordinatorAssistant PRIVATE wx::core wx::base)
target_include_directories(CoordinatorAssistant PRIVATE src)
