#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>

template<typename T>
class Menu {
public:
    Menu(const std::vector<T>& options);
    void display();
    void moveUp();
    void moveDown();
    T select();

private:
    std::vector<T> options;
    size_t selectedIndex;
};
#include "Menu.cpp"

#endif // MENU_H