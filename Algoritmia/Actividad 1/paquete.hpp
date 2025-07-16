#ifndef PAQUETE_HPP
#define PAQUETE_HPP

#include <iostream>
using namespace std;

class Paquete{
    private:
        string origen;
        string destino;
        string destinatario;
        double peso;
    public:
        Paquete() {//Tiene que llamarse igual a la clase

        }
        Paquete(const string& origen, 
                const string& destino,
                const string& destinarario,
                double peso) {
            this->origen = origen;//this es para saber a que nos referimos a un paquete dentro de la clase
            Paquete::destino = destino;//Paquete:: es lo mismo que poner this
            this->destinatario = destinatario;
            this->peso = peso;
        } 
    //metodos de acceso
    void setOrigen(const string& valor){//El & es para que no se copie la informacion muchas veces y pasarlo a referencia y el const es para que no se modifique desde aqui
        origen = valor;
    }

    string getOrigen() {
        return origen;
    }

    void setDestino(const string& valor){
        destino = valor;
    }

    string getDestino(){
        return destino;
    }

    void setDestinatario(const string& valor){
        destinatario = valor;
    }

    string getDestinatario(){
        return destinatario;
    }

    void setPeso(double valor){//En el double no se pone porque solo usa 8 bytes en la memoria
        peso = valor;
    }

    double getPeso(){
        return peso;
    }
};

#endif