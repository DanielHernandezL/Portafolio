#ifndef LABORATORIO_HPP
#define LABORATORIO_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include "computadora.hpp"
using namespace std;

#define MAX 5

class Laboratorio
{
    private:
        Computadora* computadoras;
        size_t cont;
        size_t tam;
    public:
        Laboratorio(){
            cont = 0;
            tam = MAX;
            computadoras = new Computadora[tam];
        }

        void agregarFinal(const Computadora& computadora){
            if(llena()){
                cout << "Expandiendo..." << endl;
                expandir();
            }
            computadoras[cont] = computadora;
            cont++;
        }

        void agregarInicio(const Computadora& computadora){
            if(llena()){
                cout << "Expandiendo..." << endl;
                expandir();
            }
            for(size_t i = cont; i>0; i--){
                computadoras[i] = computadoras[i-1];
            }
            computadoras[0] = computadora;
            cont++;
        }

        void mostrar(){
            for(size_t i = 0; i < cont; i++){
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

            for(size_t i = 0; i < cont; i++){
                Computadora& computadora = computadoras[i];
                archivo << computadora << endl;
            }

            archivo.close();
        }

        void mostrar_tabla(){
        cout << "tam=" << tam << endl;
        cout << "cont=" << cont << endl;
        cout << left;
        cout << setw(10) << "Sistema operativo"
             << setw(10) << "Memoria RAM"
             << setw(15) << "Memoria ROM"
             << setw(5) << "Numero de la computadora"
             << endl;
            for(size_t i = 0; i < cont; i++){
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

             for (size_t i = 0; i < cont; i++){
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
            for(size_t i = 0; i < cont; i++ ){
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
            if (archivo.eof()) break; //End of line
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
            return cont == tam;
        }
        bool vacia(){
            return cont == 0;
        }

        void eliminarFinal(){
            if(vacia()){
                cout << "Laboratorio vacio" << endl;
                return;
            }
            cont--;
        }

        void eliminarInicio(){
            if(vacia()){
                cout << "Laboratorio vacio" << endl;
                return;
            }
            for(size_t i = 0; i < cont -1; i++){
                computadoras[i] = computadoras[i+1];
            }
            cont--;
        }

        void insertar(const Computadora& computadora, size_t posicion){
            if(llena()){
                cout << "Laboratorio lleno" << endl;
                return;
            }
            if(posicion >= cont){
                cout << "Posicion no valida" << endl;
            }
            for(size_t i = cont; i > posicion; i--){
                computadoras[i] = computadoras[i-1];
            }
                computadoras[posicion] = computadora;
                cont++;
        }

        void eliminar(size_t posicion){
            if(vacia()){
                cout << "Laboratorio vacio" << endl;
                return;
            }
            if(posicion >= cont){
                cout << "Posicion no valida" << endl;
                return; 
            }
            for(size_t i = posicion; i < cont -1; i++){
                computadoras[i] = computadoras[i+1];
            }
            cont--;
        }

        void expandir(){
            Computadora* nuevo = new Computadora[tam+MAX];
            for(size_t i = 0; i < tam; i++){
            nuevo[i] = computadoras[i];
        }

        delete []computadoras;
        computadoras = nuevo;
        tam = tam + MAX;
    }

    void encoger(){
        if(vacia()){
            return;
        }

        if(llena()){
            return;
        }

        Computadora* reducido = new Computadora[cont];
        for(size_t i = 0; i < cont; i++){

            reducido[i] = computadoras[i];
        }

        delete []computadoras;
        computadoras = reducido;
        tam = cont;
    }
};

#endif