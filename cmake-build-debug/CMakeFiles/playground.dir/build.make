# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = "/Users/zw/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/171.4073.41/CLion.app/Contents/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/Users/zw/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/171.4073.41/CLion.app/Contents/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zw/code/C++_Projects/PlaneFinder

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zw/code/C++_Projects/PlaneFinder/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/playground.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/playground.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/playground.dir/flags.make

CMakeFiles/playground.dir/playground.cpp.o: CMakeFiles/playground.dir/flags.make
CMakeFiles/playground.dir/playground.cpp.o: ../playground.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zw/code/C++_Projects/PlaneFinder/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/playground.dir/playground.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/playground.dir/playground.cpp.o -c /Users/zw/code/C++_Projects/PlaneFinder/playground.cpp

CMakeFiles/playground.dir/playground.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/playground.dir/playground.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zw/code/C++_Projects/PlaneFinder/playground.cpp > CMakeFiles/playground.dir/playground.cpp.i

CMakeFiles/playground.dir/playground.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/playground.dir/playground.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zw/code/C++_Projects/PlaneFinder/playground.cpp -o CMakeFiles/playground.dir/playground.cpp.s

CMakeFiles/playground.dir/playground.cpp.o.requires:

.PHONY : CMakeFiles/playground.dir/playground.cpp.o.requires

CMakeFiles/playground.dir/playground.cpp.o.provides: CMakeFiles/playground.dir/playground.cpp.o.requires
	$(MAKE) -f CMakeFiles/playground.dir/build.make CMakeFiles/playground.dir/playground.cpp.o.provides.build
.PHONY : CMakeFiles/playground.dir/playground.cpp.o.provides

CMakeFiles/playground.dir/playground.cpp.o.provides.build: CMakeFiles/playground.dir/playground.cpp.o


CMakeFiles/playground.dir/SimplePly.cpp.o: CMakeFiles/playground.dir/flags.make
CMakeFiles/playground.dir/SimplePly.cpp.o: ../SimplePly.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zw/code/C++_Projects/PlaneFinder/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/playground.dir/SimplePly.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/playground.dir/SimplePly.cpp.o -c /Users/zw/code/C++_Projects/PlaneFinder/SimplePly.cpp

CMakeFiles/playground.dir/SimplePly.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/playground.dir/SimplePly.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zw/code/C++_Projects/PlaneFinder/SimplePly.cpp > CMakeFiles/playground.dir/SimplePly.cpp.i

CMakeFiles/playground.dir/SimplePly.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/playground.dir/SimplePly.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zw/code/C++_Projects/PlaneFinder/SimplePly.cpp -o CMakeFiles/playground.dir/SimplePly.cpp.s

CMakeFiles/playground.dir/SimplePly.cpp.o.requires:

.PHONY : CMakeFiles/playground.dir/SimplePly.cpp.o.requires

CMakeFiles/playground.dir/SimplePly.cpp.o.provides: CMakeFiles/playground.dir/SimplePly.cpp.o.requires
	$(MAKE) -f CMakeFiles/playground.dir/build.make CMakeFiles/playground.dir/SimplePly.cpp.o.provides.build
.PHONY : CMakeFiles/playground.dir/SimplePly.cpp.o.provides

CMakeFiles/playground.dir/SimplePly.cpp.o.provides.build: CMakeFiles/playground.dir/SimplePly.cpp.o


CMakeFiles/playground.dir/rply.c.o: CMakeFiles/playground.dir/flags.make
CMakeFiles/playground.dir/rply.c.o: ../rply.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zw/code/C++_Projects/PlaneFinder/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/playground.dir/rply.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/playground.dir/rply.c.o   -c /Users/zw/code/C++_Projects/PlaneFinder/rply.c

CMakeFiles/playground.dir/rply.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/playground.dir/rply.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/zw/code/C++_Projects/PlaneFinder/rply.c > CMakeFiles/playground.dir/rply.c.i

CMakeFiles/playground.dir/rply.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/playground.dir/rply.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/zw/code/C++_Projects/PlaneFinder/rply.c -o CMakeFiles/playground.dir/rply.c.s

