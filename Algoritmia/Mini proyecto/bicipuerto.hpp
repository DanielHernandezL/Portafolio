#ifndef BICIPUERTO_HPP
#define BICIPUERTO_HPP
#include <fstream>
#include <iostream>
#include <iomanip>
#include "bicicleta.hpp"
#include "arreglo.hpp"

#define MAX 50

class Bicipuerto
{
private:
    Arreglo<Bicicleta> bicicletas;
    string nombreBicipuerto;
public:
    Bicipuerto(){

    }

void mostrar(){
        for (size_t i = 0; i < bicicletas.cantidad(); i++)
        {
            Bicicleta& bicicleta = bicicletas[i];
            cout << bicicleta << endl;
        }
        
    }

    void agregarFinalBicicleta(const Bicicleta& bicicleta) {
        bicicletas.agregarFinalBicicleta(bicicleta);
    }

    void eliminarFinalBicicleta(){
        bicicletas.eliminarFinalBicicleta();
        }

    void respaldar_csv(){
        ofstream archivo("Bicipuerto.csv");

        if(archivo.fail()){
            cout << "Error al crear el archivo" << endl;
            return;
    }
    for(size_t i= 0; i < bicicletas.cantidad(); i++){
        Bicicleta& bicicleta = bicicletas[i];

        archivo << bicicleta.getId() << ","
                << bicicleta.getTiempu() <<","
                << bicicleta.getMtr() <<  endl;
        }

    archivo.close();
    }

};
#endif