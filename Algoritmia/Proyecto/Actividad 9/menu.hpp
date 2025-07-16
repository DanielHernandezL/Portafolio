#ifndef MENU_HPP
#define MENU_HPP

#include "VideoGame.hpp"
#include <vector>

size_t capturar_posicion(){
    size_t posicion;
    cout << "Posición: ";
    cin >> posicion;

    return posicion;
}

Civilizacion caputar_civilizacion(){
    Civilizacion civilizacion;
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

    return civilizacion;
}

void menu(VideoGame& videogame){
    int opcion;

    while (true)
    {
        cout << "\n\tMenú de civilización:" << endl;
        cout << "1) Agregar civilización" << endl;
        cout << "2) Insertar civilización" << endl;
        cout << "3) Ordenar" << endl;
        cout << "4) Eliminar civilización" << endl;
        cout << "5) Buscar civilización" << endl;
        cout << "6) Modificar civilización" << endl;
        cout << "7) Resumen" << endl;
        cout << "0) Salir" << endl;
        cout << "Opción: ";
        cin >> opcion; 
        cin.ignore();

        if(opcion == 1){
            Civilizacion civilizacion;
            cin >> civilizacion;

            videogame.agregarFinal(civilizacion);
        }
        else if(opcion == 2){
            Civilizacion civilizacion;
            cin >> civilizacion;
            size_t posicion = capturar_posicion();

            videogame.insertarPosicion(civilizacion, posicion);
        }
        else if(opcion == 3){
            size_t op;
            cout << endl;
            cout << "1) Por nombre (ascendente)" << endl;
            cout << "2) Posición en X (ascendente)" << endl;
            cout << "3) Posición en Y (ascendente)" << endl;
            cout << "4) Por puntuación (descendente)" << endl;
            cout << "Opción: ";
            cin >> op;
            if(op == 1){
                videogame.ordenar_nombre();
                videogame.resumen();
            }
            else if(op == 2){
                videogame.ordenar_x();
                videogame.resumen();
            }
            else if(op == 3){
                videogame.ordenar_y();
                videogame.resumen();
            }
            else if(op == 4){
                videogame.ordenar_puntiacion();
                videogame.resumen();
            }
        }
        else if(opcion == 4){
            string nombre;
            cout << "Nombre de usuario a buscar: ";
            getline(cin, nombre);

            videogame.eliminarPorNombre(nombre);
        }

        else if(opcion == 5){
            string nombre;
            cout << "Ingrese el nombre de la civilización: ";
            getline(cin, nombre);

            try{
                Civilizacion& Civilizacion = videogame.buscar(nombre);
                cout << Civilizacion << endl;
            }catch(const char* e){
                std::cerr << e << '\n';
            }
        }
        else if(opcion == 6){
             string nombre;
                cout << "Ingrese el nombre de la civilizacion que quiere modificar: ";
                getline(cin, nombre);
            //Civilizacion& Civilizacion = videogame.modificarCivilizacion(nombre);
             try{
                 Civilizacion& Civilizacion = videogame.modificarCivilizacion(nombre);
                 cout << Civilizacion << endl;
             }catch(const char* e){
                 std::cerr << e << '\n';
             }
        }
        else if(opcion == 7){
            videogame.resumen(); 
        }
        else if(opcion == 0){
            break;
        }
    }
}

void menu_videogames(){
    vector<VideoGame> videogames;
    string opc; 

    while (true)
    {
        cout << endl;
        cout << "\tMenú de usuarios" << endl;
        cout << "1) Nombre de usuario" << endl;
        cout << "2) Eliminar nombre de usuario" << endl;
        cout << "3) Buscar nombre de usuario" << endl;
        cout << "0) Salir" << endl;
        cout << "Opción: ";
        getline(cin, opc);

        if(opc == "1"){
            string nombre;

            cout << "Nombre de usuario: ";
            getline(cin, nombre);  

            VideoGame videogame;
            videogame.setNombreDeusuario(nombre);

            videogames.push_back(videogame);
        }
        else if(opc == "2"){
            if(videogames.empty()){
                cout << "No hay civilizaciónes" << endl;
                continue;
            }

            size_t posicion = capturar_posicion();
            if(posicion < videogames.size()){
                videogames.erase(videogames.begin() + posicion);
                cin.ignore();
                continue;
            }

            cout << "Posición no válida";

            videogames.erase(videogames.begin() + posicion);
        }
        else if(opc == "3"){
            string nombre;

            cout << "Nombre de usuario a buscar: ";
            getline(cin, nombre);

            for(size_t i = 0; i < videogames.size(); i++){
                if(nombre == videogames[i].getNombreDeusuario()){
                    menu(videogames[i]);
                    break;
                }
            }
        }
        else if(opc == "0"){
            break;
        }
    }
    
}
#endif