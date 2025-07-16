#ifndef VIDEOGAME_HPP
#define VIDEOGAME_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include "civilizacion.hpp"
#include "menu.hpp"
#include <vector>
#include <algorithm>
using namespace std;

class VideoGame{

private: 
    vector<Civilizacion> civilizaciones;
    string Nombredeusuario;
public: 
    VideoGame(){}

    void setNombreDeusuario(const string& nombre){
        Nombredeusuario = nombre;
    }

    string getNombreDeusuario() const {
        return Nombredeusuario;
    }

    void agregarFinal(const Civilizacion& civilizacion){
        civilizaciones.push_back(civilizacion);
    }

    void insertarPosicion(const Civilizacion& civilizacion, size_t posicion){
        if(posicion < civilizaciones.size()){
            auto p = civilizaciones.begin() + posicion;
            civilizaciones.insert(p, civilizacion);
        }
        else{
            cout << "Posición no válida" << endl;
        }
    }

    void ordenar_nombre(){
        sort(civilizaciones.begin(), civilizaciones.end());
    }

    void ordenar_x(){
        auto fn = [](const Civilizacion& civilizacion1, const Civilizacion& civilizacion2){return civilizacion1.getX() < civilizacion2.getX();};
        sort(civilizaciones.begin(), civilizaciones.end(), fn);
    }

    void ordenar_y(){
        auto fn = [](const Civilizacion& civilizacion1, const Civilizacion& civilizacion2){return civilizacion1.getY() < civilizacion2.getY();};
        sort(civilizaciones.begin(), civilizaciones.end(), fn);
    }

    void ordenar_puntiacion(){
        auto fn = [](const Civilizacion& civilizacion1, const Civilizacion& civilizacion2){return civilizacion1.getPuntuacion() > civilizacion2.getPuntuacion();};
        sort(civilizaciones.begin(), civilizaciones.end(), fn);
    }

    void eliminarPorNombre(string nombre) {
        auto it = find_if(civilizaciones.begin(), civilizaciones.end(), [&](const Civilizacion& c) {
            return c.getNombre() == nombre;
        });
        if (it != civilizaciones.end()) {
            civilizaciones.erase(it);
            cout << "Civilizacion eliminada" << endl;
        } else {
            cout << "La civilizacion no existe" << endl;
        }
    }

    // Civilizacion& buscar(const string& nombre){
    //     for(size_t i = 0; i < civilizaciones.size(); i++){
    //         if(nombre == civilizaciones[i].getNombre()){
    //             return civilizaciones[i];
    //         }
    //     }
    //     throw "No se encontró la civilización";
    // }
    Civilizacion& buscar(const string& nombre){
        Civilizacion civilizacion;
        civilizacion.setNombre(nombre);

        auto it = find(civilizaciones.begin(), civilizaciones.end(), civilizacion);
        if(it != civilizaciones.end()) return *it;

        throw "Civilización no encontrada";

        
    }

    Civilizacion& modificarCivilizacion(const string& nombre){
        for(size_t i = 0; i < civilizaciones.size(); i++){
            if(nombre == civilizaciones[i].getNombre()){
        cout << endl;
        cout << left;
        cout << setw(10) << "nombre"
             << setw(15) << "Coordenadas X"
             << setw(15) << "coordenadas Y"
             << setw(10) << "Puntuación"
             << endl;
        Civilizacion& civilizacion = civilizaciones[i];
        cout << setw(14) << civilizacion.getNombre()
             << setw(15) << civilizacion.getX()
             << setw(13) << civilizacion.getY()
             << setw(12) << civilizacion.getPuntuacion()
             << endl;
                int opcion = 0;
     while (opcion != 4) {
        cout << endl;
        cout << "Modificar:" << endl;
        cout << "1) Nombre" << endl;
        cout << "2) Ubicación en X" << endl;
        cout << "3) Ubicación en Y" << endl;
        cout << "4) Puntuación" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        Civilizacion& civilizacion = civilizaciones[i];

        if(opcion == 1){
            string nombre;
            cout << "Ingrese el nuevo nombre: ";
            getline(cin, nombre);
            civilizacion.setNombre(nombre);
            cout << "Nombre modificado" << endl;
            return civilizaciones[i];
        }
        else if(opcion ==  2){
            int x;
            cout << "Ingrese la nueva ubicación en X: ";
            cin >> x;
            civilizacion.setX(x);
            cout << "Ubicación en X modificada" << endl;
            return civilizaciones[i];
        }
        else if(opcion == 3){
            int y;
            cout << "Ingrese la nueva ubicación en Y: ";
            cin >> y;
            civilizacion.setY(y);
            cout << "Ubicación modificada" << endl;
            return civilizaciones[i];
        }
        else if(opcion == 4){
            int puntuacion;
            cout << "Ingrese la nueva puntuación: ";
            cin >> puntuacion,
            civilizacion.setPuntuacion(puntuacion);
            cout << "Puntuación modificada";
            return civilizaciones[i];
        }
        else {
            cout << "Esa opción no existe" << endl;
        }
    }
            }
        }
        throw "No se encontró la civilización";
    }

    void resumen(){
        cout << "\nTotal = " << civilizaciones.size() << endl;
        cout << left;
        cout << setw(10) << "nombre"
             << setw(15) << "Coordenadas X"
             << setw(15) << "coordenadas Y"
             << setw(10) << "Puntuación"
             << endl;
        for(size_t i = 0; i < civilizaciones.size(); i++){
            Civilizacion& civilizacion = civilizaciones[i];

        cout << setw(14) << civilizacion.getNombre()
             << setw(15) << civilizacion.getX()
             << setw(13) << civilizacion.getY()
             << setw(12) << civilizacion.getPuntuacion()
             << endl;

        } 
    }

    bool llena(){
        return civilizaciones.size() == civilizaciones.capacity();
    }

    

};


#endif