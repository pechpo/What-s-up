# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/foreverlasting/git/What-s-up/Login

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/foreverlasting/git/What-s-up/build-Login-Qt_6_5_2_for_macOS-Debug

# Utility rule file for Login_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/Login_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Login_autogen.dir/progress.make

CMakeFiles/Login_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/foreverlasting/git/What-s-up/build-Login-Qt_6_5_2_for_macOS-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target Login"
	/opt/homebrew/Cellar/cmake/3.27.3/bin/cmake -E cmake_autogen /Users/foreverlasting/git/What-s-up/build-Login-Qt_6_5_2_for_macOS-Debug/CMakeFiles/Login_autogen.dir/AutogenInfo.json Debug

Login_autogen: CMakeFiles/Login_autogen
Login_autogen: CMakeFiles/Login_autogen.dir/build.make
.PHONY : Login_autogen

# Rule to build all files generated by this target.
CMakeFiles/Login_autogen.dir/build: Login_autogen
.PHONY : CMakeFiles/Login_autogen.dir/build

CMakeFiles/Login_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Login_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Login_autogen.dir/clean

CMakeFiles/Login_autogen.dir/depend:
	cd /Users/foreverlasting/git/What-s-up/build-Login-Qt_6_5_2_for_macOS-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/foreverlasting/git/What-s-up/Login /Users/foreverlasting/git/What-s-up/Login /Users/foreverlasting/git/What-s-up/build-Login-Qt_6_5_2_for_macOS-Debug /Users/foreverlasting/git/What-s-up/build-Login-Qt_6_5_2_for_macOS-Debug /Users/foreverlasting/git/What-s-up/build-Login-Qt_6_5_2_for_macOS-Debug/CMakeFiles/Login_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Login_autogen.dir/depend

