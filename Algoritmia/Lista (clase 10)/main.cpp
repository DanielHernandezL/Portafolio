#include <iostream>
#include "menu.cpp"

using namespace std;

int main(){

    vector<Seleccion> mundial;
    menu_mundial(mundial);

    //  Seleccion seleccion ("México");
    //  menu_seleccion(seleccion);
    // Jugador j01("Daniel", 10, 5);
    // cout << j01 << "\n";
    // Jugador j02("Erick", 14, 3);
    // cout << j02 << "\n";
    // Jugador j03("Jose", 20, 4);
    // cout << j03 << "\n";
    // Jugador j04("Goretti", 1, 0);
    // cout << j04 << "\n";

    // // Jugador j02;
    // // cin >> j02;
    // // cout << j02;

    // Seleccion seleccion("México");
    // seleccion.agregarFinal(j01);
    // seleccion.agregarInicio(j02);
    // seleccion.agregarInicio(j03);
    // seleccion.agregarInicio(j04);
    // seleccion.mostrar();

    // seleccion.ordenarNombre();
    // seleccion.mostrar();

    // seleccion.ordenarNumeroPlayera();
    // seleccion.mostrar();

    // seleccion.ordenarGolesAnotados();
    // seleccion.mostrar();

    // seleccion.eliminarPorGolesMenorA(4);
    // seleccion.mostrar();

    // try{
    //     cout << seleccion.frente() << "\n";
    //     cout << seleccion.ultimo() << "\n";
    // } catch (const char* msg){
    //     cout << msg << endl;
    // }

    // try{
    //     seleccion.eliminarFinal();
    //     seleccion.mostrar();
    // }catch (const char* msg){
    //     cout << msg << endl;
    // }

    // try{
    //     seleccion.eliminarInicio();
    //     seleccion.mostrar();
    // }catch (const char* msg){
    //     cout << msg << endl;
    // }

    return 0;
}