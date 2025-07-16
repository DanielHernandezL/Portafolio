#include <iostream>
#include <fstream>
using namespace std;

int main(){
   ifstream archivo("prueba.txt");

   if(archivo.fail()){
    cout << "Error al abrir el archivo" << endl;
    exit(-1);
   }
   string texto;
   getline(archivo, texto);

   cout << texto;

   archivo.close();


    return 0;
}

void crear_archivo(){
     ofstream archivo("C:C:\\Windows\\System32\\prueba.txt");

    if(archivo.fail()){
        cout << "Error al crear el archivo" << endl;
        exit(-1);
    }

    archivo << "Hola desde el escritorio de windows";

    archivo.close();
}