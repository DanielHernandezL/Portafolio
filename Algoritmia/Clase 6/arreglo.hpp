#ifndef ARREGLO_HPP
#define ARREGLO_HPP

#include <iostream>

using namespace std;

#define MAX 5

template <class T>
class Arreglo
{
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

    void agregarFinal(const T& elemento) {//declaraciones de clase en mayusculas objetos de las clases en minusculas
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
        //mover a la derecha
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

        //mover de derecha a izquierda
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

        //mover a la derecha
        for (size_t i = cont; i > posicion; i--){
            arreglo[i] = arreglo[i-1];
        }
        arreglo[posicion] = elemento;
        cont++;
    }

    void eliminar(size_t posicion){
        if(vacia()){
            cout << "Tra vacia" << endl;
            return;
        }
        if (posicion >= cont){
            cout << "Posicion no valida" << endl;
            return;
        }
        //mover a la izquierda
        for(size_t i = posicion; i< cont -1; i++){
            arreglo[i] = arreglo[i+1];
        }
        cont --;
    }
    void expandir(){
        //Crear nuevo arreglo
        T* nuevo = new T[tam+MAX];
        //Copiar los arreglo al nuevo arreglo dinamico
        for(size_t i = 0; i < tam; i++){
            nuevo[i] = arreglo[i];
        }

        //Liberar los arreglo viejos
        delete []arreglo;
        //Enlazar hacia el nuevo arreglo dinamico
        arreglo = nuevo;
        //Actualizar el tamaño del arreglo
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
        //Copiar los arreglo al nuevo arreglo dinamico
        for(size_t i = 0; i < cont; i++){

            reducido[i] = arreglo[i];
        }

        //Liberar los arreglo viejos
        delete []arreglo;
        //Enlazar hacia el nuevo arreglo dinamico
        arreglo = reducido;
        //Actualizar el tamaño del arreglo
        tam = cont;
    }

    size_t cantidad() {return cont;}
    size_t capacidad() {return tam;}

    T& operator[](size_t posicion) {return arreglo[posicion];}
};

#endif