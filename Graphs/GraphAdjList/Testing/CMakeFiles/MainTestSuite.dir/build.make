# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing

# Include any dependencies generated for this target.
include CMakeFiles/MainTestSuite.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MainTestSuite.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MainTestSuite.dir/flags.make

CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o: CMakeFiles/MainTestSuite.dir/flags.make
CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o: MainTestSuite.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o -c /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing/MainTestSuite.cpp

CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing/MainTestSuite.cpp > CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.i

CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing/MainTestSuite.cpp -o CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.s

CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o.requires:
.PHONY : CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o.requires

CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o.provides: CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o.requires
	$(MAKE) -f CMakeFiles/MainTestSuite.dir/build.make CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o.provides.build
.PHONY : CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o.provides

CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o.provides.build: CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o

# Object files for target MainTestSuite
MainTestSuite_OBJECTS = \
"CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o"

# External object files for target MainTestSuite
MainTestSuite_EXTERNAL_OBJECTS =

MainTestSuite: CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o
MainTestSuite: CMakeFiles/MainTestSuite.dir/build.make
MainTestSuite: /usr/lib/libgtest.a
MainTestSuite: CMakeFiles/MainTestSuite.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable MainTestSuite"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MainTestSuite.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MainTestSuite.dir/build: MainTestSuite
.PHONY : CMakeFiles/MainTestSuite.dir/build

CMakeFiles/MainTestSuite.dir/requires: CMakeFiles/MainTestSuite.dir/MainTestSuite.cpp.o.requires
.PHONY : CMakeFiles/MainTestSuite.dir/requires

CMakeFiles/MainTestSuite.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MainTestSuite.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MainTestSuite.dir/clean

CMakeFiles/MainTestSuite.dir/depend:
	cd /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing /home/jhallard/DataStructures/Graphs/GraphAdjList/Testing/CMakeFiles/MainTestSuite.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MainTestSuite.dir/depend