CMakeFiles/playground.dir/rply.c.o.requires:

.PHONY : CMakeFiles/playground.dir/rply.c.o.requires

CMakeFiles/playground.dir/rply.c.o.provides: CMakeFiles/playground.dir/rply.c.o.requires
	$(MAKE) -f CMakeFiles/playground.dir/build.make CMakeFiles/playground.dir/rply.c.o.provides.build
.PHONY : CMakeFiles/playground.dir/rply.c.o.provides

CMakeFiles/playground.dir/rply.c.o.provides.build: CMakeFiles/playground.dir/rply.c.o


CMakeFiles/playground.dir/Patch.cpp.o: CMakeFiles/playground.dir/flags.make
CMakeFiles/playground.dir/Patch.cpp.o: ../Patch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zw/code/C++_Projects/PlaneFinder/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/playground.dir/Patch.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/playground.dir/Patch.cpp.o -c /Users/zw/code/C++_Projects/PlaneFinder/Patch.cpp

CMakeFiles/playground.dir/Patch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/playground.dir/Patch.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zw/code/C++_Projects/PlaneFinder/Patch.cpp > CMakeFiles/playground.dir/Patch.cpp.i

CMakeFiles/playground.dir/Patch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/playground.dir/Patch.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zw/code/C++_Projects/PlaneFinder/Patch.cpp -o CMakeFiles/playground.dir/Patch.cpp.s

CMakeFiles/playground.dir/Patch.cpp.o.requires:

.PHONY : CMakeFiles/playground.dir/Patch.cpp.o.requires

CMakeFiles/playground.dir/Patch.cpp.o.provides: CMakeFiles/playground.dir/Patch.cpp.o.requires
	$(MAKE) -f CMakeFiles/playground.dir/build.make CMakeFiles/playground.dir/Patch.cpp.o.provides.build
.PHONY : CMakeFiles/playground.dir/Patch.cpp.o.provides

CMakeFiles/playground.dir/Patch.cpp.o.provides.build: CMakeFiles/playground.dir/Patch.cpp.o


# Object files for target playground
playground_OBJECTS = \
"CMakeFiles/playground.dir/playground.cpp.o" \
"CMakeFiles/playground.dir/SimplePly.cpp.o" \
"CMakeFiles/playground.dir/rply.c.o" \
"CMakeFiles/playground.dir/Patch.cpp.o"

# External object files for target playground
playground_EXTERNAL_OBJECTS =

playground: CMakeFiles/playground.dir/playground.cpp.o
playground: CMakeFiles/playground.dir/SimplePly.cpp.o
playground: CMakeFiles/playground.dir/rply.c.o
playground: CMakeFiles/playground.dir/Patch.cpp.o
playground: CMakeFiles/playground.dir/build.make
playground: CMakeFiles/playground.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zw/code/C++_Projects/PlaneFinder/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable playground"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/playground.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/playground.dir/build: playground

.PHONY : CMakeFiles/playground.dir/build

CMakeFiles/playground.dir/requires: CMakeFiles/playground.dir/playground.cpp.o.requires
CMakeFiles/playground.dir/requires: CMakeFiles/playground.dir/SimplePly.cpp.o.requires
CMakeFiles/playground.dir/requires: CMakeFiles/playground.dir/rply.c.o.requires
CMakeFiles/playground.dir/requires: CMakeFiles/playground.dir/Patch.cpp.o.requires

.PHONY : CMakeFiles/playground.dir/requires

CMakeFiles/playground.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/playground.dir/cmake_clean.cmake
.PHONY : CMakeFiles/playground.dir/clean

CMakeFiles/playground.dir/depend:
	cd /Users/zw/code/C++_Projects/PlaneFinder/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zw/code/C++_Projects/PlaneFinder /Users/zw/code/C++_Projects/PlaneFinder /Users/zw/code/C++_Projects/PlaneFinder/cmake-build-debug /Users/zw/code/C++_Projects/PlaneFinder/cmake-build-debug /Users/zw/code/C++_Projects/PlaneFinder/cmake-build-debug/CMakeFiles/playground.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/playground.dir/depend

