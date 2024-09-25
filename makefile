# # Compiler
# CXX = g++

# # Compiler flags
# CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# # SFML flags and libs
# SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# # Source files
# SOURCES = main.cpp tree.cpp Complex.cpp
# TEST_SOURCES = tests.cpp  # Ensure this file exists

# # Object files
# OBJECTS = $(SOURCES:.cpp=.o)
# TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# # Executable names
# MAIN_EXECUTABLE = tree_complex_demo
# TEST_EXECUTABLE = test_demo

# # Default target
# all: $(MAIN_EXECUTABLE) $(TEST_EXECUTABLE)

# # Linking the main executable
# $(MAIN_EXECUTABLE): $(OBJECTS)
# 	$(CXX) $(OBJECTS) -o $(MAIN_EXECUTABLE) $(SFML_FLAGS)

# # Linking the test executable
# $(TEST_EXECUTABLE): $(TEST_OBJECTS)  # Just need test objects for this
# 	$(CXX) $(TEST_OBJECTS) -o $(TEST_EXECUTABLE) $(SFML_FLAGS)

# # Compiling source files
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Clean target
# clean:
# 	rm -f $(OBJECTS) $(TEST_OBJECTS) $(MAIN_EXECUTABLE) $(TEST_EXECUTABLE)

# # Phony targets
# .PHONY: all clean

# Variables
CXX = g++
# With Coverage falgs
CXXFLAGS = -std=c++17 -Wall -I/usr/include/SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Target
TARGET = main

# Object files
OBJS = Complex.o main.o

TEST_OBJ = tests.o

# Rules
all: $(TARGET) tests

tree: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

tests: Complex.o tests.o
	$(CXX) Complex.o tests.o -o tests $(LDFLAGS)

Complex.o: Complex.cpp Complex.hpp
	$(CXX) -c Complex.cpp -o Complex.o $(CXXFLAGS)

Demo.o: Demo.cpp tree.cpp Complex.hpp
	$(CXX) -c Demo.cpp -o Demo.o $(CXXFLAGS)

tests.o: tests.cpp tree.cpp Complex.hpp
	$(CXX) -c tests.cpp -o tests.o $(CXXFLAGS)

# Phony targets
.PHONY: clean all tests coverage html_report

clean:
	rm -f $(OBJS) $(TARGET) tests.o tests *.gcno *.gcda *.gcov coverage.info
	rm -rf out

coverage: all
	./$(TARGET)
	@gcov $(SRCS)

html_report: coverage
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out


