CXX = g++
CXXFLAGS = -std=c++17 -I./src -I./test
SRC_DIR = src
TEST_DIR = test

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*/*.cc)

# Test executables
TEST_EXECUTABLES = tokens lexer ast parser regex

# Use bash for handling the syntax
SHELL := /bin/bash

# Rules for each test
tokens: test/test_tokens/test_tokens.cc $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SRC_FILES)

ast: test/test_ast/test_ast.cc $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SRC_FILES)

lexer: test/test_lexer/test_lexer.cc $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SRC_FILES)

parser: test/test_parser/test_parser.cc $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SRC_FILES)

regex: test/test_regex/test_regex.cc $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SRC_FILES)

# Default target
all: $(TEST_EXECUTABLES)
	@echo "Running all tests..."
	@time ( \
		for test in $(TEST_EXECUTABLES); do \
			echo "Running $$test..."; \
			if [ -f ./$$test ]; then \
				./$$test || exit 1; \
			else \
				echo "Error: $$test executable not found!"; \
				exit 1; \
			fi; \
		done )
	@echo "All tests passed!"

# Clean up
clean:
	rm -f $(TEST_EXECUTABLES)
