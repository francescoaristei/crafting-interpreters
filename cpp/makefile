# commands
# make: build the main executable
# bin/main: runs the executable
# make clean: removes all generated object files and executable.

# compiler settings
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic
LDFLGAS :=

# dirs
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
MAIN := $(BIN_DIR)/main

# targets
all: $(MAIN)

$(MAIN): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)