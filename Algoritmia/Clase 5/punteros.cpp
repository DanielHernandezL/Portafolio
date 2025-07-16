#include <iostream>
using namespace std;

int main(){
    size_t* puntero = nullptr;
    size_t incremento = 100000000;
    size_t tam_actual = incremento;

    while(true){

    
        puntero = new size_t[tam_actual];

        for(size_t i = 0; i < tam_actual; i++){
            puntero[i] = i;
        }


        // for(size_t i = 0; i < tam_actual; i++){
        //     cout << puntero[i] << endl;
        // }
    
    tam_actual = tam_actual + incremento;
    cout << tam_actual << endl;
    delete []puntero;
    }

    return 0;
}

    // int a = 10;
    // cout << "a=" << a << endl;
    // int* puntero = &a;
    // cout << "puntero=" << puntero << endl;

    // *puntero = 12;
    // cout << "a=" << a << endl;