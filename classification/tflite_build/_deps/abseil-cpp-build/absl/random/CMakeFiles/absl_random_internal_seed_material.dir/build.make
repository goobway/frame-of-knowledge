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
include _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/flags.make

_deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.o: _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/flags.make
_deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.o: abseil-cpp/absl/random/internal/seed_material.cc
_deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.o: _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/calista/School/frame-of-knowledge/classification/tflite_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.o"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/random && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.o -MF CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.o.d -o CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.o -c /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/random/internal/seed_material.cc

_deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.i"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/random && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/random/internal/seed_material.cc > CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.i

_deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.s"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/random && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/random/internal/seed_material.cc -o CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.s

# Object files for target absl_random_internal_seed_material
absl_random_internal_seed_material_OBJECTS = \
"CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.o"

# External object files for target absl_random_internal_seed_material
absl_random_internal_seed_material_EXTERNAL_OBJECTS =

_deps/abseil-cpp-build/absl/random/libabsl_random_internal_seed_material.a: _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/internal/seed_material.cc.o
_deps/abseil-cpp-build/absl/random/libabsl_random_internal_seed_material.a: _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/build.make
_deps/abseil-cpp-build/absl/random/libabsl_random_internal_seed_material.a: _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/calista/School/frame-of-knowledge/classification/tflite_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libabsl_random_internal_seed_material.a"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/random && $(CMAKE_COMMAND) -P CMakeFiles/absl_random_internal_seed_material.dir/cmake_clean_target.cmake
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/random && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/absl_random_internal_seed_material.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/build: _deps/abseil-cpp-build/absl/random/libabsl_random_internal_seed_material.a
.PHONY : _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/build

_deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/clean:
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/random && $(CMAKE_COMMAND) -P CMakeFiles/absl_random_internal_seed_material.dir/cmake_clean.cmake
.PHONY : _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/clean

_deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/depend:
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/calista/School/frame-of-knowledge/classification/tensorflow_src/tensorflow/lite /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/random /home/calista/School/frame-of-knowledge/classification/tflite_build /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/random /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/abseil-cpp-build/absl/random/CMakeFiles/absl_random_internal_seed_material.dir/depend

