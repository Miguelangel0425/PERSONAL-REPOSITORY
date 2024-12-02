#include <iostream>

class Vector {
public:
    int x, y;

    Vector(int x = 0, int y = 0) : x(x), y(y) {}

    Vector operator+(const Vector& other) {
        
        auto add = [](int a, int b) { return a + b; };
        return Vector(add(x, other.x), add(y, other.y));
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")\n";
    }
};

int main() {
    Vector v1(1, 2);
    Vector v2(3, 4);

    // Sobrecarga del operador '+'
    Vector v3 = v1 + v2;
    v3.print();  // Imprime: (4, 6)

    return 0;
}
