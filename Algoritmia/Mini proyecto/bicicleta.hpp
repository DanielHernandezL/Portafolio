#ifndef BICICLETA_HPP
#define BICICLETA_HPP

#include <iostream>
using namespace std;

class Bicicleta{
    private:
    string id;
    double tiempu;
    double mtr;
public:
    Bicicleta(){
    }

    Bicicleta(const string& id, double tiempu, double mtr){
        this->id = id;
        this->tiempu = tiempu;
        this->mtr = mtr;
        }
    void setId(const string& v){
        id = v;
    }
    string getId(){
        return id;
    }
    void setTiempu(double v){
        tiempu = v;
    }
    double getTiempu(){
        return tiempu;
    }
    void setMtr(double v){
        mtr = v;
    }
    double getMtr(){
        return mtr;
    }

friend ostream& operator<<(ostream& out, const Bicicleta& bicicleta){
        out <<"ID: "<< bicicleta.id <<endl;
        out <<"Tiempo de uso: "<< bicicleta.tiempu <<endl;
        out <<"Metros recorridos: "<< bicicleta.mtr <<endl;

        return out;
    }

    friend istream& operator>>(istream& in, Bicicleta& bicicleta){
        string temp;

        cout << "ID: ";
        getline(cin, temp);
        bicicleta.setId(temp);

        double tiempu;
        cout << "Tiempo de uso: ";
        cin >> tiempu;
        bicicleta.setTiempu(tiempu);

        double mtr;
        cout << "Metros recorridos: ";
        cin >> mtr;
        bicicleta.setMtr(mtr);

        return in;

    }
};

#endif