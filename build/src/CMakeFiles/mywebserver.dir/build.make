# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/llz/code/HTTPserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/llz/code/HTTPserver/build

# Include any dependencies generated for this target.
include src/CMakeFiles/mywebserver.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/mywebserver.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/mywebserver.dir/flags.make

src/CMakeFiles/mywebserver.dir/Epoll.cpp.o: src/CMakeFiles/mywebserver.dir/flags.make
src/CMakeFiles/mywebserver.dir/Epoll.cpp.o: ../src/Epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/llz/code/HTTPserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/mywebserver.dir/Epoll.cpp.o"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mywebserver.dir/Epoll.cpp.o -c /home/llz/code/HTTPserver/src/Epoll.cpp

src/CMakeFiles/mywebserver.dir/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mywebserver.dir/Epoll.cpp.i"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/llz/code/HTTPserver/src/Epoll.cpp > CMakeFiles/mywebserver.dir/Epoll.cpp.i

src/CMakeFiles/mywebserver.dir/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mywebserver.dir/Epoll.cpp.s"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/llz/code/HTTPserver/src/Epoll.cpp -o CMakeFiles/mywebserver.dir/Epoll.cpp.s

src/CMakeFiles/mywebserver.dir/Handle.cpp.o: src/CMakeFiles/mywebserver.dir/flags.make
src/CMakeFiles/mywebserver.dir/Handle.cpp.o: ../src/Handle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/llz/code/HTTPserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/mywebserver.dir/Handle.cpp.o"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mywebserver.dir/Handle.cpp.o -c /home/llz/code/HTTPserver/src/Handle.cpp

src/CMakeFiles/mywebserver.dir/Handle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mywebserver.dir/Handle.cpp.i"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/llz/code/HTTPserver/src/Handle.cpp > CMakeFiles/mywebserver.dir/Handle.cpp.i

src/CMakeFiles/mywebserver.dir/Handle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mywebserver.dir/Handle.cpp.s"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/llz/code/HTTPserver/src/Handle.cpp -o CMakeFiles/mywebserver.dir/Handle.cpp.s

src/CMakeFiles/mywebserver.dir/Http.cpp.o: src/CMakeFiles/mywebserver.dir/flags.make
src/CMakeFiles/mywebserver.dir/Http.cpp.o: ../src/Http.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/llz/code/HTTPserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/mywebserver.dir/Http.cpp.o"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mywebserver.dir/Http.cpp.o -c /home/llz/code/HTTPserver/src/Http.cpp

src/CMakeFiles/mywebserver.dir/Http.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mywebserver.dir/Http.cpp.i"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/llz/code/HTTPserver/src/Http.cpp > CMakeFiles/mywebserver.dir/Http.cpp.i

src/CMakeFiles/mywebserver.dir/Http.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mywebserver.dir/Http.cpp.s"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/llz/code/HTTPserver/src/Http.cpp -o CMakeFiles/mywebserver.dir/Http.cpp.s

src/CMakeFiles/mywebserver.dir/Server.cpp.o: src/CMakeFiles/mywebserver.dir/flags.make
src/CMakeFiles/mywebserver.dir/Server.cpp.o: ../src/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/llz/code/HTTPserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/mywebserver.dir/Server.cpp.o"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mywebserver.dir/Server.cpp.o -c /home/llz/code/HTTPserver/src/Server.cpp

src/CMakeFiles/mywebserver.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mywebserver.dir/Server.cpp.i"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/llz/code/HTTPserver/src/Server.cpp > CMakeFiles/mywebserver.dir/Server.cpp.i

src/CMakeFiles/mywebserver.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mywebserver.dir/Server.cpp.s"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/llz/code/HTTPserver/src/Server.cpp -o CMakeFiles/mywebserver.dir/Server.cpp.s

src/CMakeFiles/mywebserver.dir/Time.cpp.o: src/CMakeFiles/mywebserver.dir/flags.make
src/CMakeFiles/mywebserver.dir/Time.cpp.o: ../src/Time.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/llz/code/HTTPserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/mywebserver.dir/Time.cpp.o"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mywebserver.dir/Time.cpp.o -c /home/llz/code/HTTPserver/src/Time.cpp

src/CMakeFiles/mywebserver.dir/Time.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mywebserver.dir/Time.cpp.i"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/llz/code/HTTPserver/src/Time.cpp > CMakeFiles/mywebserver.dir/Time.cpp.i

src/CMakeFiles/mywebserver.dir/Time.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mywebserver.dir/Time.cpp.s"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/llz/code/HTTPserver/src/Time.cpp -o CMakeFiles/mywebserver.dir/Time.cpp.s

src/CMakeFiles/mywebserver.dir/sub.cpp.o: src/CMakeFiles/mywebserver.dir/flags.make
src/CMakeFiles/mywebserver.dir/sub.cpp.o: ../src/sub.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/llz/code/HTTPserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/mywebserver.dir/sub.cpp.o"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mywebserver.dir/sub.cpp.o -c /home/llz/code/HTTPserver/src/sub.cpp

src/CMakeFiles/mywebserver.dir/sub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mywebserver.dir/sub.cpp.i"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/llz/code/HTTPserver/src/sub.cpp > CMakeFiles/mywebserver.dir/sub.cpp.i

src/CMakeFiles/mywebserver.dir/sub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mywebserver.dir/sub.cpp.s"
	cd /home/llz/code/HTTPserver/build/src && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/llz/code/HTTPserver/src/sub.cpp -o CMakeFiles/mywebserver.dir/sub.cpp.s

# Object files for target mywebserver
mywebserver_OBJECTS = \
"CMakeFiles/mywebserver.dir/Epoll.cpp.o" \
"CMakeFiles/mywebserver.dir/Handle.cpp.o" \
"CMakeFiles/mywebserver.dir/Http.cpp.o" \
"CMakeFiles/mywebserver.dir/Server.cpp.o" \
"CMakeFiles/mywebserver.dir/Time.cpp.o" \
"CMakeFiles/mywebserver.dir/sub.cpp.o"

# External object files for target mywebserver
mywebserver_EXTERNAL_OBJECTS =

../bin/mywebserver: src/CMakeFiles/mywebserver.dir/Epoll.cpp.o
../bin/mywebserver: src/CMakeFiles/mywebserver.dir/Handle.cpp.o
../bin/mywebserver: src/CMakeFiles/mywebserver.dir/Http.cpp.o
../bin/mywebserver: src/CMakeFiles/mywebserver.dir/Server.cpp.o
../bin/mywebserver: src/CMakeFiles/mywebserver.dir/Time.cpp.o
../bin/mywebserver: src/CMakeFiles/mywebserver.dir/sub.cpp.o
../bin/mywebserver: src/CMakeFiles/mywebserver.dir/build.make
../bin/mywebserver: src/CMakeFiles/mywebserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/llz/code/HTTPserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ../../bin/mywebserver"
	cd /home/llz/code/HTTPserver/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mywebserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/mywebserver.dir/build: ../bin/mywebserver

.PHONY : src/CMakeFiles/mywebserver.dir/build

src/CMakeFiles/mywebserver.dir/clean:
	cd /home/llz/code/HTTPserver/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mywebserver.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/mywebserver.dir/clean

src/CMakeFiles/mywebserver.dir/depend:
	cd /home/llz/code/HTTPserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/llz/code/HTTPserver /home/llz/code/HTTPserver/src /home/llz/code/HTTPserver/build /home/llz/code/HTTPserver/build/src /home/llz/code/HTTPserver/build/src/CMakeFiles/mywebserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/mywebserver.dir/depend

