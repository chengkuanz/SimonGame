# CMakeList.txt : CMake project for SimonGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("SimonGame")

# Add source to this project's executable.
add_executable (SimonGame "SimonGame.cpp" "SimonGame.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SimonGame PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_include_directories(SimonGame PUBLIC "./include")
target_link_directories(SimonGame PUBLIC "./lib")
target_link_libraries(SimonGame sfml-graphics-d sfml-main-d  sfml-system-d sfml-window-d tgui-d sfml-audio-d)
