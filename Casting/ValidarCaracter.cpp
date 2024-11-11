#include "Validacion.h"

char Validacion<char>::ingresar(const char *msj){
    char c;
    std::cout << msj;
    while (true){

        c = getch();
        if(isalpha(c)){
            std::cout << c;
            return c;
        } else if(c == 8){
            std::cout << "\b \b";
        }
    }
}