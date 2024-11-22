#include "Validacion.h"

std:: String Validacion<std::string>::ingresar(const char *msj){
    std::string cad;
    char c;
    std:: String valor;
    std::cout << msj;
    while((c = getch) !13){
        if (isalpha(c)){
            std::cout << c;
            cad[i++] = c;   
        } else if(c == 8 && i > 0){
            std::cout << "\b \b";
            i--;
        }
    }
    cad [i] = '\0';
    valor = std::string(cad);
    return valor;
}