#ifndef VIDEOJUEGO_H
#define VIDEOJUEGO_H

#include "personaje.h"

class Videojuego
{
    Personaje arreglo[5];
    size_t cont;
public:
    Videojuego();
    void agregarPersonaje(const Personaje &p);
    void mostrar();
};


#endif