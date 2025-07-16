#include "videojuego.h" 
Laboratorio::Laboratorio()
{
    cont = 0;
}

void Laboratorio::agregarComputadora(const Computadora &p)
{
    if(cont < 5){
        arreglo[cont] = p;
        cont++;
    }
    else{
        cout << "Arreglo lleno" << endl;
    }
}

void Laboratorio::mostrar()
{
    for(size_t i = 0; i < cont; i++){
        Computadora &p = arreglo [i];
        cout << "Version de Windows: " << p.getModelow() << endl;
        cout << "Memoria: " << p.getRom() << endl;
        cout << "Precio: " << p.getPrecio() << endl;
        cout << "RAM: " << p.getRam() << endl;
        cout << endl;
    }
}