# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rengaj/Documents/PAGE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rengaj/Documents/PAGE

# Include any dependencies generated for this target.
include CMakeFiles/PAGE.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PAGE.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PAGE.out.dir/flags.make

CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o: CMakeFiles/PAGE.out.dir/flags.make
CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o: src/page_utility.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rengaj/Documents/PAGE/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o -c /home/rengaj/Documents/PAGE/src/page_utility.cpp

CMakeFiles/PAGE.out.dir/src/page_utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAGE.out.dir/src/page_utility.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rengaj/Documents/PAGE/src/page_utility.cpp > CMakeFiles/PAGE.out.dir/src/page_utility.cpp.i

CMakeFiles/PAGE.out.dir/src/page_utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAGE.out.dir/src/page_utility.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rengaj/Documents/PAGE/src/page_utility.cpp -o CMakeFiles/PAGE.out.dir/src/page_utility.cpp.s

CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o.requires:
.PHONY : CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o.requires

CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o.provides: CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o.requires
	$(MAKE) -f CMakeFiles/PAGE.out.dir/build.make CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o.provides.build
.PHONY : CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o.provides

CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o.provides.build: CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o

CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o: CMakeFiles/PAGE.out.dir/flags.make
CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o: src/page_matrix.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rengaj/Documents/PAGE/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o -c /home/rengaj/Documents/PAGE/src/page_matrix.cpp

CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rengaj/Documents/PAGE/src/page_matrix.cpp > CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.i

CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rengaj/Documents/PAGE/src/page_matrix.cpp -o CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.s

CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o.requires:
.PHONY : CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o.requires

CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o.provides: CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o.requires
	$(MAKE) -f CMakeFiles/PAGE.out.dir/build.make CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o.provides.build
.PHONY : CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o.provides

CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o.provides.build: CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o

CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o: CMakeFiles/PAGE.out.dir/flags.make
CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o: src/page_graphics.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rengaj/Documents/PAGE/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o -c /home/rengaj/Documents/PAGE/src/page_graphics.cpp

CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rengaj/Documents/PAGE/src/page_graphics.cpp > CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.i

CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rengaj/Documents/PAGE/src/page_graphics.cpp -o CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.s

CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o.requires:
.PHONY : CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o.requires

CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o.provides: CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o.requires
	$(MAKE) -f CMakeFiles/PAGE.out.dir/build.make CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o.provides.build
.PHONY : CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o.provides

CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o.provides.build: CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o

CMakeFiles/PAGE.out.dir/src/main.cpp.o: CMakeFiles/PAGE.out.dir/flags.make
CMakeFiles/PAGE.out.dir/src/main.cpp.o: src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rengaj/Documents/PAGE/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PAGE.out.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PAGE.out.dir/src/main.cpp.o -c /home/rengaj/Documents/PAGE/src/main.cpp

CMakeFiles/PAGE.out.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAGE.out.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rengaj/Documents/PAGE/src/main.cpp > CMakeFiles/PAGE.out.dir/src/main.cpp.i

CMakeFiles/PAGE.out.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAGE.out.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rengaj/Documents/PAGE/src/main.cpp -o CMakeFiles/PAGE.out.dir/src/main.cpp.s

CMakeFiles/PAGE.out.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/PAGE.out.dir/src/main.cpp.o.requires

CMakeFiles/PAGE.out.dir/src/main.cpp.o.provides: CMakeFiles/PAGE.out.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/PAGE.out.dir/build.make CMakeFiles/PAGE.out.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/PAGE.out.dir/src/main.cpp.o.provides

CMakeFiles/PAGE.out.dir/src/main.cpp.o.provides.build: CMakeFiles/PAGE.out.dir/src/main.cpp.o

CMakeFiles/PAGE.out.dir/src/page_window.cpp.o: CMakeFiles/PAGE.out.dir/flags.make
CMakeFiles/PAGE.out.dir/src/page_window.cpp.o: src/page_window.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rengaj/Documents/PAGE/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/PAGE.out.dir/src/page_window.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PAGE.out.dir/src/page_window.cpp.o -c /home/rengaj/Documents/PAGE/src/page_window.cpp

