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
CMAKE_COMMAND = /Users/chasenagle/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake

# The command to remove a file.
RM = /Users/chasenagle/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/chasenagle/CLionProjects/RenderingEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app

# Include any dependencies generated for this target.
include CMakeFiles/OpenGLProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OpenGLProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGLProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGLProject.dir/flags.make

CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.o: CMakeFiles/OpenGLProject.dir/flags.make
CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.o: /Users/chasenagle/CLionProjects/RenderingEngine/src/Components/mainEngine.cpp
CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.o: CMakeFiles/OpenGLProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.o -MF CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.o.d -o CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.o -c /Users/chasenagle/CLionProjects/RenderingEngine/src/Components/mainEngine.cpp

CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/chasenagle/CLionProjects/RenderingEngine/src/Components/mainEngine.cpp > CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.i

CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/chasenagle/CLionProjects/RenderingEngine/src/Components/mainEngine.cpp -o CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.s

CMakeFiles/OpenGLProject.dir/src/glad.c.o: CMakeFiles/OpenGLProject.dir/flags.make
CMakeFiles/OpenGLProject.dir/src/glad.c.o: /Users/chasenagle/CLionProjects/RenderingEngine/src/glad.c
CMakeFiles/OpenGLProject.dir/src/glad.c.o: CMakeFiles/OpenGLProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OpenGLProject.dir/src/glad.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OpenGLProject.dir/src/glad.c.o -MF CMakeFiles/OpenGLProject.dir/src/glad.c.o.d -o CMakeFiles/OpenGLProject.dir/src/glad.c.o -c /Users/chasenagle/CLionProjects/RenderingEngine/src/glad.c

CMakeFiles/OpenGLProject.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/OpenGLProject.dir/src/glad.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/chasenagle/CLionProjects/RenderingEngine/src/glad.c > CMakeFiles/OpenGLProject.dir/src/glad.c.i

CMakeFiles/OpenGLProject.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/OpenGLProject.dir/src/glad.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/chasenagle/CLionProjects/RenderingEngine/src/glad.c -o CMakeFiles/OpenGLProject.dir/src/glad.c.s

CMakeFiles/OpenGLProject.dir/src/main.cpp.o: CMakeFiles/OpenGLProject.dir/flags.make
CMakeFiles/OpenGLProject.dir/src/main.cpp.o: /Users/chasenagle/CLionProjects/RenderingEngine/src/main.cpp
CMakeFiles/OpenGLProject.dir/src/main.cpp.o: CMakeFiles/OpenGLProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/OpenGLProject.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGLProject.dir/src/main.cpp.o -MF CMakeFiles/OpenGLProject.dir/src/main.cpp.o.d -o CMakeFiles/OpenGLProject.dir/src/main.cpp.o -c /Users/chasenagle/CLionProjects/RenderingEngine/src/main.cpp

CMakeFiles/OpenGLProject.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OpenGLProject.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/chasenagle/CLionProjects/RenderingEngine/src/main.cpp > CMakeFiles/OpenGLProject.dir/src/main.cpp.i

CMakeFiles/OpenGLProject.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OpenGLProject.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/chasenagle/CLionProjects/RenderingEngine/src/main.cpp -o CMakeFiles/OpenGLProject.dir/src/main.cpp.s

# Object files for target OpenGLProject
OpenGLProject_OBJECTS = \
"CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.o" \
"CMakeFiles/OpenGLProject.dir/src/glad.c.o" \
"CMakeFiles/OpenGLProject.dir/src/main.cpp.o"

# External object files for target OpenGLProject
OpenGLProject_EXTERNAL_OBJECTS =

bin/OpenGLProject.app/Contents/MacOS/OpenGLProject: CMakeFiles/OpenGLProject.dir/src/Components/mainEngine.cpp.o
bin/OpenGLProject.app/Contents/MacOS/OpenGLProject: CMakeFiles/OpenGLProject.dir/src/glad.c.o
bin/OpenGLProject.app/Contents/MacOS/OpenGLProject: CMakeFiles/OpenGLProject.dir/src/main.cpp.o
bin/OpenGLProject.app/Contents/MacOS/OpenGLProject: CMakeFiles/OpenGLProject.dir/build.make
bin/OpenGLProject.app/Contents/MacOS/OpenGLProject: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.1.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
bin/OpenGLProject.app/Contents/MacOS/OpenGLProject: /opt/homebrew/lib/libglfw.3.4.dylib
bin/OpenGLProject.app/Contents/MacOS/OpenGLProject: /opt/homebrew/lib/libglm.dylib
bin/OpenGLProject.app/Contents/MacOS/OpenGLProject: CMakeFiles/OpenGLProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bin/OpenGLProject.app/Contents/MacOS/OpenGLProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenGLProject.dir/link.txt --verbose=$(VERBOSE)
	/Users/chasenagle/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_directory /Users/chasenagle/CLionProjects/RenderingEngine/Content/Models /Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app/bin/OpenGLProject.app/Contents/Resources/Content/Models
	/Users/chasenagle/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_directory /Users/chasenagle/CLionProjects/RenderingEngine/Content/Shaders /Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app/bin/OpenGLProject.app/Contents/Resources/Content/Shaders
	/Users/chasenagle/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_directory /Users/chasenagle/CLionProjects/RenderingEngine/Content/Textures /Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app/bin/OpenGLProject.app/Contents/Resources/Content/Textures
	/Users/chasenagle/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_directory /Users/chasenagle/CLionProjects/RenderingEngine/Content/Images /Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app/bin/OpenGLProject.app/Contents/Resources/Content/Images

# Rule to build all files generated by this target.
CMakeFiles/OpenGLProject.dir/build: bin/OpenGLProject.app/Contents/MacOS/OpenGLProject
.PHONY : CMakeFiles/OpenGLProject.dir/build

CMakeFiles/OpenGLProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenGLProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenGLProject.dir/clean

CMakeFiles/OpenGLProject.dir/depend:
	cd /Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chasenagle/CLionProjects/RenderingEngine /Users/chasenagle/CLionProjects/RenderingEngine /Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app /Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app /Users/chasenagle/CLionProjects/RenderingEngine/build/macos-app/CMakeFiles/OpenGLProject.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/OpenGLProject.dir/depend

