#ifndef ALDEANO_HPP
#define ALDEANO_HPP  

#include <iostream>
using namespace std;

class Aldeano{
    private:
    string nombreal;
    int edad;
    string genero;
    int salud;
    public:
    Aldeano(){}

    Aldeano(const string& nombreal, int edad, string genero, int salud): nombreal (nombreal), edad (edad), salud (salud){}

    void setNombreal(const string& valor){
        nombreal = valor;
    }

    string getNombreal() const {
        return nombreal;
    }

    void setEdad( int valor){
        edad = valor;
    }

    int getEdad() const {
        return edad;
    }

    void setGenero(const string& valor){
        genero = valor;
    }

    string getGenero() const {
        return genero;
    }

    void setSalud(int valor){
        salud = valor;
    }

    int getSalud() const {
        return salud;
    }

    friend ostream& operator<<(ostream& out, const Aldeano& aldeano){
        out << "Nombre del aldeano: " << aldeano.nombreal << endl;
        out << "Edad: " << aldeano.edad << endl;
        out << "Género: " << aldeano.genero << endl;
        out << "Salud: " << aldeano.salud << endl;

        return out;
     }

    friend istream& operator >>(istream& in, Aldeano& aldeano){
        string temp;

        cout << "Nombre del Aldeano: ";
        getline(cin, temp);
        aldeano.setNombreal(temp);

        int edad;
        cout << "Edad: ";
        cin >> edad;
        aldeano.setEdad(edad);

        cout << "Género: ";
        getline(cin, temp);
        aldeano.setGenero(temp);

        int salud;
        cout << "Salud: ";
        cin >> salud;
        aldeano.setSalud(salud);

        return in;

    }

    bool operator==(const Aldeano& aldeano){
       return nombreal == aldeano.getNombreal();
    }
    //Descendente
    bool operator<(const Aldeano& aldeano){
       return nombreal < aldeano.getNombreal();
    }
};

#endif