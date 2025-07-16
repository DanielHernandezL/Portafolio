#include "personaje.h"

Personaje::Personaje()
{

}

Personaje::Personaje(const string &nombre,
                const string &tipo,
                float fuerza,
                int salud)
{
    this->nombre = nombre;
    this->tipo = tipo;
    this->fuerza = fuerza;
    this->salud = salud;
}

void Personaje::setNombre(const string &v)
{
    nombre = v;
}
string Personaje::getNombre()
{
    return nombre;
}

void Personaje::setTipo(const string &v)
{
    tipo = v;
}

string Personaje::getTipo()
{
    return tipo;
}
void Personaje::setFuerza(float v)
{
    fuerza = v;
}

float Personaje::getFuerza()
{
    return fuerza;
}

void Personaje::setSalud(int v)
{
    salud = v;
}

int Personaje::getSalud()
{
    return salud;
}
