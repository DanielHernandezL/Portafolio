#ifndef PAQUETERIA_HPP
#define PAQUETERIA_HPP

#include <iostream>
#include "paquete.hpp"
using namespace std;

class Paqueteria
{
private:
    Paquete paquetes[5];
    size_t cont;
public:
    Paqueteria(){
        cont = 0;
    }

    void agregar(const Paquete& paquete) {//declaraciones de clase en mayusculas objetos de las clases en minusculas
        if(cont >= 4){
            cout << "Paqueteria llena";
            return;
        } 
        paquetes[cont] = paquete;
        cont ++;
    }

    void mostrar(){
        for (size_t i = 0; i < cont; i++)
        {
            Paquete& paquete = paquetes[i];
            
            cout <<"Origen: "<< paquete.getOrigen() <<endl;
            cout <<"Destino: "<< paquete.getDestino() <<endl;
            cout <<"Destinatario: "<< paquete.getDestinatario() <<endl;
            cout <<"Peso: "<< paquete.getPeso() <<endl;
        }
        
    }
};

#endif