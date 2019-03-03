# OpenGL #
A rendering engine for trying out new OpenGL features.

### Build ###

#### Dependencies ####
	* OpenGL: The multiplatform graphics API used to develop the rendering engine
	* FreeGLUT: FreeGLUT is a free-software/open-source alternative to the OpenGL Utility Toolkit (GLUT) library. For more information please visit http://freeglut.sourceforge.net/
	* GLEW: The OpenGL Extension Wrangler Library (GLEW) is a cross-platform open-source C/C++ extension loading library. For more information please visit http://glew.sourceforge.net/
	* DevIL: Developer's Image Library (DevIL) is a programmer's library to develop applications with very powerful image loading capabilities, yet is easy for a developer to learn and use. For more information please visit http://openil.sourceforge.net/

#### Build system ####
Use CMake to build the source. For more information please visit https://cmake.org/

### Content ###
	* GLngin: The rendering engine.
	* Fractals: Draws Julia and Mandelbrot sets using fragment shader.
	* ImageProcessing: Performs some basic image processing operations on a loaded texture using fragment shader.
	* NBody: Performs N-body simulation using compute shader.
	* PositionBasedDynamics: Performs cloth simulation using compute shaders.
	* Splines: Draws control polygon and bezier curve using geometry shader.

