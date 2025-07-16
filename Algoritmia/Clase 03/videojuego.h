#ifndef VIDEOJUEGO_H
#define VIDEOJUEGO_H

#include "personaje.h"

class Laboratorio
{
    Computadora arreglo[5];
    size_t cont;
public:
    Laboratorio();
    void agregarComputadora(const Computadora &p);
    void mostrar();
};


#endif