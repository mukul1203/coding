# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -fdiagnostics-color=always -g

TEST_DIR = ../test_framework

# Source files
SRCS = main.cpp $(TEST_DIR)/catch_amalgamated.cpp

# Object files directory
OBJDIR = build

# Executable
TARGET = $(OBJDIR)/main.out

# Objects (placing object files in the build directory)
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SRCS)))

# Default rule
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Rule to compile source files into object files
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile source files in src directory
$(OBJDIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean rule
clean:
	rm -rf $(OBJDIR)

# Phony targets
.PHONY: all clean
