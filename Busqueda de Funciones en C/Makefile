# Makefile para el Analizador de Complejidad

# Compilador y opciones
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Directorios
SRC_DIR = .
OBJ_DIR = obj

# Archivos fuente y objeto
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/FunctionExtractor.cpp
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
	@echo "Compilación completada: $(TARGET)"

# Patrón para compilar archivos .cpp a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compilado: $<"

# Dependencias específicas
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/FunctionExtractor.h
$(OBJ_DIR)/FunctionExtractor.o: $(SRC_DIR)/FunctionExtractor.cpp $(SRC_DIR)/FunctionExtractor.h

# Limpiar archivos compilados
clean:
	@echo "Limpiando archivos compilados..."
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Limpieza completada"

# Ejecutar el programa con un archivo de ejemplo
run: $(TARGET)
	@echo "Ejecutando analizador con ejemplo..."
	./$(TARGET) ejemplo.c

# Ejecutar con valgrind para detección de errores de memoria
debug: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) ejemplo.c

.PHONY: all clean run debug directories