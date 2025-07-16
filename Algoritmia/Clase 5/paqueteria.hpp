#ifndef PAQUETERIA_HPP
#define PAQUETERIA_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include "paquete.hpp"
using namespace std;

#define MAX 50

class Paqueteria
{
private:
    Paquete* paquetes;
    size_t cont;
    size_t tam;
public:
    Paqueteria(){
        cont = 0;
        tam = MAX;
        paquetes = new Paquete[tam];
    }

    void agregarFinal(const Paquete& paquete) {//declaraciones de clase en mayusculas objetos de las clases en minusculas
        if(llena()){
            cout << "Expandiendo..." << endl;
            expandir();
        } 
        paquetes[cont] = paquete;
        cont ++;
    }

    void agregarInicio(const Paquete& paquete){
         if(llena()){
            cout << "Expandiendo..." << endl;
            expandir();
        } 
        //mover a la derecha
        for(size_t i = cont; i>0; i--){
            paquetes[i] = paquetes[i-1];
        }
        paquetes[0]= paquete;
        cont++;
    }

    void mostrar(){
        for (size_t i = 0; i < cont; i++)
        {
            Paquete& paquete = paquetes[i];
            cout << paquete << endl;
        }
        
    }

    void respaldar(){
        ofstream archivo("paqueteria.txt");

        if(archivo.fail()){
            cout << "Error al crear el archivo" << endl;
            return;
        }
        for (size_t i = 0; i < cont; i++)
        {
            Paquete& paquete = paquetes[i];
            archivo << paquete << endl;
        }

        archivo.close();
    }

    void mostrar_tabla(){
        cout << "tam=" << tam << endl;
        cout << "cont=" << cont << endl;
        cout << left;
        cout << setw(10) << "Origen"
             << setw(10) << "Destino"
             << setw(15) << "Destinatario"
             << setw(5) << "Peso"
             << endl;
        for (size_t i = 0; i < cont; i++){
            Paquete& paquete = paquetes[i];
            
            cout << setw(10) << paquete.getOrigen();
            cout << setw(10) << paquete.getDestino();
            cout << setw(15) << paquete.getDestinatario();
            cout << setw(5) << paquete.getPeso();
            cout << endl;
        }
    }
    void respaldar_tabla(){
        ofstream archivo("paqueteria_tabla.txt");

        if(archivo.fail()){
            cout << "Error al crear el archivo" << endl;
            return;
    }
    archivo << left;
        archivo << setw(10) << "Origen"
             << setw(10) << "Destino"
             << setw(15) << "Destinatario"
             << setw(5) << "Peso"
             << endl;
        for (size_t i = 0; i < cont; i++){
            Paquete& paquete = paquetes[i];
            
            archivo << setw(10) << paquete.getOrigen();
            archivo << setw(10) << paquete.getDestino();
            archivo << setw(15) << paquete.getDestinatario();
            archivo << setw(5) << paquete.getPeso();
            archivo << endl;
        }

        archivo.close();
    }

    void respaldar_csv(){
        ofstream archivo("paqueteria.csv");

        if(archivo.fail()){
            cout << "Error al crear el archivo" << endl;
            return;
    }
    for(size_t i= 0; i < cont; i++){
        Paquete& paquete = paquetes[i];

        archivo << paquete.getOrigen() << ","
                << paquete.getDestino() <<","
                << paquete.getDestinatario() << ","
                << paquete.getPeso() << endl;
        }

    archivo.close();
    }

    void recuperar_csv(){
        ifstream archivo("paqueteria.csv");
        
        if(archivo.fail()){
            cout << "Error al abrir el archivo" << endl;
            return;
        }

        while(true){
            Paquete paquete;
            string temp;

            getline(archivo, temp, ',');
            if (archivo.eof()) break; //End of line
            paquete.setOrigen(temp);

            getline(archivo, temp, ',');
            paquete.setDestino(temp);

            getline(archivo, temp, ',');
            paquete.setDestinatario(temp);

            getline(archivo, temp);
            paquete.setPeso(stod(temp));

            agregarFinal(paquete);
            
        }
        archivo.close();
    }

    bool llena(){
        return cont == tam;
    }

    bool vacia(){
        return cont == 0;
    }

    void eliminarFinal(){
        if(vacia()){
            cout << "Paqueteria vacia, no se puede eliminar" << endl;
            return;
        }
        cont--;
    }

    void eliminarInicio(){
        if(vacia()){
            cout << "Paqueteria vacia, no se puede eliminar" << endl;
            return;
        }

        //mover de derecha a izquierda
        for(size_t i = 0; i< cont -1; i++){
            paquetes[i] = paquetes[i+1];
        }
        cont--;
    }

    void insertar(const Paquete& paquete, size_t posicion){
        if(llena()){
            cout << "Paqueteria vacia, no se puede eliminar" << endl;
            return;
        }
        if (posicion >= cont){
            cout << "Posicion no valida" << endl;
        }

        //mover a la derecha
        for (size_t i = cont; i > posicion; i--){
            paquetes[i] = paquetes[i-1];
        }
        paquetes[posicion] = paquete;
        cont++;
    }

    void eliminar(size_t posicion){
        if(vacia()){
            cout << "paquetera vacia" << endl;
            return;
        }
        if (posicion >= cont){
            cout << "Posicion no valida" << endl;
            return;
        }
        //mover a la izquierda
        for(size_t i = posicion; i< cont -1; i++){
            paquetes[i] = paquetes[i+1];
        }
        cont --;
    }
    void expandir(){
        //Crear nuevo arreglo
        Paquete* nuevo = new Paquete[tam+MAX];
        //Copiar los paquetes al nuevo arreglo dinamico
        for(size_t i = 0; i < tam; i++){
            nuevo[i] = paquetes[i];
        }

        //Liberar los paquetes viejos
        delete []paquetes;
        //Enlazar hacia el nuevo arreglo dinamico
        paquetes = nuevo;
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

        Paquete* reducido = new Paquete[cont];
        //Copiar los paquetes al nuevo arreglo dinamico
        for(size_t i = 0; i < cont; i++){

            reducido[i] = paquetes[i];
        }

        //Liberar los paquetes viejos
        delete []paquetes;
        //Enlazar hacia el nuevo arreglo dinamico
        paquetes = reducido;
        //Actualizar el tamaño del arreglo
        tam = cont;
    }
};

#endif