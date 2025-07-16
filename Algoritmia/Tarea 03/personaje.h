#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <iostream>
using namespace std;

class Personaje 
{
    string nombre;
    string tipo;
    float fuerza;
    int salud;
public:
        Personaje();
        Personaje(const string &nombre,
                  const string &tipo,
                  float fuerza,
                  int salud);
    void setNombre(const string &v);
    string getNombre();
    void setTipo(const string &v);
    string getTipo();
    void setFuerza(float v);
    float getFuerza();
    void setSalud(int v);
    int getSalud();
};  

#endif