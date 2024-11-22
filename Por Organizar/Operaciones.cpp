#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Operaciones.h"

Operaciones::Operaciones() {}

Operaciones::Operaciones(Matriz m1) {
	this->_matriz = m1;
}

// Asignar memoria para la matriz
void Operaciones::segmentar() {
	int** matriz;
	matriz = new int*[_matriz.getDim()];
	for (int j = 0; j < _matriz.getDim(); j++) {
		matriz[j] = new int[_matriz.getDim()];
	}
	_matriz.setMatriz3(matriz);
}

// Llenar la matriz con ceros
void Operaciones::encerar() {
	for (int i = 0; i < _matriz.getDim(); i++) {
		for (int j = 0; j < _matriz.getDim(); j++) {
			_matriz.getMatriz1()[i][j] = 0;
		}
	}
}

// Elevar la matriz a una potencia
void Operaciones::procesarPot(int exp) {
	for (int e = 1; e <= exp; e++) {
		for (int i = 0; i < _matriz.getDim(); i++) {
			for (int j = 0; j < _matriz.getDim(); j++) {
				for (int k = 0; k < _matriz.getDim(); k++) {
					_matriz.getMatriz3()[i][j] += _matriz.getMatriz2()[i][k] * _matriz.getMatriz2()[k][j];
				}
			}
		}
	}
}

// Multiplicar dos matrices
void Operaciones::procesarMulti() {
	for (int i = 0; i < _matriz.getDim(); i++) {
		for (int j = 0; j < _matriz.getDim(); j++) {
			_matriz.getMatriz3()[i][j] = 0;
			for (int k = 0; k < _matriz.getDim(); k++) {
				_matriz.getMatriz3()[i][j] += _matriz.getMatriz1()[i][k] * _matriz.getMatriz2()[k][j];
			}
		}
	}
}

// Imprimir la matriz 1
void Operaciones::imprimir() {
	std::cout << "La matriz 1 es:\n";
	for (int i = 0; i < _matriz.getDim(); i++) {
		for (int j = 0; j < _matriz.getDim(); j++) {
			std::cout << _matriz.getMatriz1()[i][j] << "\t";
		}
		std::cout << "\n";
	}
}

// Generar una matriz aleatoria
int** Operaciones::generarMatriz() {
	srand(time(NULL));
	int** matriz = new int*[_matriz.getDim()];
	for (int i = 0; i < _matriz.getDim(); i++) {
		matriz[i] = new int[_matriz.getDim()];
		for (int j = 0; j < _matriz.getDim(); j++) {
			matriz[i][j] = rand() % 3;
		}
	}
	return matriz;
}

// Imprimir una matriz pasada como parámetro
void Operaciones::imprimirEscalar(int** matriz) {
	std::cout << "\nLa matriz Parametrizada: \n";
	for (int i = 0; i < _matriz.getDim(); i++) {
		for (int j = 0; j < _matriz.getDim(); j++) {
			std::cout << matriz[i][j] << "\t";
		}
		std::cout << "\n";
	}
}

// Multiplicar una matriz por un escalar (7 en este caso)
void Operaciones::multiplicarEscalar(int** matriz) {
	std::cout << "\nLa matriz de 7:\n";
	for (int i = 0; i < _matriz.getDim(); i++) {
		for (int j = 0; j < _matriz.getDim(); j++) {
			matriz[i][j] = 7;
			std::cout << matriz[i][j] << "\t";
		}
		std::cout << "\n";
	}
}