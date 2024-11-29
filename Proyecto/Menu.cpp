#include "menu.h"

template<typename T>
Menu<T>::Menu(const std::vector<T>& options) : options(options), selectedIndex(0) {}

template<typename T>
void Menu<T>::display() {
    system("cls");
    for (size_t i = 0; i < options.size(); ++i) {
        if (i == selectedIndex) {
            std::cout << " ---> " << options[i] << std::endl; // Opción seleccionada
        } else {
            std::cout << options[i] << std::endl; // Otras opciones
        }
    }
}

template<typename T>
void Menu<T>::moveUp() {
    if (selectedIndex == 0) {
        selectedIndex = options.size() - 1; // Volver a la última opción
    } else {
        --selectedIndex;
    }
}

template<typename T>
void Menu<T>::moveDown() {
    if (selectedIndex == options.size() - 1) {
        selectedIndex = 0; // Volver a la primera opción
    } else {
        ++selectedIndex;
    }
}

template<typename T>
T Menu<T>::select() {
    return options[selectedIndex];
}


template class Menu<std::string>;