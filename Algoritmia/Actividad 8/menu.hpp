#ifndef MENU_HPP
#define MENU_HPP

#include "laboratorio.hpp"

size_t capturar_posicion(){
    size_t posicion;
    cout << "posicion: ";
    cin >> posicion;

    return posicion;
}

Computadora capturar_computadora(){
    Computadora computadora;
    string temp;

    cout << "Sistema Operativo: ";
    getline(cin, temp);
    computadora.setSistema(temp);

    double rom;
    cout << "Memoria ROM";
    cin >> rom;
    computadora.setRom(rom);

    double ram;
    cout << "Memoria RAM: ";
    cin >> ram;
    computadora.setRom(ram);

    double num;
    cout << "Numero de la computadora:";
    cin >> num;
    computadora.setNum(num);

    return computadora;
}

void menu(Laboratorio &laboratorio){
    int opcion;

    while(true){
        cout << "1) Agregar final computadora" << endl;
        cout << "2) Mostrar computadoras" << endl;
        cout << "3) Agregar inicio paquete" << endl;
        cout << "4) Eliminar final computadora"  << endl;
        cout << "5) Eliminar inicio computadora" << endl;
        cout << "6) Insertar en posicion" << endl;
        cout << "7) Eliminar en posicion" << endl;
        cout << "8) Mostrar tabla" << endl;
        cout << "9) Respaldar" << endl;
        cout << "10) Respaldar tabla " << endl;
        cout << "11) Respaldar .csv" << endl;
        cout << "12) Recuperar .csv" << endl;
        cout << "13) Encoger" << endl;
        cout << "14) Llena" << endl;
        cout << "15) Vacía" << endl;
        cout << "0) Salir" << endl;
        cin >> opcion; cin.ignore();

        if(opcion == 1){
            Computadora computadora;
            cin >> computadora;

            laboratorio.agregarFinal(computadora);
        }
        else if(opcion == 2){
            laboratorio.mostrar();
        }
        else if(opcion == 3){
            Computadora computadora;
            cin >> computadora;

            laboratorio.agregarInicio(computadora);
        }
        else if(opcion == 4){
            laboratorio.eliminarFinal();
            }
            else if(opcion == 5){
                laboratorio.eliminarInicio();
            }
            else if(opcion == 6){
                Computadora computadora;
                cin >> computadora;
                size_t posicion = capturar_posicion();
                laboratorio.insertar(computadora, posicion);
            }
            else if(opcion == 7){
                laboratorio.eliminar(capturar_posicion());
            }
            else if(opcion == 8){
                laboratorio.mostrar_tabla();
            }
            else if(opcion == 9){
                laboratorio.respaldar();
            }
            else if(opcion == 10){
                laboratorio.respaldar_tabla();
            }
            else if(opcion == 11){
                laboratorio.respaldar_csv();
            }
            else if(opcion == 12){
                laboratorio.recuperar_csv();
            }
            else if(opcion == 13){
                laboratorio.encoger();
            }
            else if(opcion == 14){
                if(laboratorio.llena()){
                    cout << "Laboratorio vacío" << endl;
                }
            }
            else if(opcion == 15){
                if(laboratorio.vacia()){
                    cout << "Laboratorio vacío" << endl;
                }
                else{
                    cout << "El laboratorio no está vació" << endl;
                }
            }
            else if(opcion == 0){
                break;
            }
    }
}

#include<vector>
void menu_laboratorios(){
    vector<Laboratorio> laboratorios;
    string op;

    while(true){
        cout << "1) Crear laboratorio" << endl;
        cout << "2) Eliminar laboratorio" << endl;
        cout << "3) Buscar laboratorio" << endl;
        cout << "0) Salir" << endl;
        getline(cin, op);

        if(op == "1"){
            string nombre;

            cout << "Nombre: ";
            getline(cin, nombre);

            Laboratorio laboratorio;
            laboratorio.setNombreLaboratorio(nombre);

            laboratorios.push_back(laboratorio);
        }
        else if(op == "2"){
            if(laboratorios.empty()){
                cout << "No hay laboratorios" << endl;
                continue;
            }
            size_t posicion = capturar_posicion();
            if (posicion < laboratorios.size()){
                laboratorios.erase(laboratorios.begin() + posicion);
                continue;
            }
            cout << "Posición no valida" << endl;
        }
        else if(op == "3"){
            string nombre;

            cout << "Buscar nombre de laboratorio: ";
            getline(cin, nombre);

            for(size_t i = 0; i < laboratorios.size(); i++){
                if(nombre == laboratorios[i].getNombreLaboratorio()){
                    menu(laboratorios[i]);
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