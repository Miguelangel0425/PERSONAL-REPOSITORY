#include "Fraccion.h"
#include <iostream>
#include <stdexcept>
#include <numeric>

Fraccion::Fraccion() : numerador(0), denominador(1) {
}

Fraccion::Fraccion(int num, int den){
    setNumerador(num);
    setDenominador(den);
};

Fraccion::~Fraccion() {
}

void Fraccion::setNumerador(int num) {
    numerador = num;
    simplificar();
}

void Fraccion::setDenominador(int den) {
    if (den == 0) {
        throw std::invalid_argument("El denominador no puede ser 0");
    }
    denominador = den;
    simplificar();
}

int Fraccion::getNumerador() const {
    return numerador;
}

int Fraccion::getDenominador() const {
    return denominador;
}

void Fraccion::simplificar() {
    int gcd = std::gcd(numerador, denominador); 
    numerador /= gcd;
    denominador /= gcd;

    if (denominador < 0) {
        numerador = -numerador;
        denominador = -denominador;
    }  
}

Fraccion sumar(const Fraccion& f1, const Fraccion& f2) {
    int num = f1.getNumerador() * f2.getDenominador() + f2.getNumerador() * f1.getDenominador();
    int den = f1.getDenominador() * f2.getDenominador();
    return Fraccion(num, den);
}