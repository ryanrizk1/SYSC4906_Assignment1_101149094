# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build

# Include any dependencies generated for this target.
include main/CMakeFiles/sample_project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include main/CMakeFiles/sample_project.dir/compiler_depend.make

# Include the progress variables for this target.
include main/CMakeFiles/sample_project.dir/progress.make

# Include the compile flags for this target's objects.
include main/CMakeFiles/sample_project.dir/flags.make

main/CMakeFiles/sample_project.dir/main.cpp.o: main/CMakeFiles/sample_project.dir/flags.make
main/CMakeFiles/sample_project.dir/main.cpp.o: /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/main/main.cpp
main/CMakeFiles/sample_project.dir/main.cpp.o: main/CMakeFiles/sample_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object main/CMakeFiles/sample_project.dir/main.cpp.o"
	cd /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build/main && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT main/CMakeFiles/sample_project.dir/main.cpp.o -MF CMakeFiles/sample_project.dir/main.cpp.o.d -o CMakeFiles/sample_project.dir/main.cpp.o -c /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/main/main.cpp

main/CMakeFiles/sample_project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sample_project.dir/main.cpp.i"
	cd /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build/main && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/main/main.cpp > CMakeFiles/sample_project.dir/main.cpp.i

main/CMakeFiles/sample_project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sample_project.dir/main.cpp.s"
	cd /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build/main && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/main/main.cpp -o CMakeFiles/sample_project.dir/main.cpp.s

# Object files for target sample_project
sample_project_OBJECTS = \
"CMakeFiles/sample_project.dir/main.cpp.o"

# External object files for target sample_project
sample_project_EXTERNAL_OBJECTS =

/home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/bin/sample_project: main/CMakeFiles/sample_project.dir/main.cpp.o
/home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/bin/sample_project: main/CMakeFiles/sample_project.dir/build.make
/home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/bin/sample_project: main/CMakeFiles/sample_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/bin/sample_project"
	cd /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build/main && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sample_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
main/CMakeFiles/sample_project.dir/build: /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/bin/sample_project
.PHONY : main/CMakeFiles/sample_project.dir/build

main/CMakeFiles/sample_project.dir/clean:
	cd /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build/main && $(CMAKE_COMMAND) -P CMakeFiles/sample_project.dir/cmake_clean.cmake
.PHONY : main/CMakeFiles/sample_project.dir/clean

main/CMakeFiles/sample_project.dir/depend:
	cd /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/main /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build/main /home/ryanrizk/SYSC4906/Assignment1/blank_project_rt/build/main/CMakeFiles/sample_project.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : main/CMakeFiles/sample_project.dir/depend