CMakeFiles/PAGE.out.dir/src/page_window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAGE.out.dir/src/page_window.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rengaj/Documents/PAGE/src/page_window.cpp > CMakeFiles/PAGE.out.dir/src/page_window.cpp.i

CMakeFiles/PAGE.out.dir/src/page_window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAGE.out.dir/src/page_window.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rengaj/Documents/PAGE/src/page_window.cpp -o CMakeFiles/PAGE.out.dir/src/page_window.cpp.s

CMakeFiles/PAGE.out.dir/src/page_window.cpp.o.requires:
.PHONY : CMakeFiles/PAGE.out.dir/src/page_window.cpp.o.requires

CMakeFiles/PAGE.out.dir/src/page_window.cpp.o.provides: CMakeFiles/PAGE.out.dir/src/page_window.cpp.o.requires
	$(MAKE) -f CMakeFiles/PAGE.out.dir/build.make CMakeFiles/PAGE.out.dir/src/page_window.cpp.o.provides.build
.PHONY : CMakeFiles/PAGE.out.dir/src/page_window.cpp.o.provides

CMakeFiles/PAGE.out.dir/src/page_window.cpp.o.provides.build: CMakeFiles/PAGE.out.dir/src/page_window.cpp.o

# Object files for target PAGE.out
PAGE_out_OBJECTS = \
"CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o" \
"CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o" \
"CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o" \
"CMakeFiles/PAGE.out.dir/src/main.cpp.o" \
"CMakeFiles/PAGE.out.dir/src/page_window.cpp.o"

# External object files for target PAGE.out
PAGE_out_EXTERNAL_OBJECTS =

PAGE.out: CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o
PAGE.out: CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o
PAGE.out: CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o
PAGE.out: CMakeFiles/PAGE.out.dir/src/main.cpp.o
PAGE.out: CMakeFiles/PAGE.out.dir/src/page_window.cpp.o
PAGE.out: /usr/local/lib/libglfw.a
PAGE.out: /usr/lib/libGLU.so
PAGE.out: /usr/lib/libGL.so
PAGE.out: /usr/lib/libSM.so
PAGE.out: /usr/lib/libICE.so
PAGE.out: /usr/lib/libX11.so
PAGE.out: /usr/lib/libXext.so
PAGE.out: /usr/lib/libGLEW.so
PAGE.out: /usr/lib/libXrandr.so
PAGE.out: CMakeFiles/PAGE.out.dir/build.make
PAGE.out: CMakeFiles/PAGE.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable PAGE.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PAGE.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PAGE.out.dir/build: PAGE.out
.PHONY : CMakeFiles/PAGE.out.dir/build

CMakeFiles/PAGE.out.dir/requires: CMakeFiles/PAGE.out.dir/src/page_utility.cpp.o.requires
CMakeFiles/PAGE.out.dir/requires: CMakeFiles/PAGE.out.dir/src/page_matrix.cpp.o.requires
CMakeFiles/PAGE.out.dir/requires: CMakeFiles/PAGE.out.dir/src/page_graphics.cpp.o.requires
CMakeFiles/PAGE.out.dir/requires: CMakeFiles/PAGE.out.dir/src/main.cpp.o.requires
CMakeFiles/PAGE.out.dir/requires: CMakeFiles/PAGE.out.dir/src/page_window.cpp.o.requires
.PHONY : CMakeFiles/PAGE.out.dir/requires

CMakeFiles/PAGE.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PAGE.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PAGE.out.dir/clean

CMakeFiles/PAGE.out.dir/depend:
	cd /home/rengaj/Documents/PAGE && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rengaj/Documents/PAGE /home/rengaj/Documents/PAGE /home/rengaj/Documents/PAGE /home/rengaj/Documents/PAGE /home/rengaj/Documents/PAGE/CMakeFiles/PAGE.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PAGE.out.dir/depend

