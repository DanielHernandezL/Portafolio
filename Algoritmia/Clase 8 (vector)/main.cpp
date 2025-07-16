#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> enteros;
    string op;

    while(true){
        cout << "1) push_back" << endl;
        cout << "2) pop_back" << endl;
        cout << "3) Mostrar" << endl;
        cout << "4) Mosrar (iteradores)" << endl;
        cout << "5) Ordenar (asc)" << endl;
        cout << "6) Ordenar (desc)" << endl;
        cout << "7) Insertar" << endl;
        cout << "8) Eliminar" << endl;
        cout << "9) Información" << endl;
        cout << "10) Reserve (expandir)" << endl;
        cout << "11) shrink (encoger)" << endl;
        cout << "0) Salir" << endl;
        getline(cin, op);

        if(op == "1"){
            int entero;
            cout << "Entero: ";
            cin >> entero; cin.ignore();

            enteros.push_back(entero);
        }
        if(op == "2"){
            if(!enteros.empty()){
                enteros.pop_back();
            } else {
                cout << "Vector vacio" << endl;
                
            }
            
        }
        if(op == "3"){
            for(size_t i = 0; i < enteros.size(); i++){
                cout << enteros[i] << ", ";
            }
            cout << endl;
        }
        else if(op == "4"){
            auto it = enteros.begin(); //auto se utiliza para no poner todo  esto: vector<int>::iterador
            while(it != enteros.end()){
                cout << *it << ", ";
                it++;
            }
            cout << endl;
        }
        else if(op == "5"){
            sort(enteros.begin(), enteros.end());
        }
        else if(op == "6"){
            sort(enteros.begin(), enteros.end(), greater<int>());
        }
        else if(op == "7"){
            size_t posicion;
            cout << "Posicion: ";
            cin >> posicion;

            int entero;
            cout << "Entero: ";
            cin >> entero; cin.ignore();

            if(posicion < enteros.size()){
                auto p = enteros.begin() + posicion;
                enteros.insert(p, entero);
            } else{
                cout << "Posición no válida" << endl;
            }
        }
        if(op == "8"){
            if(!enteros.empty()){
                size_t posicion;
                cout << "Posición: ";
                cin >> posicion; cin.ignore();

                if(posicion < enteros.size()){
                    auto p = enteros.begin()+posicion;
                    enteros.erase(p);
                } else {
                    cout << "Posicion no valida" << endl;
                }

            } else {
                cout << "El vector está vacío, no se puede eliminar" << endl;
            }
        }
        else if(op == "9"){
            cout << "size: " << enteros.size() << endl;
            cout << "capacity: " << enteros.capacity() << endl;
            cout << "max_size: " << enteros.max_size() << endl;
        }
        else if(op == "10"){
            size_t nueva_capacidad;
            cout << "Capacidad: ";
            cin >> nueva_capacidad; cin.ignore();

            if(nueva_capacidad > enteros.size()){
                enteros.reserve(nueva_capacidad);
            } else {
                cout << "La nueva capacidad es menor al tamaño";
            }
        }
        else if(op == "11"){
            enteros.shrink_to_fit();
        }
        if(op == "0"){
            break;
        }
        
        }

    return 0;
}