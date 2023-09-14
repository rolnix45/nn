cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_COMPILER             "clang++")
set(CMAKE_CXX_FLAGS                "-Wall -std=c++2b")
set(CMAKE_CXX_FLAGS_DEBUG          "-gfull")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(nn VERSION 0.1)

find_package(bgfx REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(engine/include game/include ${BGFX_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIRS})
file(GLOB_RECURSE _sources
    "engine/**/*.hpp"
    "engine/**/*.cpp"
    "game/**/*.hpp"
    "game/**/*.cpp"
    "main.cpp"
)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)

add_executable(${PROJECT_NAME} ${_sources})
add_dependencies(${PROJECT_NAME} copy_assets)
target_link_libraries(${PROJECT_NAME}
    bgfx::bgfx
    glfw
    assimp.dll
    fmt
)