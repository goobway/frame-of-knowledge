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
include _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/flags.make

_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.o: _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/flags.make
_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.o: abseil-cpp/absl/strings/internal/ostringstream.cc
_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.o: _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/calista/School/frame-of-knowledge/classification/tflite_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.o"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.o -MF CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.o.d -o CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.o -c /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/strings/internal/ostringstream.cc

_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.i"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/strings/internal/ostringstream.cc > CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.i

_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.s"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/strings/internal/ostringstream.cc -o CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.s

_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.o: _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/flags.make
_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.o: abseil-cpp/absl/strings/internal/utf8.cc
_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.o: _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/calista/School/frame-of-knowledge/classification/tflite_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.o"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.o -MF CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.o.d -o CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.o -c /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/strings/internal/utf8.cc

_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.i"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/strings/internal/utf8.cc > CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.i

_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.s"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/strings/internal/utf8.cc -o CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.s

_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.o: _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/flags.make
_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.o: abseil-cpp/absl/strings/internal/escaping.cc
_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.o: _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/calista/School/frame-of-knowledge/classification/tflite_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.o"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.o -MF CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.o.d -o CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.o -c /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/strings/internal/escaping.cc

_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.i"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/strings/internal/escaping.cc > CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.i

_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.s"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/strings/internal/escaping.cc -o CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.s

# Object files for target absl_strings_internal
absl_strings_internal_OBJECTS = \
"CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.o" \
"CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.o" \
"CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.o"

# External object files for target absl_strings_internal
absl_strings_internal_EXTERNAL_OBJECTS =

_deps/abseil-cpp-build/absl/strings/libabsl_strings_internal.a: _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/ostringstream.cc.o
_deps/abseil-cpp-build/absl/strings/libabsl_strings_internal.a: _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/utf8.cc.o
_deps/abseil-cpp-build/absl/strings/libabsl_strings_internal.a: _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/internal/escaping.cc.o
_deps/abseil-cpp-build/absl/strings/libabsl_strings_internal.a: _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/build.make
_deps/abseil-cpp-build/absl/strings/libabsl_strings_internal.a: _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/calista/School/frame-of-knowledge/classification/tflite_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libabsl_strings_internal.a"
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && $(CMAKE_COMMAND) -P CMakeFiles/absl_strings_internal.dir/cmake_clean_target.cmake
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/absl_strings_internal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/build: _deps/abseil-cpp-build/absl/strings/libabsl_strings_internal.a
.PHONY : _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/build

_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/clean:
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings && $(CMAKE_COMMAND) -P CMakeFiles/absl_strings_internal.dir/cmake_clean.cmake
.PHONY : _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/clean

_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/depend:
	cd /home/calista/School/frame-of-knowledge/classification/tflite_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/calista/School/frame-of-knowledge/classification/tensorflow_src/tensorflow/lite /home/calista/School/frame-of-knowledge/classification/tflite_build/abseil-cpp/absl/strings /home/calista/School/frame-of-knowledge/classification/tflite_build /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings /home/calista/School/frame-of-knowledge/classification/tflite_build/_deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/abseil-cpp-build/absl/strings/CMakeFiles/absl_strings_internal.dir/depend

