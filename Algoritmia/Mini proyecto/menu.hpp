#ifndef MENU_HPP
#define MENU_HPP

#include "bicipuerto.hpp"

size_t capturar_posicion(){
    size_t posicion;
    cout << "posicion: ";
    cin >> posicion;

    return posicion;
}

Bicicleta capturar_bicicleta(){
    Bicicleta bicicleta;
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

    return bicicleta;
}

    void menu(Bicipuerto &bicipuerto){
    int opcion;


    while (true)
    {
        cout << "1) Agregar una bicicleta al final" << endl;
        cout << "2) Eliminar la ultima bicicleta " << endl;
        cout << "3) Mostrar las bicicletas mostradas" << endl;
        cout << "4) Respalrar las bicicletas en .csv" << endl;
        cout << "0) Salir" << endl;
        cin >> opcion; cin.ignore();

        if(opcion==1){
            Bicicleta bicicleta;
            cin >> bicicleta;

            bicipuerto.agregarFinalBicicleta(bicicleta);
        }
        else if(opcion==2){
            bicipuerto.eliminarFinalBicicleta();
        }
        else if(opcion==3){
            bicipuerto.mostrar();
        }
        else if(opcion==4){
            bicipuerto.respaldar_csv();
        }
        else if(opcion==0){
            break;
        }
    }


}


#endif