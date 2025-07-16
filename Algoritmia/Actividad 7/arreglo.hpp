#ifndef ARREGLO_HPP
#define ARREGLO_HPP

#include <iostream>
using namespace std;

#define MAX 5

template <class T>
class Arreglo{
    private:
        T* arreglo;
        size_t cont;
        size_t tam;
    public:
        Arreglo(){
            cont = 0;
            tam = MAX;
            arreglo = new T[tam];
        }

        void agregarFinal(const T& elemento) {
        if(llena()){
            cout << "Expandiendo..." << endl;
            expandir();
        } 
        arreglo[cont] = elemento;
        cont ++;
    }

    void agregarInicio(const T& elemento){
         if(llena()){
            cout << "Expandiendo..." << endl;
            expandir();
        } 
        for(size_t i = cont; i>0; i--){
            arreglo[i] = arreglo[i-1];
        }
        arreglo[0]= elemento;
        cont++;
    }

  
    bool llena(){
        return cont == tam;
    }

    bool vacia(){
        return cont == 0;
    }

    void eliminarFinal(){
        if(vacia()){
            cout << "Arreglo vacio, no se puede eliminar" << endl;
            return;
        }
        cont--;
    }

    void eliminarInicio(){
        if(vacia()){
            cout << "Arreglo vacio, no se puede eliminar" << endl;
            return;
        }

        for(size_t i = 0; i< cont -1; i++){
            arreglo[i] = arreglo[i+1];
        }
        cont--;
    }

    void insertar(const T& elemento, size_t posicion){
        if(llena()){
            cout << "Arreglo vacio, no se puede eliminar" << endl;
            return;
        }
        if (posicion >= cont){
            cout << "Posicion no valida" << endl;
        }

        for (size_t i = cont; i > posicion; i--){
            arreglo[i] = arreglo[i-1];
        }
        arreglo[posicion] = elemento;
        cont++;
    }

    void eliminar(size_t posicion){
        if(vacia()){
            cout << "Laboratorio vacio" << endl;
            return;
        }
        if (posicion >= cont){
            cout << "Posicion no valida" << endl;
            return;
        }
        for(size_t i = posicion; i< cont -1; i++){
            arreglo[i] = arreglo[i+1];
        }
        cont --;
    }
    void expandir(){
        T* nuevo = new T[tam+MAX];
        for(size_t i = 0; i < tam; i++){
            nuevo[i] = arreglo[i];
        }

        delete []arreglo;
        arreglo = nuevo;
        tam = tam + MAX;
    }

    void encoger(){
        if(vacia()){
            
            return;
        }

        if(llena()){
            return;
        }

        T* reducido = new T[cont];
        for(size_t i = 0; i < cont; i++){

            reducido[i] = arreglo[i];
        }

        delete []arreglo;
        arreglo = reducido;
        tam = cont;
    }

    size_t cantidad() {return cont;}
    size_t capacidad() {return tam;}

    T& operator[](size_t posicion) {return arreglo[posicion];}
};

#endif