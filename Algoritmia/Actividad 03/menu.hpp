#ifndef MENU_HPP
#define MENU_HPP
#include "laboratorio.hpp"

void menu(Laboratorio &laboratorio){
    int opcion;

    while(true){
        cout << "1) Agregar computadora " << endl;
        cout << "2) Mostrar computadoras" << endl;
        cout << "0) Salir" << endl;
        cin >> opcion; cin.ignore();

        if(opcion ==1){
            Computadora computadora;
            string temp;

            cout << "Sistema operativo: ";
            getline(cin, temp);
            computadora.setSistema(temp);

            cout << "Nombre de la computadora: ";
            getline(cin, temp);
            computadora.setNombre(temp);
            
            double RAM;
            cout << "RAM: ";
            cin >> RAM;
            computadora.setram(RAM);

            double ROM;
            cout << "ROM: ";
            cin >> ROM;
            computadora.setrom(ROM);

            

            laboratorio.agregar(computadora);
            
            laboratorio.mostrar();
        }
        //else if(opcion==2){
            
        //}
        else if(opcion==0){
            break;
        }

    }
}

#endif