# Opengl project for learning purpose

Project is using [QDarkStyleSheet](https://github.com/ColinDuquesnoy/QDarkStyleSheet) stylesheet for demos. To fetch missing project type:
```
git sumbodule init qt/demos/QDarkStyleSheet
git submodule update
```

# Build instructions:
```
mkdir build
cd build
cmake ../ -DCMAKE_CXX_COMPILER=clang++
make run
```

# Build debug:
```
cmake ../ -DCMAKE_CXX_COMIPLER=clang++ -DCMAKE_BUILD_TYPE=Debug
```

# Disable demos
```
cmake ../ -DCMAKE_CXX_COMPILER=clang++ -DENABLE_DEMOS=FALSE
```

# To run only one test, eg.
Tests for now will not compile.
```
make run_shaderloader_test -DENABLE_TESTS
```

# For MS Windows
It is needed to download dependencies via:
```
git submodule init
git submodule update
```
After that import project into QtCreator and built normally

# Folder structure
* **cmake** - cmake stuffs
* **demos** - contains all small/sample applications
  * **light_demo** - allows to play with light using sliders
  * **main_demo** - primary opengl application, written with freeglut
  * **triangle** - simple triangle in opengl, used for implementing/checking new features
  * **qt** - common part of qt demos, contains widgets created for demos
* **external** - contains projects dependencies (used for windows)
  * **glew** - OpenGL Extension Wrangler
  * **glm** - math library
* **src** - core/common part of all demos
  * **shaders** - shaders used for common part
  * **units** - contains units like meters/seconds/radians/vertices etc.
* **tests** - unit tests (currently abandoned)
* **vera** - vera cpp style checker
