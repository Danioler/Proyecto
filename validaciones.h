#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <iostream>
using namespace std;

int validarEntero(void){
    int numero;
    while(!(cin >> numero)){
        cout << "ERROR: Debe ingresar un numero entero valido. Intente de nuevo: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
    return numero;
}

float validarFlotante(void){
    float numero;
    while(!(cin >> numero)){
        cout << "ERROR: Debe ingresar un numero decimal valido. Intente de nuevo: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
    return numero;
}

#endif
