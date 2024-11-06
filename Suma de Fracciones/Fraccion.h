#ifndef FRACCION_H
#define FRACCION_H

class Fraccion {
    private: 
        int numerador;
        int denominador;

        void  simplificar();

    public:
        
        Fraccion(); // Constructor por defecto

        Fraccion(int num, int den); // Constructor con parametros

        ~Fraccion();    // Destructor 

        void setNumerador(int num) {
            numerador = num;
        }

        void setDenominador(int den) {
            denominador = den;
        }

        int getNumerador() { 
            return numerador;
        }

        int getDenominador() {
            return denominador;
        }
};

#endif // FRACCION_H