#ifndef COMPUTADORA_HPP
#define COMPUTADORA_HPP

#include <iostream>
using namespace std;

class Computadora{
    private:
        string sistema;
        string nombre;
        double RAM;
        double ROM;
        
    public:
        Computadora(){
        }
        Computadora(const string &sistema, const string &nombre, double RAM, double ROM){
            this->sistema = sistema;
            this->nombre = nombre;
            this->RAM = RAM;
            this->ROM = ROM;
        }
    void setSistema(const string &v){
        sistema=v;
    } 
    string getSistema(){
        return sistema;
    }
    void setNombre(const string &v){
        nombre=v;
    }
    string getNombre(){
        return nombre;
    }
    void setram(double v){
        RAM=v;
    }
    double getram(){
        return RAM;
    }
    void setrom(double v){
        ROM=v;
    }
    double getrom(){
        return ROM;
    }
   
};

#endif