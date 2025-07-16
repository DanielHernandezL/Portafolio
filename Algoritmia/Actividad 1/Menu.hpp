#ifndef MENU_HPP
#define MENU_HPP

#include "paqueteria.hpp"

void menu(Paqueteria &paqueteria){
    int opcion;

    while (true){
        cout << "1) Agregar Paquete" << endl;
        cout << "2) Mostrar Paquetes" << endl;
        cout << "0) Salir" << endl;
        cin >> opcion; cin.ignore();

        if(opcion ==1){
            Paquete paquete;
            string temp;

            cout << "Origen: ";
            getline(cin, temp);
            paquete.setOrigen(temp);

            cout << "Destino: ";
            getline(cin, temp);
            paquete.setDestino(temp);

            cout << "Destinatario: ";
            getline(cin, temp);
            paquete.setDestinatario(temp);

            double peso;
            cout << "Peso: ";
            cin >> peso;
            paquete.setPeso(peso);

            paqueteria.agregar(paquete);
        }
        else if(opcion == 2){
            paqueteria.mostrar();
        }
        else if(opcion == 0){
            break;
        }
    }
}


#endif