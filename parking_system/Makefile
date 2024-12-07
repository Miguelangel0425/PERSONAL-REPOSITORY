CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS = 

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
DATA_DIR = data

# Archivos fuente
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Nombre del ejecutable
EXEC = parking_system

# Regla principal
all: $(BUILD_DIR) $(DATA_DIR) $(EXEC)

# Crear directorios
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DATA_DIR):
	mkdir -p $(DATA_DIR)

# Enlazar el ejecutable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar archivos fuente
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -rf $(BUILD_DIR) $(EXEC)

.PHONY: all clean