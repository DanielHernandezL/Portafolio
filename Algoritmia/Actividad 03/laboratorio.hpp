#ifndef LABORATORIO_HPP
#define LABORATORIO_HPP

#include <iostream>
#include "computadora.hpp"
using namespace std;

class Laboratorio{
    private: 
        Computadora computadoras[5];
        size_t cont;
    public:
    Laboratorio(){
        cont=0;
    }
    void agregar(const Computadora &computadora){
        if(cont>=5){
            cout << "Laboratorio lleno" << endl;
            return;
        }
        computadoras[cont]= computadora;
        cont++;
    }
    void mostrar(){
        for (size_t i = 0; i < cont; i++){
            Computadora &computadora=computadoras[i];

            cout <<"Sistem Operativo: "<< computadora.getSistema() <<endl;
            cout <<"RAM: "<< computadora.getram() <<endl;
            cout <<"ROM: "<< computadora.getrom() <<endl;
            cout <<"Nombre de la computadora: "<< computadora.getNombre() <<endl;
            cout << endl;
        }
    }
};




#endif