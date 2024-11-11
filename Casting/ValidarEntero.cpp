#include "Validacion.h"

int Validacion<int>::ingresar(const char *msj){
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;

    std::cout << msj;

    while((c = getch()) != 13){
        if(c >= '0' && c <= '9'){
            std::cout << c;
            cad[i++] = c;
        } else if(c == 8 && i > 0){
            std::cout << "\b \b";
            i--;
        }
    }

    cad [i] = '\0';
    valor = atoi(cad);
    return valor;
}