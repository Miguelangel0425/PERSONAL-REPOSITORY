# Makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
SOURCES = src/main.cpp src/parking_manager.cpp src/vehicle.cpp src/input_validator.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = parking_system

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(EXECUTABLE)