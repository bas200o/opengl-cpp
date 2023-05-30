C++ & OpenGL opdracht Bas Winkelhof
=======================
Eindopdracht voor C++ en OpenGL TI2.4

Runs on
 * Linux
 * Windows
 * Mac

Clone (With submodules):
========================

```
git clone --recursive git@github.com:bas200o/opengl-cpp.git
```

Alternatively, if you don't used the --recursive option, you can type:
```bash
git submodule init
git submodule update
```

usage (VS Code)
---------------
Install the following extensions

https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools

https://marketplace.visualstudio.com/items?itemName=twxs.cmake

- Select build kit (eg. GCC)
- Select build target opengl-bas
- run


usage (Linux - x11) : 
---------------
Some standard library to install:
```bash
sudo apt-get install cmake libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev

Open the directory into a terminal
```bash
mkdir build
cd build
cmake ..
./main
```

usage (Windows) :
-----------------
For instance :
* cmake-gui .
* Configure (Choose for example Visual Studio generator)
* Generate
Launch the generated project in your favorite IDE and run it.

## Testing
run ```ctest``` from build directory



