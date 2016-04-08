CS 418 - MP2 Flight Simulator

Joe Pagliuco (jpagli2)


***********************************************************************************************
*** DISCLAIMER: THIS PROJECT ONLY WORKS ON WINDOWS MACHINES ***********************************
***********************************************************************************************

Video Link: https://www.youtube.com/watch?v=1jn3LBo4Y8E


What this project is:
	- This MP is built on top of a game engine I've been working on over this semester. The repository is located on my
		github: https://github.com/jbpagliuco/CS418Engine
	- The only files necessary to create specifically this MP (not the engine) are in the assets folder, namely scripts/cameraMovement.lua and scenes/scene.cs418scene
	- The engine itself contains all OpenGL drawing calls, this can be seen in graphics/Renderer.cpp
	- Any project using the current state of the engine can be creating using lua scripts, and a scene file; No recompilation is required.
	- The .exe file to run is called Engine.exe - This file will run the correct scripts to create the flight simulator.
	
	
	
MP Controls and Configuration:
	- Rotate pitch by using the Up and Down arrow keys (inverted controls)
	- Rotate roll by using the Left and Right arrow keys
	- Increase the speed of the plane by holding the W key, and decrease the speed by holding the S key
	- If the program is taking to too long to initialize, try setting the terrain size to a lower value.
		- Correct values are explained in the scene_help.txt file, and the actual data can be modified in the assets/scenes/scene.cs418scene file
		- NOTE: Any changes in configuration will NOT require recompiling of the project, only restarting the .exe file



Basic Information:
	1. PLATFORM: Windows
	2. OS VERSION: Only tested on Windows 7, should work on 7 and up
	3. BUILD ENVIRONMENT: Visual Studio
	4. BUILD ENVIRONMENT VERSION: Visual Studio Community 2015
	5. LANGUAGE: C++
	6. EXTERNAL LIBRARIES: OPENGL, GLEW, LUA 5.1, LUABRIDGE, SOIL
	
Build Instructions:
	This project needs the external libraries linked, as well as the necessary includes folders
		Include:
			include
			SOIL/include
			Lua51/include
			LuaBridge
			glew-1.13.0/include
			
		Libraries:
			SOIL/lib
			Lua51/lib
			glew-1.13.0/lib/Release/Win32
	These folders (which are relative to the project path) need to be added the Visual Studio Project File.
		This can be done going into the project properties, and adding the include folders to C/C++ > General > Additional Include Directories,
		and the library directories to Linker > General > Addition Library Directories
	In addition to this, the following dependencies need to be added to the project: opengl32.lib, glew32.lib, lua51.lib, and SOIL.lib
		These can be added by going to Linker > Input > Additional Dependencies