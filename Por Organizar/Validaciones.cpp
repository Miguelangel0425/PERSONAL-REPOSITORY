/***********************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                  *
 * Proposito:                      Validaciones con casting            *
 * Autor:                          Miguel Caiza                        *
 * Fecha de creacion:              06/10/2024                          *
 * Fecha de modificacion:          07/11/2024                          *
 * Materia:                        Estructura de datos                 *
 * NRC :                           1978                                *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

using namespace std;

int ingresar(char *);

//Ingresar enteros------------------------------------------------------------------------

int ingresar(char *msj){
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    printf("%s", msj);
    while((c = getch()) != 13){
        if (c >= '0' && c <= '9'){
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8) {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i++] = '\0';
    valor = atoi(cad);
    return valor;
}


//Ingresar una letra-------------------------------------------------------------------------
char ingresarLetra(char *);
char ingresarLetra(char *msj) {
    char c;
    printf("%s", msj);
    while (true) {
        c = getch();
        if (isalpha(c)) {
            printf("%c", c);
            return c;
        } else if (c == 8) {
            printf("\b \b");
        }
    }
}



//Ingresar float------------------------------------------------------------------------------

float ingresarFloat(char *);
float ingresarFloat(char *msj){
    char cad[10];
    char c;
    int i = 0;
    float valor = 0;
    printf("%s", msj);
    while((c = getch()) != 13){
        if (c >= '0' && c <= '9'){
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8) {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (c == 46) {
            bool aux = false;
            for (int j = 0; cad[j] != '\0'; j++) {
                if (cad[j] == 46){
                    aux = true;
                    break;
                }
            }
            if(aux == false){
                printf("%c", c);
                cad[i++] = c;
            }
        }
    }
    cad[i++] = '\0';
    for (int j = 0; cad[j] != '\0'; j++) {
        valor = atof(cad);
    }
    return valor;
}

//ingresar un string---------------------------------------------------------------------------------------
string ingresarString(char *);
string ingresarString(char *msj) {
    char cad[10];
    char c;
    int i = 0;
    string valor;
    printf("%s", msj);
    while ((c = getch()) != 13) {
        if (isalpha(c)) {
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8) {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i] = '\0';
    for (int j = 0; cad[j] != '\0'; j++) {
        valor = valor + cad[j];
    }

    return valor;
}

//Ingresar double------------------------------------------------------------------------------
double ingresarDouble(char *msj){
    char cad[20];
    char c;
    int i = 0;
    double valor = 0;
    printf("%s", msj);
    bool puntoDecimal = false;
    while((c = getch()) != 13){
        if (c >= '0' && c <= '9'){
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8) {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (c == '.' && !puntoDecimal) {
            puntoDecimal = true;
            printf("%c", c);
            cad[i++] = c;
        }
    }
    cad[i] = '\0';
    valor = atof(cad);
    return valor;
}

int SumarEnteros(int obj1, int obj2){
    int temporal;
    temporal = obj1 + obj2;
    return temporal;
}

float SumarFlotantes(float obj1, float obj2){
    ingresarString("Ingrese su nombre: ");
    float temporal;
    temporal = obj1 + obj2;
    return temporal;
}

int main(){
    int numero1 = ingresar("ingrese un valor entero: ");
    cout << endl;
    int numero2 = ingresar("Ingrese un valor entero: ");
    cout << endl;
    int Resultado = SumarEnteros(numero1, numero2);
    cout << Resultado << endl;

    float num1 = ingresarFloat("ingrese un valor flotante: ");
    cout << endl;
    float num2 = ingresarFloat("Ingrese un valor flotante: ");
    cout << endl;
    float Respuesta = SumarFlotantes(num1, num2);
    cout << endl;
    cout << Respuesta << endl;



    /*cout << imprimirNumeros << endl;
    char imprimirLetras = ingresarLetra("ingrese letras: ");
    cout << endl;
    cout << imprimirLetras << endl;
    float imprimirFloats = ingresarFloat("ingrese un valor flotante: ");
    cout << endl;
    cout << imprimirFloats << endl;
    string imprimirString = ingresarString("ingrese un string: ");
    cout << endl;
    cout << imprimirString << endl;
    double imprimirDouble = ingresarDouble("Ingrese un valor double: ");
    cout << endl << imprimirDouble << endl;*/

}
