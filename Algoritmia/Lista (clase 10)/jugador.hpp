#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <iostream>
using namespace std;


class Jugador{
    private: 
    string nombre;
    int numeroPlayera;
    int golesAnotados;

    public:
    Jugador(){}
    Jugador(const string& nombre,
            int numeroPlayera,
            int golesAnotados):nombre(nombre),
                                numeroPlayera(numeroPlayera),
                                golesAnotados(golesAnotados){}
    //Metodos de acceso
    void setNombre(const string& valor){
        nombre = valor;
    }

    string getNombre() const {
        return nombre;
    }

    void setNumeroPlayera(int valor){
        numeroPlayera = valor;
    }

    int getNumeroPlayera() const {
        return numeroPlayera;
    }

    void setGolesAnotados(int valor){
        golesAnotados = valor;
    }

    int getGolesAnotados() const {
        return golesAnotados;
    }

    friend istream& operator>>(istream& is, Jugador& jugador){
        cout << "Nombre: ";
        getline(is, jugador.nombre);

        cout << "# de playera: ";
        is >> jugador.numeroPlayera;

        cout << "Goles anotados: ";
        is >> jugador.golesAnotados;
        is.ignore();
        return is; 
    }

    friend ostream& operator<<(ostream& os, const Jugador& jugador){
        os << "Nombre: " << jugador.nombre << "\n";
        os << "# de playera: " << jugador.numeroPlayera << "\n";
        os << "Goles anotados: " << jugador.golesAnotados << "\n";

        return os;
    }

    bool operator<(const Jugador& jugador){
        return nombre < jugador.nombre;
    }
};


#endif