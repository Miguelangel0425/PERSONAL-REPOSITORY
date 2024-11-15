#include <iostream>
#include "Matriz.h"
#include "Operaciones.h"

// Función para solicitar y leer un número entero
int ingresar(const char* msj) {
	int dim;
	std::cout << "\n" << msj << "\n";
	std::cin >> dim;
	return dim;
}

// Función para inicializar y realizar operaciones con matrices
void iniciar(int dim) {
	int pot;
	int **m1 = nullptr;
	int **m2 = nullptr;
	int **m3 = nullptr;

	// Crear objeto Matriz y Operaciones
	Matriz matriz(m1, m2, m3, dim);
	Operaciones operaciones(matriz);

	// Segmentación y llenado de matrices
	operaciones.segmentar();
	operaciones.encerar();

	// Generar y mostrar matrices iniciales
	std::cout << "\nMatriz 1 inicializada:\n";
	m1 = operaciones.generarMatriz();
	matriz.setMatriz1(m1);
	operaciones.imprimir();

	std::cout << "\nMatriz 2 inicializada:\n";
	m2 = operaciones.generarMatriz();
	matriz.setMatriz2(m2);
	operaciones.imprimir();

	// Potencia de matriz
	pot = ingresar("Ingrese la potencia de la matriz");
	operaciones.procesarPot(pot);
	std::cout << "\nMatriz R (resultado de potencia):\n";
	operaciones.imprimir();

	// Multiplicación de matrices
	std::cout << "\nMatriz Multiplicación:\n";
	operaciones.procesarMulti();
	operaciones.imprimir();

	// Multiplicación escalar de una matriz
	std::cout << "\nMatriz Escalar (multiplicada por 7):\n";
	operaciones.multiplicarEscalar(m1); // Multiplica m1 por el escalar
}

// Función principal
int main(int argc, char** argv) {
	int dim = ingresar("Ingrese la dimension de la matriz");
	iniciar(dim);
	return 0;
}