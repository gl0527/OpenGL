# OpenGL
A rendering engine for trying out new OpenGL features.

## Installation
### Supported operating systems
Theoretically all Linux distributions.

Tested on the following distros:
* Linux Mint 19
* Linux Mint 20.1
* Debian 10

### Prerequisites
The following packages are required to go on with the installation process: `git`, `cmake` and `g++`.

### Install dependencies
A possible way for installing the dependencies:
```bash
$ sudo apt install -y libglew-dev freeglut3-dev libdevil-dev clang-format
```

### Install this repo
A possible way for installing this repo:
```bash
$ git clone https://github.com/gl0527/OpenGL.git
$ cd OpenGL
$ mkdir build && cd build
$ cmake ../Modules
$ make -j

```
The generated binaries can be found in the `Bin` directory created by
`CMake`.

## Content
  * GLngin: The rendering engine.
  * Fractals: Draws Julia and Mandelbrot sets using fragment shader.
  * ImageProcessing: Performs some basic image processing operations on a loaded texture using fragment shader.
  * NBody: Performs N-body simulation using compute shader.
  * PositionBasedDynamics: Performs cloth simulation using compute shaders.
  * Splines: Draws control polygon and bezier curve using geometry shader.
  * GameOfLife: Applies the rules of Game of Life onto an input texture using fragment shader.
