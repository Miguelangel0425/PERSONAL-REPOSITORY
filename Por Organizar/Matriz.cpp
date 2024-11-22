#include <iostream>
#include "Matriz.h"
Matriz::Matriz(){
}
Matriz::Matriz(int **matriz1, int **matriz2, int **matriz3, int dim ){
	this->matriz1=matriz1;
	this->matriz2=matriz2;
	this->matriz3=matriz3;
	this->dim=dim;
}
int Matriz::getDim(){
	return dim;
}
void Matriz::setDim(int dim){
	this->dim=dim;
}
int** Matriz::getMatriz1(){
	return matriz1;
}
void Matriz::setMatriz1(int **matriz1){
	this-> matriz1=matriz1;
}

int **Matriz::getMatriz2(){
	return matriz2;
}
void Matriz::setMatriz2(int **matriz2){
	this-> matriz2=matriz2;
}

int **Matriz::getMatriz3(){
	return matriz3;
}
void Matriz::setMatriz3(int **matriz3){
	this->matriz3=matriz3;
}
