#ifndef MENU_HPP
#define MENU_HPP

#include "paqueteria.hpp"

size_t capturar_posicion(){
    size_t posicion;
    cout << "posicion: ";
    cin >> posicion;

    return posicion;
}

Paquete capturar_paquete(){
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

    return paquete;
}

void menu(Paqueteria &paqueteria){
    int opcion;

    while (true){
        cout << "1) Agregar Final Paquete" << endl;
        cout << "2) Mostrar Paquetes" << endl;
        cout << "3) Agregar Inicio Paquete" << endl;
        cout << "4) Eliminar Final Paquete" << endl;
        cout << "5) Eliminar Inicio Paquete" << endl;
        cout << "6) Insertar en posicion" << endl;
        cout << "7) Eliminar en posicion" << endl;
        cout << "8) Mostrar tabla" << endl;
        cout << "9) Respaldar" << endl;
        cout << "10) Respaldar Tabla" << endl;
        cout << "11) Respaldar CSV" << endl;
        cout << "12) Recuperar CSV" << endl;
        cout << "13) Encoger" << endl;
        cout << "14) Llena" << endl;
        cout << "15) Vacía"<< endl;
        cout << "0) Salir" << endl;
        cin >> opcion; cin.ignore();

        if(opcion ==1){
            Paquete paquete;// = capturar_paquete();
            cin >> paquete;

            paqueteria.agregarFinal(paquete);
        }
        else if(opcion == 2){
            paqueteria.mostrar();
        }
        else if(opcion == 3){
            Paquete paquete;//= capturar_paquete();
            cin >> paquete;

            paqueteria.agregarInicio(paquete);
        }
        else if(opcion == 4){
            paqueteria.eliminarFinal();
        }
        else if(opcion == 5){
            paqueteria.eliminarInicio();
        }
        else if(opcion == 6){
            Paquete paquete;// = capturar_paquete();
            cin >> paquete;
            size_t posicion = capturar_posicion();

            paqueteria.insertar(paquete, posicion);
        }
        else if(opcion == 7){
            paqueteria.eliminar(capturar_posicion());
        }
        else if(opcion == 8){
            paqueteria.mostrar_tabla();
        }
        else if(opcion == 9){
            paqueteria.respaldar();
        }
        else if(opcion ==10){
            paqueteria.respaldar_tabla();
        }
        else if(opcion == 11){
            paqueteria.respaldar_csv();
        }
        else if(opcion == 12){
            paqueteria.recuperar_csv();
        }
        else if(opcion == 13){
            paqueteria.encoger();
        }
        else if( opcion == 14){
            if(paqueteria.llena()){
                cout << "Paquetería llena" << endl;
            }
        }
        else if(opcion == 15){
             if(paqueteria.vacia()){
                cout << "Paquetería vacía" << endl;
            }
            else{
                cout << "La paquetería no está vacía" << endl;
            } 
        }
        else if(opcion == 0){
            break;
        }
    }
}

#include<vector>
void menu_paqueterias(){
    vector<Paqueteria> paqueterias;

    string op;

    while(true){
        cout << "1) Crear Paqueteria" << endl;
        cout << "2) Eliminar Paqueteria" << endl;
        cout << "3) Buscar Paqueteria" << endl;
        cout << "0) Salir" << endl;
        getline(cin, op);

        if(op == "1"){
            string nombre;

            cout << "nombre: ";
            getline(cin, nombre);

            Paqueteria paqueteria;
            paqueteria.setNombrePaqueteria(nombre);

            paqueterias.push_back(paqueteria);
        }
        else if(op == "2"){
            if(paqueterias.empty()){
                cout << "no hay paqueterias" << endl;
                continue;
            }
            size_t posicion = capturar_posicion();
            if(posicion < paqueterias.size()){
                paqueterias.erase(paqueterias.begin() + posicion);
                continue;
            }
            cout << "posición no válida" << endl;   
        }
        else if(op == "3"){
            string nombre;
            cout << "nombre a buscar: ";
            getline(cin, nombre);

            for(size_t i = 0; i < paqueterias.size(); i++){
                if(nombre == paqueterias[i].getNombrePaqueteria()){
                    menu(paqueterias[i]);
                   break;
                }
            }
        }
        else if(op == "0"){
            break;
        }
        
    }

}


#endif