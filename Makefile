CXX = clang++
CXXFLAGS = -c -Wall -std=c++11 -DGL_GLEXT_PROTOTYPES
LDFLAGS = -lglut -lGL -lGLU -lGLEW
SOURCES = $(shell ls src | grep .cpp)
OBJECTS = $(SOURCES:.cpp=.o)
HEADER_FILES = $(shell ls src | grep .hpp)
BUILD_DIR = build/release
OBJ_DIR = build/release/obj
OUT_OBJECTS = $(addprefix $(OBJ_DIR)/,$(OBJECTS))
EXECUTABLE = opengl
SRC_SHADERS = src/shaders/
SHADERS = $(shell ls $(SRC_SHADERS) | grep .glsl)
OUT_SHADERS = $(addprefix $(BUILD_DIR)/, $(SHADERS))

vpath %.o $(OBJ_DIR)
vpath %.cpp src
vpath %.hpp src
vpath $(EXECUTABLE) $(BUILD_DIR)

all: $(OBJ_DIR) $(EXECUTABLE)
	
$(EXECUTABLE): $(OUT_OBJECTS) $(OUT_SHADERS) 
	$(CXX) $(LDFLAGS) $(OUT_OBJECTS) -o $(BUILD_DIR)/$@

$(OBJ_DIR)/%.o: %.cpp $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.glsl: $(SRC_SHADERS)/%.glsl
	cp $< $(BUILD_DIR)

clean:
	rm -rf build

run: all
	$(BUILD_DIR)/$(EXECUTABLE)

tests: all
	make -f tests/Makefile run
