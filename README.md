# Opengl project for learning purpose

Project is using [QDarkStyleSheet](https://github.com/ColinDuquesnoy/QDarkStyleSheet) stylesheet for demos. To fetch missing project type:
```
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

# Build demos
```
cmake ../ -DCMAKE_CXX_COMPILER=clang++ -DENABLE_DEMOS=TRUE
```

# To run only one test, eg.
Tests for now will not compile.
```
make run_shaderloader_test -DENABLE_TESTS
```
