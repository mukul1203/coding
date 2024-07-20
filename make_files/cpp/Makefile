# Compiler
CXX = g++

# Includes
INCLUDE = ../include

# Compiler flags
# -DFMT_HEADER_ONLY to use fmt library in header only mode
CXXFLAGS = -Wall -Wextra -std=c++2a -fdiagnostics-color=always -g -I $(INCLUDE) -DFMT_HEADER_ONLY

# cpp for test framework resides in include for now, may separate out later
TEST_FRAMEWORK_DIR = $(INCLUDE)/test_framework

# Source files
SRCS = main.cpp $(TEST_FRAMEWORK_DIR)/catch_amalgamated.cpp

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

# Rule to compile test framework source files into object files
$(OBJDIR)/%.o: $(TEST_FRAMEWORK_DIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Run
run: $(TARGET)
	./$(TARGET) --success --colour-mode ansi --verbosity high

# Clean rule
clean:
	rm -rf $(OBJDIR)

# Phony targets
.PHONY: all run clean
