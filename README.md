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

## known issue
The relative path used when loading models is diffrent under windows vs linux. when running in windows models will not load. Find and replace the locations by going back one folder with ```../```

## Testing
run ```ctest``` from build directory



