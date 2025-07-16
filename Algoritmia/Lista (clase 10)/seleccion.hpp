#ifndef SELECCION_HPP
#define SELECCION_HPP

#include "jugador.hpp"
#include <list>
#include <iomanip>
#include <algorithm>

class Seleccion{
    string nombre;
    list<Jugador> jugadores;

    public:
        Seleccion(){}
        Seleccion(const string& nombre): nombre(nombre){}

        //Metodo de acceso
        void setNombre(const string& valor){
            nombre = valor;
        }

        string getNombre() const {
            return nombre;
        }

        void agregarFinal(const Jugador& jugador){
            jugadores.push_back(jugador);
        }
            
        void agregarInicio(const Jugador& jugador){
        jugadores.push_front(jugador);
        }

        void mostrar(){
            cout << "Seleccion: " << nombre << "\n";
            cout << left;
            cout << setw(15) << "Nombre"
                 << setw(13) << "# de playera"
                 << setw(15) << "Goles Anotados"
                 << endl;
                for(auto it = jugadores.begin(); it != jugadores.end(); it++ ){
                cout<< setw(15) << (*it).getNombre()
                    << setw(13) << (*it).getNumeroPlayera()
                    << setw(15) << (*it).getGolesAnotados()
                    << endl;
                }
        }

        Jugador& frente(){
            if(jugadores.empty()) throw "La lista esta vacía";

            return jugadores.front();
        }

        Jugador& ultimo(){
            if(jugadores.empty()) throw "La lista esta vacía";

            return jugadores.back();
        }

        void eliminarFinal(){
            if(jugadores.empty()) throw "La lista esta vacía";

            return jugadores.pop_back();
        }

        void eliminarInicio(){
            if(jugadores.empty()) throw "La lista esta vacía";

            return jugadores.pop_front();
        }

        void ordenarNombre(){
            jugadores.sort();
        }
        //Ascendente
        void ordenarNumeroPlayera(){
            auto fn = [](const Jugador& j1, const Jugador& j2){
                return j1.getNumeroPlayera() < j2.getNumeroPlayera();
            };
            jugadores.sort(fn);
        }
        //Descendente
        void ordenarGolesAnotados(){
            auto fn = [](const Jugador& j1, const Jugador& j2){
                return j1.getGolesAnotados() > j2.getGolesAnotados();
            };
            jugadores.sort(fn);
        }

        void eliminarPorNombre(const string& nombre){
            auto it = find_if(jugadores.begin(), jugadores.end(), [nombre](const Jugador& jugador){ return jugador.getNombre() == nombre;});
            if(it == jugadores.end()) throw "Jugador no encontrado";

            jugadores.erase(it);
        }

        void eliminarPorNumeroPlayera(int numeroPlayera){
            auto it = find_if(jugadores.begin(), jugadores.end(), [numeroPlayera](const Jugador& jugador){ return jugador.getNumeroPlayera() == numeroPlayera;});
            if(it == jugadores.end()) throw "Jugador no encontrado";

            jugadores.erase(it);
        }

        void eliminarPorGolesMenorA(int goles){
            auto it = ([goles](const Jugador& jugador){ return jugador.getGolesAnotados() < goles;});

            jugadores.remove_if(it);
        }
};

#endif