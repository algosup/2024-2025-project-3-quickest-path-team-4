# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ian/Desktop/road_runner

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ian/Desktop/road_runner/build

# Include any dependencies generated for this target.
include CMakeFiles/pathfinding_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pathfinding_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pathfinding_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pathfinding_server.dir/flags.make

CMakeFiles/pathfinding_server.dir/codegen:
.PHONY : CMakeFiles/pathfinding_server.dir/codegen

CMakeFiles/pathfinding_server.dir/src/main.cpp.o: CMakeFiles/pathfinding_server.dir/flags.make
CMakeFiles/pathfinding_server.dir/src/main.cpp.o: /Users/ian/Desktop/road_runner/src/main.cpp
CMakeFiles/pathfinding_server.dir/src/main.cpp.o: CMakeFiles/pathfinding_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ian/Desktop/road_runner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pathfinding_server.dir/src/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pathfinding_server.dir/src/main.cpp.o -MF CMakeFiles/pathfinding_server.dir/src/main.cpp.o.d -o CMakeFiles/pathfinding_server.dir/src/main.cpp.o -c /Users/ian/Desktop/road_runner/src/main.cpp

CMakeFiles/pathfinding_server.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pathfinding_server.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ian/Desktop/road_runner/src/main.cpp > CMakeFiles/pathfinding_server.dir/src/main.cpp.i

CMakeFiles/pathfinding_server.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pathfinding_server.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ian/Desktop/road_runner/src/main.cpp -o CMakeFiles/pathfinding_server.dir/src/main.cpp.s

CMakeFiles/pathfinding_server.dir/src/loading.cpp.o: CMakeFiles/pathfinding_server.dir/flags.make
CMakeFiles/pathfinding_server.dir/src/loading.cpp.o: /Users/ian/Desktop/road_runner/src/loading.cpp
CMakeFiles/pathfinding_server.dir/src/loading.cpp.o: CMakeFiles/pathfinding_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ian/Desktop/road_runner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/pathfinding_server.dir/src/loading.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pathfinding_server.dir/src/loading.cpp.o -MF CMakeFiles/pathfinding_server.dir/src/loading.cpp.o.d -o CMakeFiles/pathfinding_server.dir/src/loading.cpp.o -c /Users/ian/Desktop/road_runner/src/loading.cpp

CMakeFiles/pathfinding_server.dir/src/loading.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pathfinding_server.dir/src/loading.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ian/Desktop/road_runner/src/loading.cpp > CMakeFiles/pathfinding_server.dir/src/loading.cpp.i

CMakeFiles/pathfinding_server.dir/src/loading.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pathfinding_server.dir/src/loading.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ian/Desktop/road_runner/src/loading.cpp -o CMakeFiles/pathfinding_server.dir/src/loading.cpp.s

CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.o: CMakeFiles/pathfinding_server.dir/flags.make
CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.o: /Users/ian/Desktop/road_runner/src/Bidirectional_Astar.cpp
CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.o: CMakeFiles/pathfinding_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ian/Desktop/road_runner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.o -MF CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.o.d -o CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.o -c /Users/ian/Desktop/road_runner/src/Bidirectional_Astar.cpp

CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ian/Desktop/road_runner/src/Bidirectional_Astar.cpp > CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.i

CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ian/Desktop/road_runner/src/Bidirectional_Astar.cpp -o CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.s

CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.o: CMakeFiles/pathfinding_server.dir/flags.make
CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.o: /Users/ian/Desktop/road_runner/src/graph_loader.cpp
CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.o: CMakeFiles/pathfinding_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ian/Desktop/road_runner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.o -MF CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.o.d -o CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.o -c /Users/ian/Desktop/road_runner/src/graph_loader.cpp

CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ian/Desktop/road_runner/src/graph_loader.cpp > CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.i

CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ian/Desktop/road_runner/src/graph_loader.cpp -o CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.s

# Object files for target pathfinding_server
pathfinding_server_OBJECTS = \
"CMakeFiles/pathfinding_server.dir/src/main.cpp.o" \
"CMakeFiles/pathfinding_server.dir/src/loading.cpp.o" \
"CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.o" \
"CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.o"

# External object files for target pathfinding_server
pathfinding_server_EXTERNAL_OBJECTS =

pathfinding_server: CMakeFiles/pathfinding_server.dir/src/main.cpp.o
pathfinding_server: CMakeFiles/pathfinding_server.dir/src/loading.cpp.o
pathfinding_server: CMakeFiles/pathfinding_server.dir/src/Bidirectional_Astar.cpp.o
pathfinding_server: CMakeFiles/pathfinding_server.dir/src/graph_loader.cpp.o
pathfinding_server: CMakeFiles/pathfinding_server.dir/build.make
pathfinding_server: /opt/homebrew/lib/libboost_filesystem.dylib
pathfinding_server: /opt/homebrew/lib/libboost_program_options.dylib
pathfinding_server: /opt/homebrew/lib/libboost_thread.dylib
pathfinding_server: /opt/homebrew/lib/libboost_system.dylib
pathfinding_server: /opt/homebrew/lib/libboost_atomic.dylib
pathfinding_server: CMakeFiles/pathfinding_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ian/Desktop/road_runner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable pathfinding_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pathfinding_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pathfinding_server.dir/build: pathfinding_server
.PHONY : CMakeFiles/pathfinding_server.dir/build

CMakeFiles/pathfinding_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pathfinding_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pathfinding_server.dir/clean

CMakeFiles/pathfinding_server.dir/depend:
	cd /Users/ian/Desktop/road_runner/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ian/Desktop/road_runner /Users/ian/Desktop/road_runner /Users/ian/Desktop/road_runner/build /Users/ian/Desktop/road_runner/build /Users/ian/Desktop/road_runner/build/CMakeFiles/pathfinding_server.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/pathfinding_server.dir/depend

