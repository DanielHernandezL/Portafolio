#ifndef CIVILIZACION_HPP
#define CIVILIZACION_HPP

#include <iostream>
using namespace std;


class Civilizacion{
    private: 
        string nombre;
        double x;
        double y;
        double puntuacion;
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
        cin >> x;
        civilizacion.setX(x);

        double y;
        cout << "Coordenada en Y: ";
        cin >> y;
        civilizacion.setY(y);

        double puntuacion;
        cout << "Puntuación: ";
        cin >> puntuacion;
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
    //Ascendente
    bool operator>(const Civilizacion& civilizacion){
       return nombre > civilizacion.getNombre();
    }
};


#endif