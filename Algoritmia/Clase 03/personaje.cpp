#include "personaje.h"

Computadora::Computadora()
{

}

Computadora::Computadora(int modelow, double rom, float precio, double Ram)
{
    this->modelow = modelow;
    this->rom = rom;
    this->precio = precio;
    this->ram = ram;
}

void Computadora::setModelow(int v)
{
    modelow = v;
}

int Computadora::getModelow()
{
    return modelow;
}

void Computadora::setRom(double v)
{
    rom = v;
}

double Computadora::getRom()
{
    return rom;
}

void Computadora::setPrecio(float v)
{
    precio = v;
}

float Computadora::getPrecio()
{
    return precio;
}

void Computadora::setRam(double v)
{
    ram = v;
}

double Computadora::getRam()
{
    return ram;
}
