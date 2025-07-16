#ifndef ARREGLO_HPP
#define ARREGLO_HPP
#include <iostream>
using namespace std;

#define MAX 50

template <class T>
class Arreglo
{
private:
    T* arreglo;
    size_t cont;
    size_t tam;
public:
    Arreglo(){
        cont = 0;
        tam = MAX;
        arreglo = new T[tam];
    }

void agregarFinalBicicleta(const Bicicleta &bicicleta) {
        if(llena()){
            cout << "Bicipuerto esta lleno" << endl;
            return;
        } 
        arreglo[cont] = bicicleta;
        cont ++;
    }

    void eliminarFinalBicicleta(){
        if(vacia()){
            cout << "No hay bicicletas registradas" << endl;
            return;
        }
        cont--;
    }


bool llena(){
        return cont == tam;
    }

    bool vacia(){
        return cont == 0;
    }

    size_t cantidad() {return cont;}
    size_t capacidad() {return tam;}

    T& operator[](size_t posicion) {return arreglo[posicion];}

};

#endif