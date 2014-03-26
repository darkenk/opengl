CXX = clang++
CXXFLAGS = -c -Wall -std=c++11
LDFLAGS = -lglut -lGL -lgtest -lpthread
SOURCES = $(shell ls tests | grep .cpp)
OBJECTS = $(SOURCES:.cpp=.o)
RELEASE_OBJ_DIR = build/release/obj
TEST_OBJ_DIR = build/tests/obj
TEST_DIR = build/tests
TEST_OBJECTS = $(addprefix $(TEST_OBJ_DIR)/,$(OBJECTS))
RELEASE_OBJECTS = $(addprefix $(RELEASE_OBJ_DIR)/,$(OBJECTS))
EXECUTABLES = $(shell ls tests | grep .cpp | sed -e 's/.cpp//g')

vpath %.o $(TEST_OBJ_DIR)
vpath %.cpp tests
vpath $(EXECUTABLES) $(TEST_DIR)

all: $(TEST_OBJ_DIR) $(EXECUTABLES)
    
$(EXECUTABLES): $(TEST_OBJECTS)
	$(CXX) $(TEST_OBJ_DIR)/$@.o $(RELEASE_OBJ_DIR)/$@.o -o $(TEST_DIR)/$@ $(LDFLAGS)

$(TEST_OBJ_DIR)/%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

$(TEST_OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf build

run: all
	for i in $(EXECUTABLES) ; \
	do \
		$(TEST_DIR)/$(EXECUTABLES) ; \
	done \
