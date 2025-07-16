#include "seleccion.hpp"

void menu_seleccion(Seleccion& seleccion){
    string op;

    while(true){
        cout << "1) Agregar final" << endl;
        cout <<"2) Agregar inicio" << endl;
        cout << "3) Mostrar" << endl;
        cout << "4) Frente" << endl;
        cout << "5) Último" << endl;
        cout << "6) Eliminar último" << endl;
        cout << "7) Eliminar Inicio" << endl;
        cout << "8) Ordenar por nombre" << endl;
        cout << "9) Ordenar por # de playera" << endl;
        cout << "10) Ordenar por goles anotados" << endl;
        cout << "11) Eliminar por nombre" << endl;
        cout << "12) Eliminar por # de playera" << endl;
        cout << "13) Eliminar por goles" << endl;
        cout << "0) Salir" << endl;
        getline(cin, op);

        if(op == "1"){
            Jugador jugador;
            cin >> jugador;
            seleccion.agregarFinal(jugador);
        }
        else if(op == "2"){
            Jugador jugador;
            cin >> jugador;
            seleccion.agregarInicio(jugador);
        }
        else if(op == "3"){
            seleccion.mostrar();
        }
        else if(op == "4"){
            try{
                cout << seleccion.frente() << endl;
            }catch(const char* msg){
                cout << msg << endl;
            }
        }
        else if(op == "5"){
            try{
                cout << seleccion.ultimo() << endl;
            }catch(const char* msg){
                cout << msg << endl;
            }
        }
        else if(op == "6"){
            try{
                seleccion.eliminarFinal();
            }catch(const char* msg){
                cout << msg << endl;
            }
        }
        else if(op == "7"){
            try{
                seleccion.eliminarInicio();
            }catch(const char* msg){
                cout << msg << endl;
            }
        }
        else if(op == "8"){
            seleccion.ordenarNombre();
            seleccion.mostrar();
        }
        else if(op == "9"){
            seleccion.ordenarNumeroPlayera();
            seleccion.mostrar();
        }
        else if(op == "10"){
            seleccion.ordenarGolesAnotados();
            seleccion.mostrar();
        }
        else if(op == "11"){
            string nombre;
            cout << "Nombre: ";
            getline(cin, nombre);

            try{
                seleccion.eliminarPorNombre(nombre);
            }catch(const char* msg){
                cout << msg << endl;
            }
        }
        else if(op == "12"){
            int numeroPlayera;
            cout << "# de playera: ";
            cin >> numeroPlayera; cin.ignore();
            try{
                seleccion.eliminarPorNumeroPlayera(numeroPlayera);
            }catch(const char* msg){
                cout << msg << endl;
            }
        }
        else if(op == "13"){
            int goles;
            cout << "Goles: ";
            cin >> goles; cin.ignore();
            try{
                seleccion.eliminarPorGolesMenorA(goles);
            }catch (const char* msg){
                cout << msg << endl;
            }
        }
        else if(op == "0"){
            break;
        }
    }
}
    #include <vector>
    void menu_mundial(vector<Seleccion>& mundial){
        string op;

        while(true){
            cout << "1) Agregar selección" << endl;
            cout << "2) Mostrar selecciones" << endl;
            cout << "3) Buscar selección" << endl;
            cout << "0) Salir" << endl;
            getline(cin, op);

            if(op == "1"){
                Seleccion seleccion;
                string nombre;

                cout << "Nombre de la selección: ";
                getline(cin, nombre);
                seleccion.setNombre(nombre);

                mundial.push_back(seleccion);
            }
            else if(op == "2"){
                for(size_t i = 0; i < mundial.size(); i++){
                    cout<< mundial[i].getNombre() << endl;


                }
            }
            else if(op == "3"){
                string nombre;

                cout << "Nombre de la selección: ";
                getline(cin, nombre);

                auto it = find_if(mundial.begin(), mundial.end(), [nombre](const Seleccion& seleccion){return nombre == seleccion.getNombre();});

                if(it ==mundial.end()){
                    cout << "La selección" << nombre << "No existe" << endl;
                    continue;
                }
                menu_seleccion(*it);
            }
            else if(op == "0"){
                break;
            }

        }
    }