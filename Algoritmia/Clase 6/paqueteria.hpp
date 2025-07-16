#ifndef PAQUETERIA_HPP
#define PAQUETERIA_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include "paquete.hpp"
#include "arreglo.hpp"
using namespace std;

#define MAX 5

class Paqueteria
{
private:
    Arreglo<Paquete> paquetes;
    string nombrePaqueteria;
public:
    Paqueteria(){

    }
    
    void setNombrePaqueteria(const string& nombre){
        nombrePaqueteria = nombre;
    }
    string getNombrePaqueteria(){
        return nombrePaqueteria;
    }

    void agregarFinal(const Paquete& paquete) {//declaraciones de clase en mayusculas objetos de las clases en minusculas
        paquetes.agregarFinal(paquete);
    }

    void agregarInicio(const Paquete& paquete){
         paquetes.agregarInicio(paquete);
    }

    void mostrar(){
        for (size_t i = 0; i < paquetes.cantidad(); i++)
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
        for (size_t i = 0; i < paquetes.cantidad(); i++)
        {
            Paquete& paquete = paquetes[i];
            archivo << paquete << endl;
        }

        archivo.close();
    }

    void mostrar_tabla(){
        cout << "tam=" << paquetes.capacidad() << endl;
        cout << "cont=" << paquetes.cantidad() << endl;
        cout << left;
        cout << setw(10) << "Origen"
             << setw(10) << "Destino"
             << setw(15) << "Destinatario"
             << setw(5) << "Peso"
             << endl;
        for (size_t i = 0; i < paquetes.cantidad(); i++){
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
        for (size_t i = 0; i < paquetes.cantidad(); i++){
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
    for(size_t i= 0; i < paquetes.cantidad(); i++){
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
        return paquetes.llena();
    }

    bool vacia(){
        return paquetes.vacia();
    }

    void eliminarFinal(){
        paquetes.eliminarFinal();
        }
        

    void eliminarInicio(){
        paquetes.eliminarInicio();
    }

    void insertar(const Paquete& paquete, size_t posicion){
        paquetes.insertar(paquete, posicion);
    }

    void eliminar(size_t posicion){
       paquetes.eliminar(posicion);
    }

    void expandir(){
        paquetes.expandir();

    }

    void encoger(){
       paquetes.encoger();
    }
};

#endif