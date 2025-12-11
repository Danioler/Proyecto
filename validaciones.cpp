#include <iostream>
using namespace std;
#include "validaciones.h"

int validarEntero(void){
    int numero;
    while(!(cin >> numero)){
        cout << "ERROR: Debe ingresar un numero entero valido. Intente de nuevo: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
    return numero;
} // fin validar entero

float validarFlotante(void){
    float numero;
    while(!(cin >> numero)){
        cout << "ERROR: Debe ingresar un numero decimal valido. Intente de nuevo: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
    return numero;
} // fin validar flotante
