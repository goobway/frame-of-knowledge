# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/calista/School/frame-of-knowledge/classification/tensorflow_src/tensorflow/lite

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/calista/School/frame-of-knowledge/classification/tflite_build

# Include any dependencies generated for this target.
include _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/flags.make

_deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.o: _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/flags.make
_deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.o: ruy/ruy/kernel_avx.cc
_deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.o: _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/calista/School/frame-of-knowledge/classification/tflite_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.o"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/ruy-build/ruy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.o -MF CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.o.d -o CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.o -c /home/calista/School/frame-of-knowledge/classification/tflite_build/ruy/ruy/kernel_avx.cc

_deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.i"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/ruy-build/ruy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/calista/School/frame-of-knowledge/classification/tflite_build/ruy/ruy/kernel_avx.cc > CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.i

_deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.s"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/ruy-build/ruy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/calista/School/frame-of-knowledge/classification/tflite_build/ruy/ruy/kernel_avx.cc -o CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.s

# Object files for target ruy_kernel_avx
ruy_kernel_avx_OBJECTS = \
"CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.o"

# External object files for target ruy_kernel_avx
ruy_kernel_avx_EXTERNAL_OBJECTS =

_deps/ruy-build/ruy/libruy_kernel_avx.a: _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/kernel_avx.cc.o
_deps/ruy-build/ruy/libruy_kernel_avx.a: _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/build.make
_deps/ruy-build/ruy/libruy_kernel_avx.a: _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/calista/School/frame-of-knowledge/classification/tflite_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libruy_kernel_avx.a"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/ruy-build/ruy && $(CMAKE_COMMAND) -P CMakeFiles/ruy_kernel_avx.dir/cmake_clean_target.cmake
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/ruy-build/ruy && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ruy_kernel_avx.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/build: _deps/ruy-build/ruy/libruy_kernel_avx.a
.PHONY : _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/build

_deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/clean:
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/ruy-build/ruy && $(CMAKE_COMMAND) -P CMakeFiles/ruy_kernel_avx.dir/cmake_clean.cmake
.PHONY : _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/clean

_deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/depend:
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/calista/School/frame-of-knowledge/classification/tensorflow_src/tensorflow/lite /home/calista/School/frame-of-knowledge/classification/tflite_build/ruy/ruy /home/calista/School/frame-of-knowledge/classification/tflite_build /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/ruy-build/ruy /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/ruy-build/ruy/CMakeFiles/ruy_kernel_avx.dir/depend

