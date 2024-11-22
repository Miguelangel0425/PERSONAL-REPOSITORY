#pragma once
#include "Matriz.h"
class Operaciones{
	public:
		Operaciones();
		Operaciones(Matriz);
		void segmentar();
		int **generarMatriz();
		void encerar();
		void procesarPot(int);
		void procesarMulti();
		void imprimir();
		void multiplicarEscalar(int **);
		void imprimirEscalar(int **);
	private:
		Matriz _matriz;
};