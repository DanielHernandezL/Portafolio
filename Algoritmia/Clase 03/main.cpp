#include <iostream>
#include "videojuego.h"
using namespace std;


int main(){
    //Computadora p02 = Computadora(10, 64, 6080.99, 16);
    Computadora p02;
    p02.setModelow(10);
    p02.setRom(64);
    p02.setPrecio(6080.99);
    p02.setRam(16);
    Computadora p03;
    p03.setModelow(12);
    p03.setRom(240);
    p03.setPrecio(6580.92);
    p03.setRam(32);

    Laboratorio lb;

    lb.agregarComputadora(p02);
    lb.agregarComputadora(p03);
    
    lb.mostrar();

    // cout << p03.getNombre() << endl;
    // cout << p03.getTipo() << endl;
    // cout << p03.getFuerza() << endl;
    // cout << p03.getSalud() << endl;
    return 0;
}