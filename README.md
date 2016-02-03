
DISCLAIMER: THIS PROJECT CURRENTLY ONLY WORKS ON A WINDOWS PLATFORM!

-------------------------------------------------------------------------------------------------------------------------

TABLE OF CONTENTS:
1. PROJECT SPECIFICS
 
2. SETUP
	A. Visual Studio

-------------------------------------------------------------------------------------------------------------------------

1. PROJECT SPECIFICS



2. SETUP
    A. Visual Studio

	This project requires OpenGL, which is already provided in the Windows SDK. As a result, all that should be
	needed is a reference to opengl32.lib. To add this reference, open the properties of the project. 
	Navigate to Linker > Input > Additional Dependencies, and add "opengl32.lib" to the list (no double quotes).

