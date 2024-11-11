#ifndef FRACCION_H
#define FRACCION_H

class Fraccion {
    private: 
        int numerador;
        int denominador;

        void  simplificar();

    public:
        
        Fraccion();

        Fraccion(int num, int den);

        ~Fraccion();

        void setNumerador(int num);

        void setDenominador(int den);
        

        int getNumerador() const;

        int getDenominador() const;
};

#endif