#ifndef COMPUTADORA_HPP
#define COMPUTADORA_HPP

#include <iostream>
using namespace std;

class Computadora{
    private:
    string sistema;
    double rom;
    double ram;
    double num;
public:
    Computadora(){

    }
    Computadora(const string& sistema, double ron, double ram, double num){
        this->sistema = sistema;
        this->rom = rom;
        this->ram = ram;
        this->num = num;
        }
    void setSistema(const string& v){
        sistema = v;
    }
    string getSistema(){
        return sistema;
    }
    void setRom(double v){
        rom = v;
    }
    double getRom(){
        return rom;
    }
    void setRam(double v){
        ram = v;
    }
    double getRam(){
        return ram;
    }
    void setNum(double v){
        num = v;
    }
    double getNum(){
        return num;
    }

    friend ostream& operator<<(ostream& out, const Computadora& computadora ){
        out << "Sistema operativo: " << computadora.sistema << endl;
        out << "Memoria ROM: " << computadora.rom << endl;
        out << "Memoria RAM: " << computadora.ram << endl;
        out << "Numero de la computadora: " << computadora.num << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Computadora& computadora){
        string temp;

        cout << "Sistema operativo: ";
        getline(cin, temp);
        computadora.setSistema(temp);

        double rom;
        cout << "Memoria ROM: ";
        cin >> rom;
        computadora.setRom(rom);
        
        double ram;
        cout << "Memoria RAM: ";
        cin >> ram;
        computadora.setRam(ram);

        double num;
        cout << "Numero de la computadora:";
        cin >> num;
        computadora.setNum(num);


        return in;
    }
};

#endif