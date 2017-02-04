Youtube playlist: https://www.youtube.com/playlist?list=PLe27dA7aKQtUqdCtAziwOvw7A41XrDR40


***********************************************************************************************
*** DISCLAIMER: THIS PROJECT ONLY WORKS ON WINDOWS MACHINES ***********************************
***********************************************************************************************

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
