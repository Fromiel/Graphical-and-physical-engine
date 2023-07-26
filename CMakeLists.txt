cmake_minimum_required (VERSION 3.8)

project(GameEngine)

# Include CMakeLists.txt from folder "Engine"
add_subdirectory(Engine)

# Include CMakeLists.txt from folder "Game"
add_subdirectory(Game)

#Tests
enable_testing()

add_subdirectory(Tests)