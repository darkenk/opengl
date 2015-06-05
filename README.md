# Opengl project for learning purpose

Project is using [QDarkStyleSheet](https://github.com/ColinDuquesnoy/QDarkStyleSheet) stylesheet
for qt demos.

# Requirements
* cmake 3.2.1
* qt5
* compiler which supports c++11 (eg. clang 3.4)

# Build instructions
## Fetch dependencies
```
git submodule init
git submodule update
```
## Regular simple build
```
mkdir build
cd build
cmake ../
make -j4
```
Results are in folder build/bin/
## Options
* ENABLE_DEMOS=1 - turn on building demos
* INTERNAL_LIBS=1 - use libs from external folder instead of system libs
* ENABLE_TESTS=1 - builds tests
Eg. to build projects without demos and with tests execute:
```
cmake ../ -DENABLE_DEMOS=0 -DENABLE_TESTS=1
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
  * **assimp_demo** - demo for playing with assimp
  * **light_demo** - allows to play with light using sliders
  * **main_demo** - primary opengl application, written with freeglut
  * **triangle** - simple triangle in opengl, used for implementing/checking new features
  * **qt** - common part of qt demos, contains widgets created for demos
* **external** - contains projects dependencies (used for windows)
  * **assimp** - Assimp for loadding loading assets
  * **glew** - OpenGL Extension Wrangler
  * **glm** - math library
  * **glmock** - OpenGL mock
  * **gmock** - Google mock
  * **gtest** - Google test
* **src** - core/common part of all demos
  * **models** - contains geometric models (cube, terrain, sphere, etc.)
  * **shaders** - shaders used for common part
  * **units** - contains units like meters/seconds/radians/vertices etc.
  * **utils** - helper functions
* **tests** - unit tests
* **vera** - vera cpp style checker
