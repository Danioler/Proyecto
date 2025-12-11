#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <iostream>
using namespace std;

int validarEntero(void){
    int numero;
    while(!(cin >> numero)){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Intente de nuevo: ";
    }
    return numero;
}

float validarFlotante(void){
    float numero;
    while(!(cin >> numero)){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Intente de nuevo: ";
    }
    return numero;
}

#endif
