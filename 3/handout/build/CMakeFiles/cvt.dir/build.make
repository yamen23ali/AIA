# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout/build

# Include any dependencies generated for this target.
include CMakeFiles/cvt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cvt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cvt.dir/flags.make

CMakeFiles/cvt.dir/src/given.cpp.o: CMakeFiles/cvt.dir/flags.make
CMakeFiles/cvt.dir/src/given.cpp.o: ../src/given.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cvt.dir/src/given.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvt.dir/src/given.cpp.o -c /Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout/src/given.cpp

CMakeFiles/cvt.dir/src/given.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvt.dir/src/given.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout/src/given.cpp > CMakeFiles/cvt.dir/src/given.cpp.i

CMakeFiles/cvt.dir/src/given.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvt.dir/src/given.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout/src/given.cpp -o CMakeFiles/cvt.dir/src/given.cpp.s

# Object files for target cvt
cvt_OBJECTS = \
"CMakeFiles/cvt.dir/src/given.cpp.o"

# External object files for target cvt
cvt_EXTERNAL_OBJECTS =

libcvt.a: CMakeFiles/cvt.dir/src/given.cpp.o
libcvt.a: CMakeFiles/cvt.dir/build.make
libcvt.a: CMakeFiles/cvt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcvt.a"
	$(CMAKE_COMMAND) -P CMakeFiles/cvt.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cvt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cvt.dir/build: libcvt.a

.PHONY : CMakeFiles/cvt.dir/build

CMakeFiles/cvt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cvt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cvt.dir/clean

CMakeFiles/cvt.dir/depend:
	cd /Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout /Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout /Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout/build /Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout/build /Users/d070867/Desktop/uni/Subjects/AIA/AIA/3/handout/build/CMakeFiles/cvt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cvt.dir/depend

