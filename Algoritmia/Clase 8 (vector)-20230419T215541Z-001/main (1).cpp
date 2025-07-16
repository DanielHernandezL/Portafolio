#include<iostream>
#include <vector>
#include<algorithm>

using namespace std;

int main(){
    vector<int> enteros;
    string op;

    while (true){
        cout << "1) push_back" << endl;
        cout << "2) pop_back" << endl;
        cout << "3) mostrar" << endl;
        cout << "4) mostrar (iteradores)" << endl;
        cout << "5) ordenar (asc)" << endl;
        cout << "6) ordenar (desc)" << endl;
        cout << "7) insertar" << endl;
        cout << "8) eliminar" << endl;
        cout << "9) información" << endl;
        cout << "10) reserve" << endl;
        cout << "11) shrink (encoger)"  << endl;
        cout << "0) salir"  <<endl;
        getline(cin, op);

        if(op == "1"){
            int entero;
            cout << "entero: ";
            cin >> entero; cin.ignore();

            enteros.push_back(entero);
        }
        else if(op == "2"){
            if(!enteros.empty()){
                enteros.pop_back();
            }
            else{
                cout << "lista o vector vacío" << endl;
            }
        }
        else if(op == "3"){
            for(size_t i =0; i < enteros.size(); i++){
                cout << enteros[i] << ", ";
            }
            cout << endl;
        }
        else if(op == "4"){
            auto it = enteros.begin(); // vector<int>::iterator
            while(it != enteros.end()){
                cout << *it << ", ";
                it ++;
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
            cout << "posición: ";
            cin >> posicion;

            int entero;
            cout << "entero: ";
            cin >> entero; cin.ignore();

            if(posicion < enteros.size()){
                auto p = enteros.begin() + posicion;
                enteros.insert(p, entero);
        }
        else{
            cout << "posición no válida" << endl;
         }
        }
        else if(op == "8"){
            if(!enteros.empty()){
                size_t posicion;
                cout << "posición: ";
                cin >> posicion; cin.ignore();

                if(posicion < enteros.size()){
                    auto p = enteros.begin() + posicion;
                    enteros.erase(p);
                }
                else{
                    cout << "posición no válida" <<endl;
                }
            }
            else{
                cout << "vector vacío, no se puede eliminar" << endl;
            }
        }
        else if(op == "9"){
            cout << "size: " << enteros.size() << endl;
            cout << "capacity: " << enteros.capacity() << endl;
            cout << "max_size: " << enteros.max_size() << endl;
        }
        else if(op == "10"){
            size_t nueva_capacidad;
            cout << "capacidad: ";
            cin >> nueva_capacidad; cin.ignore();

            if(nueva_capacidad > enteros.size()){
                enteros.reserve(nueva_capacidad);
            }
            else{
                cout << "la nueva capacidad es menor que el tamaño" << endl;
            }
        }
        else if(op == "11"){
            enteros.shrink_to_fit();
        }
        else if(op == "0"){
            break;
        }
    }
    

    return 0;
}
