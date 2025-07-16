#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <iostream>
using namespace std;

class Computadora 
{
    int modelow;
    double rom;
    float precio;
    double ram;
public:
        Computadora();
        Computadora(int modelow, double rom, float precio, double ram);

    void setModelow(int v);

    int getModelow();

    void setRom(double v);

    double getRom();

    void setPrecio(float v);

    float getPrecio();

    void setRam(double v);
    
    double getRam();
};  

#endif