#ifndef CIVILIZACION_HPP
#define CIVILIZACION_HPP

#include <iostream>
#include <list>
#include <iomanip>
#include <algorithm>
#include "aldeano.hpp"
using namespace std;


class Civilizacion{
    private: 
        string nombre;
        double x;
        double y;
        double puntuacion;
        list<Aldeano>aldeanos;
    public:
    Civilizacion(){}

    Civilizacion(const string& id, double x, double y, double puntuacion){
        this->nombre = nombre;
        this->x = x;
        this->y = y;
        this->puntuacion = puntuacion;
    }

    void setNombre (const string& valor ){
        nombre = valor;
    }

    string getNombre() const {
        return nombre;
    }

    void setX(double valor){
        x = valor;
    }

    double getX() const {
        return x;
    }

    void setY(double valor){
        y = valor;
    }

    double getY() const {
        return y;
    }

    void setPuntuacion(double valor){
        puntuacion = valor;
    }

    double getPuntuacion() const {
        return puntuacion;
    }

    friend ostream& operator<<(ostream& out, const Civilizacion& civilizacion){
        out << "Nombre: " << civilizacion.nombre << endl;
        out << "Coordenada en X: " << civilizacion.x << endl;
        out << "Coordenada en Y: " << civilizacion.y << endl;
        out << "Puntuación: " << civilizacion.puntuacion << endl;

        return out;
     }

    friend istream& operator >>(istream& in, Civilizacion& civilizacion){
        string temp;

        cout << "Nombre: ";
        getline(cin, temp);
        civilizacion.setNombre(temp);

        double x;
        cout << "Coordenada en X: ";
        in >> x;
        civilizacion.setX(x);

        double y;
        cout << "Coordenada en Y: ";
        in >> y;
        civilizacion.setY(y);

        double puntuacion;
        cout << "Puntuación: ";
        in >> puntuacion;
        civilizacion.setPuntuacion(puntuacion);

        return in;

    }

    bool operator==(const Civilizacion& civilizacion){
       return nombre == civilizacion.getNombre();
    }
    //Descendente
    bool operator<(const Civilizacion& civilizacion){
       return nombre < civilizacion.getNombre();
    }

    void agregarInicio(const Aldeano& aldeano){
        aldeanos.push_front(aldeano);
    }

    void agregarFinal(const Aldeano& aldeano){
        aldeanos.push_back(aldeano);
    }

    bool comparador(const Aldeano& e){
        return e.getSalud() == 60;
    }

    void eliminarPorNombre(const string& nombre){
        auto it = find_if(aldeanos.begin(), aldeanos.end(), [nombre](const Aldeano& aldeano){return aldeano.getNombreal() == nombre;});
        if(it == aldeanos.end()) 
        throw "Aldeano no encontrado";

        aldeanos.erase(it);
    }

    void eliminarPorSalud(int x){
        auto it = ([x](const Aldeano& aldeano){return aldeano.getSalud() < x;});

        aldeanos.remove_if(it);
    }

    void eliminarPorEdad(){
        aldeanos.remove_if(comparador);
    }

    void ordenarNombre(){
        aldeanos.sort();
    }

    void ordenarEdad(){
        auto fn = [](const Aldeano& a1, const Aldeano& a2){
            return a1.getEdad() > a2.getEdad();
        };
        aldeanos.sort(fn);
    }

    void ordenarSalud(){
        auto fn = [](const Aldeano& a1, const Aldeano& a2){
            return a1.getSalud() > a2.getSalud();
        };
        aldeanos.sort(fn);
    }

    Aldeano& buscar(const string& nombre){
        Aldeano aldeano;
        aldeano.setNombreal(nombre);
        auto it = find(aldeanos.begin(), aldeanos.end(), aldeano);
        if(it != aldeanos.end()) return *it;

        throw "Aldeano no encontrado";
    }

    // Aldeano& buscar(const string& nombre){
    //     for(auto it = aldeanos.begin(); it != aldeanos.end(); it++){
    //         Aldeano& aldeano = *it;
    //         if(nombre == aldeano.getNombreal()){
    //             cout << "Nombre: " << aldeano.getNombreal() << endl;
    //             cout << "Edad: " << aldeano.getEdad() << endl;
    //             cout << "Género: " << aldeano.getGenero() << endl;
    //             cout << "Salud: " << aldeano.getSalud() << endl; 
    //         }
    //     }
    // }

    void mostrar(){
        cout << "\tAldeanos" << endl;
        cout << left;
        cout << setw(15) << "Nombre" 
             << setw(14) << "Edad" 
             << setw(14) << "Género" 
             << setw(14) << "Salud" 
             << endl;
        for(auto it = aldeanos.begin(); it != aldeanos.end(); it++){
            cout << setw(15) << (*it).getNombreal() 
                 << setw(14) << (*it).getEdad() 
                 << setw(14) << (*it).getGenero() 
                 << setw(14) << (*it).getSalud() 
                 << endl;
        }
    }

};


#endif