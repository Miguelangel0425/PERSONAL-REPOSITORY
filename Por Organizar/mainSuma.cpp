#include <iostream>
#include <stdlib.h>
#include <time.h>
#define MAX 3
/*
Suma de matrices recursiva con memoria dinámica
*/

using namespace std;

int sumaRecursivaMatrices(int** mat1, int** mat2, int f, int c);

int sumaRecursivaMatrices(int** mat1, int** mat2, int f, int c) {
	if ((f == 0) && (c == 0)) {
		return mat1[f][c] + mat2[f][c];
	} else {
		if (f > -1) {
			c--;
			if (c >= -1)
				return mat1[f][c + 1] + mat2[f][c + 1] + sumaRecursivaMatrices(mat1, mat2, f, c);
			else
				return sumaRecursivaMatrices(mat1, mat2, f - 1, MAX - 1);
		}
	}
	return 0;
}

int main(int argc, char** argv) {
	// Crear matrices dinámicamente
	int** mat1 = (int**)malloc(MAX * sizeof(int*));
	int** mat2 = (int**)malloc(MAX * sizeof(int*));
	for (int i = 0; i < MAX; i++) {
		mat1[i] = (int*)malloc(MAX * sizeof(int));
		mat2[i] = (int*)malloc(MAX * sizeof(int));
	}

	// Llenar matrices con valores aleatorios
	srand(time(NULL));
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			mat1[i][j] = rand() % 1000;
			mat2[i][j] = rand() % 1000;
		}
	}

	// Mostrar matrices
	cout << "Matriz 1:\n";
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			cout << mat1[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "\nMatriz 2:\n";
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			cout << mat2[i][j] << "\t";
		}
		cout << endl;
	}

	// Calcular y mostrar la suma recursiva de las matrices
	cout << "\nSuma de todas las entradas de ambas matrices es: " << sumaRecursivaMatrices(mat1, mat2, MAX - 1, MAX - 1) << endl;

	return 0;
}