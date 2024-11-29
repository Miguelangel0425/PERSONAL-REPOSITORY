#include "menu.h"
#include <conio.h> // Para _getch()
#include <iostream>
#include <vector>

// Funciones que representan acciones para cada opción del menú
void option1Action() {
    std::cout << "Has seleccionado Opcion 1: Realizando accion para Opcion 1..." << std::endl;
                  system("pause");
}

void option2Action() {
    std::cout << "Has seleccionado Opcion 2: Realizando accion para Opcion 2..." << std::endl;
                  system("pause");
}

void option3Action() {
    std::cout << "Has seleccionado Opcion 3: Realizando accion para Opcion 3..." << std::endl;
                  system("pause");
}

// Función que maneja la selección del menú
void handleMenuSelection(const std::string& selectedOption) {
    if (selectedOption == "Opcion 1") {
        option1Action();
    } else if (selectedOption == "Opcion 2") {
        option2Action();
    } else if (selectedOption == "Opcion 3") {
        option3Action();
    } else if (selectedOption == "Salir") {
        std::cout << "Saliendo del programa..." << std::endl;
        system("pause");
    }
}

int main() {
    std::vector<std::string> options = {"Opcion 1", "Opcion 2", "Opcion 3", "Salir"};
    Menu<std::string> menu(options);

    char input;
    while (true) {
        menu.display();
        input = _getch();

        switch (input) {
            case 'w':
                menu.moveUp();

                break;
            case 's':
                menu.moveDown(); 
                break;
            case 13:
                {
                    std::string selectedOption = menu.select();
                    handleMenuSelection(selectedOption);
                    if (selectedOption == "Salir") {
                        return 0;
                    }
                }
                break;
            default:
                break;
        }
    }

    return 0;
}
