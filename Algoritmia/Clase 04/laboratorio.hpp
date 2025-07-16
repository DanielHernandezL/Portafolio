#ifndef LABORATORIO_HPP
#define LABORATORIO_HPP

#include <iostream>
#include <iomanip>
#include "computadora.hpp"
using namespace std;

#define MAX 50

class Laboratorio
{
    private:
        Computadora computadoras[5];
        size_t cont;
    public:
        Laboratorio(){
            cont = 0;
        }

        void agregarFinal(const Computadora& computadora){
            if(llena()){
                cout << "Laboratorio lleno";
                return;
            }
            computadoras[cont] = computadora;
            cont++;
        }

        void agregarInicio(const Computadora& computadora){
            if(llena()){
                cout << "Laboratorio lleno";
                return;
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

        void mostrar_tabla(){
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
        bool llena(){
            return cont == MAX;
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
};

#endif