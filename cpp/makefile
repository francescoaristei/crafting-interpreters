# commands
# make: build the main executable
# make run_main : builds and execute the main
# bin/main: runs the executable
# make clean: removes all generated object files and executable.

# compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Isrc/include -g
LDFLAGS :=

# dirs
SRC_DIR := src/cpplox
OBJ_DIR := obj
BIN_DIR := bin

# default value is no value (REPL execution)
ARG ?= 

# source files
SRCS := $(filter-out $(SRC_DIR)/astPrinter.cpp, $(wildcard $(SRC_DIR)/*.cpp))
#SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
MAIN := $(BIN_DIR)/main

# targets
all: $(MAIN)

$(MAIN): $(OBJ_DIR)/main.o $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: run
run: $(MAIN)
	./$(MAIN) $(ARG)
