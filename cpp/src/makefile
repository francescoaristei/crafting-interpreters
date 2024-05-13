# commands
# make run_printer : builds and execute the ast printer
# bin/main: runs the executable
# make clean: removes all generated object files and executable.

# compiler settings
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic
LDFLAGS :=

# dirs
SRC_DIR := cpplox
OBJ_DIR := cpplox/obj
BIN_DIR := cpplox/bin

# source files
SRCS := $(filter-out $(SRC_DIR)/main.cpp,  $(wildcard $(SRC_DIR)/*.cpp))

OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

MAIN := $(BIN_DIR)/printer

# targets
all: $(MAIN)

$(MAIN): $(OBJ_DIR)/astPrinter.o $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: run_printer
run_printer: $(MAIN)
	./$(MAIN)