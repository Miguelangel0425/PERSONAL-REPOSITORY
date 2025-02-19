# Makefile para el Analizador de Complejidad

# Compilador y opciones
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Directorios
SRC_DIR = .
OBJ_DIR = obj

# Archivos fuente y objeto
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/FunctionExtractor.cpp $(SRC_DIR)/ComplexityVisualizer.cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Nombre del ejecutable
TARGET = analizador_complejidad

# Regla principal
all: directories $(TARGET)

# Crear directorio de objetos si no existe
directories:
	@mkdir -p $(OBJ_DIR)

# Compilación del ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Patrón para compilar archivos .cpp a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dependencias específicas
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/FunctionExtractor.h $(SRC_DIR)/ComplexityVisualizer.h
$(OBJ_DIR)/FunctionExtractor.o: $(SRC_DIR)/FunctionExtractor.cpp $(SRC_DIR)/FunctionExtractor.h
$(OBJ_DIR)/ComplexityVisualizer.o: $(SRC_DIR)/ComplexityVisualizer.cpp $(SRC_DIR)/ComplexityVisualizer.h $(SRC_DIR)/FunctionExtractor.h

# Limpiar archivos compilados
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Ejecutar el programa con un archivo de ejemplo
run: $(TARGET)
	./$(TARGET) ejemplo.c

.PHONY: all clean run directories