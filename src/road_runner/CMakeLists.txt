cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0167 NEW)

project(PathfindingServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Windows-specific settings
if(MSVC)
    add_compile_options(/W4 /MP)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Find Boost with all required components
find_package(Boost 1.70 REQUIRED COMPONENTS 
    system 
    filesystem
    program_options
    thread
)

# Explicitly add Boost include directories
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(include)

add_executable(pathfinding_server 
    src/main.cpp
    src/loading.cpp
    src/Bidirectional_Astar.cpp
    src/graph_loader.cpp
)

target_link_libraries(pathfinding_server PRIVATE 
    ${Boost_LIBRARIES}
)

# Installation rules for Windows
install(TARGETS pathfinding_server
    RUNTIME DESTINATION bin
)

install(FILES "${PROJECT_SOURCE_DIR}/data/USA-roads.csv"
    DESTINATION data
)