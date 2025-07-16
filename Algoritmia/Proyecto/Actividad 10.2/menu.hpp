#ifndef MENU_HPP
#define MENU_HPP

#include "VideoGame.hpp"
#include "civilizacion.hpp"
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

            // Civilizacion& civilizaciones;
            // for(size_t i = 0; i < civilizaciones.size(); i++){
            //     if(nombre == civilizaciones[i].getNombreDeusuario()){
            //         menu(civilizaciones[i]);
            //         break;
            //     }
            // }
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

// void menu_aldeanos(Civilizacion& civilizacion){
//     while(true){
//     string op;
//             cout << "\n\tMenú de aldeanos" << endl;
//             cout << "1) Agregar aldeano al inicio" << endl;
//             cout << "2) Agregar aldeano al final" << endl;
//             cout << "3) Eliminar aldeano" << endl;
//             cout << "4) Ordenar" << endl;
//             cout << "5) Buscar aldeano" << endl;
//             cout << "6) Modificar aldeano" << endl;
//             cout << "7) Mostrar aldeanos" << endl;
//             cout << "0) Salir" << endl;
//             cout << "Opción: " << endl;
//             getline(cin, op); cin.ignore();

//             if(op == "1"){
//                 Aldeano aldeano;
//                 cin >> aldeano;
//                 civilizacion.agregarFinal(aldeano);
//             }
//             else if(op == "2"){
//                 Aldeano aldeano;
//                 cin >> aldeano;
//                 civilizacion.agregarInicio(aldeano);
//             }
//             else if(op == "3"){
//                 size_t opcion;
//                 cout << "1) Por nombre" << endl;
//                 cout << "2) Por edad" << endl;
//                 cout << "3) Por salud" << endl;
//                 cin >> opcion;

//                 if(opcion == 1){
//                 string nombre;
//             cout << "Nombre de usuario a buscar: ";
//             getline(cin, nombre);

//             civilizacion.eliminarPorNombre(nombre);
//                 }
//                 else if(opcion == 2){
//                     int x;
//                     cout << "Edad: ";
//                     cin >> x; cin.ignore();
//                     try{
//                         civilizacion.eliminarPorSalud(x);
//                     }catch(const char* msg){
//                         cout << msg << endl;
//                     }
//                 }
//                 else if(opcion == 3){
//                     civilizacion.eliminarPorEdad();
//                 }
//             }
//             else if(op == "4"){
//                 size_t opcion;
//                 cout << "1) Nombre (ascendente)" << endl;
//                 cout << "2) Edad (descendente)" << endl;
//                 cout << "3) Salud (descendete)" << endl;
//                 cin >> opcion;

//                 if(opcion == 1){
//                     civilizacion.ordenarNombre();
//                     civilizacion.mostrar();
//                 }
//                 else if(opcion == 2){
//                     civilizacion.ordenarEdad();
//                     civilizacion.mostrar();
//                 }
//                 else if(opcion == 3){
//                     civilizacion.ordenarSalud();
//                     civilizacion.mostrar();
//                 }
//             }
//             else if(op == "5"){
//                 string nombre;
//                 cout << "Ingrese el nombre de la civilización: ";
//                 getline(cin, nombre);

//                 try{
//                     Aldeano& Aldeano = civilizacion.buscar(nombre);
//                     cout << Aldeano << endl;
//                 }catch(const char* e){
//                     std::cerr << e << '\n';
//                 }
//             }
//             else if(op == "6"){

//             }
//             else if(op == "7"){
//                 civilizacion.mostrar();
//             }
//             else if(op == "0"){
//                 break;
//             }
//     }

// }

void menu_videogames(){
    vector<VideoGame> videogames;
    string opc; 

    while (true)
    {
        cout << endl;
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