#include <iostream>
#include "arreglo.hpp"
using namespace std;

template <typename T>
void mostrar(Arreglo<T>& arreglo){
    for(size_t i = 0; i < arreglo.cantidad(); i++){
        cout << arreglo[i] << endl;
    }
}

int main(){
    Arreglo<int> enteros;
    enteros.agregarFinal(1);
    enteros.agregarFinal(3);

    mostrar(enteros);

    Arreglo<string> cadenas;
    cadenas.agregarFinal("Daniel");
    cadenas.agregarFinal("Hernandez");

    mostrar(cadenas);

    return 0;
}