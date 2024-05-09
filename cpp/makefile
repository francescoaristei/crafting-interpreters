# commands
# make: build the main and genast executables
# make run_main : builds and execute the main
# make run_genast: builds and execute the genast
# bin/main: runs the executable
# make clean: removes all generated object files and executable.

# compiler settings
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic
LDFLAGS :=

# dirs
SRC_DIR := src/cpplox
AST_DIR := src/tools
OBJ_DIR := obj
OBJ_AST_DIR := src/tools/objast
BIN_DIR := bin
AST_BIN_DIR := src/tools/bin
AST_CLASSES_DIR := src/tools/ast_classes



# source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
AST_SRCS := $(wildcard $(AST_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_AST := $(patsubst $(AST_DIR)/%.cpp, $(OBJ_AST_DIR)/%.o, $(AST_SRCS))
MAIN := $(BIN_DIR)/main
MAIN_AST := $(AST_BIN_DIR)/genast

# targets
all: $(MAIN) $(MAIN_AST)

$(MAIN): $(OBJ_DIR)/main.o $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@

$(MAIN_AST): $(OBJ_AST_DIR)/generateAst.o $(OBJS_AST)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_AST_DIR)/%.o: $(AST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(OBJ_AST_DIR) $(AST_BIN_DIR)

.PHONY: clean_ast
clean_ast:
	rm -rf $(AST_CLASSES_DIR)

.PHONY: run_main
run_main: $(MAIN)
	./$(MAIN)

.PHONY: run_genast
run_genast: $(MAIN_AST)
#@echo "Enter any additional command line arguments:"
#@read ARGS;
	@mkdir -p $(AST_CLASSES_DIR)
#./$(MAIN_AST) $$ARGS
	./$(MAIN_AST) $(AST_CLASSES_DIR)