#pragma once
#include <iostream>
class Matriz{
	private:
		int **matriz1;
		int **matriz2;
		int **matriz3;
		int dim;
	public:
		Matriz();
		Matriz(int**,int**,int**,int);
		int getDim();
		void setDim(int);
		int **getMatriz1();
		void setMatriz1(int **);
		int **getMatriz2();
		void setMatriz2(int **);
		int **getMatriz3();
		void setMatriz3(int **);
};