#pragma once
#include <iostream>
#include <vector>
#include "Lista.h"
#include "ListaPropietarios.h"


using namespace std;

void menu(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial, ListaPropietarios &listaPropietarios);
int menuInteractivo(const vector<string> &opciones, const string &titulo = "Menu Interactivo");
void menuBusquedaAvanzada(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial);
