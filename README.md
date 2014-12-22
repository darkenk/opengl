Opengl project for learning purpose

# Build instructions:
```
mkdir build
cd build
cmake ../ -DCMAKE_CXX_COMPILER clang++
make run
```

# Build debug:
```
cmake ../ -DCMAKE_CXX_COMIPLER clang++ -DCMAKE_BUILD_TYPE=Debug
```

# To run only one test, eg.
```
make run_shaderloader_test -DENABLE_TESTS
```
