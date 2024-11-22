#include "Validacion.h"

float Validacion::ingresar(const char *msj){
    char cad[10];
    char c;
    int i = 0;
    float valor = 0;
    bool punto_decimal = false;

    std::cout << msj;

    while((c = getch()) != 13){
        if(c >= '0' && c <= '9'){
            std::cout << c;
            cad[i++] = c;
        } else if(c == '.' && !punto_decimal){
            punto_decimal = true;
            std::cout << c;
            cad[i++] = c;
        } else if(c == 8 && i > 0){
            std::cout << "\b \b";
            i--;
        }
    }
    cad [i] = '\0';
    valor = atof(cad);
    return valor;
}