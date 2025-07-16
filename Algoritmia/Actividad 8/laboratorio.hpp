#ifndef LABORATORIO_HPP
#define LABORATORIO_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include "computadora.hpp"
#include <vector>
using namespace std;

#define MAX 5

class Laboratorio
{
    private:
        vector<Computadora> computadoras;
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
            computadoras.push_back(computadora);
        }

        void agregarInicio(const Computadora& computadora){
            if(!computadoras.empty()){
                computadoras.insert(computadoras.begin(), computadora);
            }
            else{
                computadoras.push_back(computadora);
            }
        }

        void mostrar(){
            for(size_t i = 0; i < computadoras.size(); i++){
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

            for(size_t i = 0; i < computadoras.size(); i++){
                Computadora& computadora = computadoras[i];
                archivo << computadora << endl;
            }

            archivo.close();
        }

        void mostrar_tabla(){
        cout << "tam = " << computadoras.capacity() << endl;
        cout << "cont = " << computadoras.size() << endl;
        cout << left;
        cout << setw(10) << "Sistema operativo"
             << setw(10) << "Memoria RAM"
             << setw(15) << "Memoria ROM"
             << setw(5) << "Numero de la computadora"
             << endl;
            for(size_t i = 0; i < computadoras.size(); i++){
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

             for (size_t i = 0; i < computadoras.size(); i++){
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
            for(size_t i = 0; i < computadoras.size(); i++ ){
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

        bool vacia(){
            return computadoras.empty();
        }

        void eliminarFinal(){
            if(!computadoras.empty()){
                computadoras.pop_back();
            }
            else{
                cout << "No hay computadoras" << endl;
            }
        }

        void eliminarInicio(){
            if(!computadoras.empty()){
                computadoras.erase(computadoras.begin());
            }
            else{
                cout << "No hay computadoras" << endl;
            }
        }

        void insertar(const Computadora& computadora, size_t posicion){
            if(posicion < computadoras.size()){
                auto p = computadoras.begin() + posicion;
                computadoras.insert(p, computadora);
            }
            else{
                cout << "No hay computadoras" << endl;
            }
        }

        void eliminar(size_t posicion){
            if(posicion < computadoras.size()){
                auto p = computadoras.begin() + posicion;
                computadoras.erase(p);
            }
            else{
                cout << "No hay computadoras" << endl;
            }
        }

        void expandir(){
            size_t nueva_capacidad = computadoras.size() + 10;
            computadoras.reserve(nueva_capacidad);
        }

    void encoger(){
        computadoras.shrink_to_fit();
    }
    bool llena(){
        return computadoras.size() == computadoras.capacity();
    }
};

#endif