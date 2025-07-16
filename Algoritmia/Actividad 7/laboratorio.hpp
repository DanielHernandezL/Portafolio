#ifndef LABORATORIO_HPP
#define LABORATORIO_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include "computadora.hpp"
#include "arreglo.hpp"
using namespace std;

#define MAX 5

class Laboratorio
{
    private:
        Arreglo<Computadora> computadoras;
        string nombreLaboratorio;
    public:
        Laboratorio(){
        
        }

        void setNombreLaboratorio(const string& nombre){
            nombreLaboratorio = nombre;
        }
        string getNombreLaboratorio(){
            return nombreLaboratorio;
        }

        void agregarFinal(const Computadora& computadora){
            computadoras.agregarFinal(computadora);
        }

        void agregarInicio(const Computadora& computadora){
            computadoras.agregarInicio(computadora);
        }

        void mostrar(){
            for(size_t i = 0; i < computadoras.cantidad(); i++){
                Computadora& computadora = computadoras[i];
                cout << computadora << endl;
            }
        }

        void respaldar(){
            ofstream archivo("laboratorio.txt");

            if(archivo.fail()){
                cout << "Error al crear el archivo" << endl;
                return;
            }

            for(size_t i = 0; i < computadoras.cantidad(); i++){
                Computadora& computadora = computadoras[i];
                archivo << computadora << endl;
            }

            archivo.close();
        }

        void mostrar_tabla(){
        cout << "tam = " << computadoras.capacidad() << endl;
        cout << "cont = " << computadoras.cantidad() << endl;
        cout << left;
        cout << setw(10) << "Sistema operativo"
             << setw(10) << "Memoria RAM"
             << setw(15) << "Memoria ROM"
             << setw(5) << "Numero de la computadora"
             << endl;
            for(size_t i = 0; i < computadoras.cantidad(); i++){
                Computadora& computadora = computadoras[i];
                cout << setw(10) << computadora.getSistema();
                cout << setw(10) << computadora.getRom();
                cout << setw(15) << computadora.getRam();
                cout << setw(5) << computadora.getNum();
                cout << endl;
            }
        }

        void respaldar_tabla(){
            ofstream archivo("laboratorio_tabla.txt");
            
            if(archivo.fail()){
                cout << "Error al crear el archivo" << endl;
                return;
            }
            archivo << left;
            archivo << setw(10) << "Sistema operativo: "
            << setw(10) << "Memoria ROM: "
            << setw(10) << "Memoria RAM: "
            << setw(15) << "Numero de la computadora: "
            << endl;

             for (size_t i = 0; i < computadoras.cantidad(); i++){
            Computadora& computadora  = computadoras[i];
            
            archivo << setw(10) << computadora.getSistema();
            archivo << setw(10) << computadora.getRom();
            archivo << setw(15) << computadora.getRam();
            archivo << setw(5) << computadora.getNum();
            archivo << endl;
            }

            archivo.close();
        }

        void respaldar_csv(){
            ofstream archivo("laboratorio.csv");

            if(archivo.fail()){
                cout << "Error al crear el archivo" << endl;
                return;
            }
            for(size_t i = 0; i < computadoras.cantidad(); i++ ){
                 Computadora& computadora = computadoras[i];

            archivo << computadora.getSistema() << ","
                    << computadora.getRom() <<","
                    << computadora.getRam() << ","
                    << computadora.getNum() << endl;
            }

            archivo.close();
        }

        void recuperar_csv(){
            ifstream archivo("laboratorio.csv");

            if(archivo.fail()){
                cout << "Error al abrir el archivo" << endl;
                return;

            }

            while(true){
                Computadora computadora;
                string temp;
                
            getline(archivo, temp, ',');
            if (archivo.eof()) break;
            computadora.setSistema(temp);

            getline(archivo, temp, ',');
            computadora.setRom(stod(temp));

            getline(archivo, temp, ',');
            computadora.setRam(stod(temp));

            getline(archivo, temp);
            computadora.setNum(stod(temp));

            agregarFinal(computadora);
            }
            archivo.close();

        }
        bool llena(){
            return computadoras.llena();
        }
        bool vacia(){
            return computadoras.vacia();
        }

        void eliminarFinal(){
            computadoras.eliminarFinal();
        }

        void eliminarInicio(){
            computadoras.eliminarInicio();
        }

        void insertar(const Computadora& computadora, size_t posicion){
            computadoras.insertar(computadora, posicion);
        }

        void eliminar(size_t posicion){
            computadoras.eliminar(posicion);
        }

        void expandir(){
            computadoras.expandir();
    }

    void encoger(){
        computadoras.encoger();
    }
};

#endif