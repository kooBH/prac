# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ffe/git/prac/hpx/2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ffe/git/prac/hpx/2/build

# Include any dependencies generated for this target.
include CMakeFiles/AA.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AA.dir/flags.make

CMakeFiles/AA.dir/main.cpp.o: CMakeFiles/AA.dir/flags.make
CMakeFiles/AA.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ffe/git/prac/hpx/2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AA.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AA.dir/main.cpp.o -c /home/ffe/git/prac/hpx/2/main.cpp

CMakeFiles/AA.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AA.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ffe/git/prac/hpx/2/main.cpp > CMakeFiles/AA.dir/main.cpp.i

CMakeFiles/AA.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AA.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ffe/git/prac/hpx/2/main.cpp -o CMakeFiles/AA.dir/main.cpp.s

CMakeFiles/AA.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/AA.dir/main.cpp.o.requires

CMakeFiles/AA.dir/main.cpp.o.provides: CMakeFiles/AA.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/AA.dir/build.make CMakeFiles/AA.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/AA.dir/main.cpp.o.provides

CMakeFiles/AA.dir/main.cpp.o.provides.build: CMakeFiles/AA.dir/main.cpp.o


# Object files for target AA
AA_OBJECTS = \
"CMakeFiles/AA.dir/main.cpp.o"

# External object files for target AA
AA_EXTERNAL_OBJECTS =

AA: CMakeFiles/AA.dir/main.cpp.o
AA: CMakeFiles/AA.dir/build.make
AA: /usr/local/lib/libhpx_init.a
AA: /usr/local/lib/libhpx_wrap.a
AA: /usr/local/lib/libhpx_init.a
AA: /usr/local/lib/libhpx.so.1.3.0
AA: /usr/local/lib/libboost_filesystem.so
AA: /usr/local/lib/libboost_program_options.so
AA: /usr/local/lib/libboost_system.so
AA: /usr/lib/x86_64-linux-gnu/libpthread.so
AA: /usr/local/lib/libboost_filesystem.so
AA: /usr/local/lib/libboost_program_options.so
AA: /usr/local/lib/libboost_system.so
AA: /usr/local/lib/libboost_regex.so
AA: /usr/local/lib/libhwloc.so
AA: /usr/lib/x86_64-linux-gnu/libpthread.so
AA: /usr/local/lib/libboost_regex.so
AA: /usr/local/lib/libhwloc.so
AA: CMakeFiles/AA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ffe/git/prac/hpx/2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AA"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AA.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AA.dir/build: AA

.PHONY : CMakeFiles/AA.dir/build

CMakeFiles/AA.dir/requires: CMakeFiles/AA.dir/main.cpp.o.requires

.PHONY : CMakeFiles/AA.dir/requires

CMakeFiles/AA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AA.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AA.dir/clean

CMakeFiles/AA.dir/depend:
	cd /home/ffe/git/prac/hpx/2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ffe/git/prac/hpx/2 /home/ffe/git/prac/hpx/2 /home/ffe/git/prac/hpx/2/build /home/ffe/git/prac/hpx/2/build /home/ffe/git/prac/hpx/2/build/CMakeFiles/AA.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AA.dir/depend
