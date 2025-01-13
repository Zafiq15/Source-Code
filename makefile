# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

SRC_DIR = .
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Target executable
TARGET = main.exe

# Source files
	
# Object files
OBJS = $(SRCS:.cpp=.obj)

# Default rule to build and run the executable
all: $(TARGET) run

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .obj files
%.obj: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run: $(TARGET)
	$(TARGET)

# Clean rule to remove generated files
clean:
	@if exist $(TARGET) del /q $(TARGET)
	@if exist *.obj del /q *.obj
