#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <iostream>

int validarEntero(void){
    int numero;
    while(!(std::cin >> numero)){
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << "Debe ingresar un numero entero. Intente de nuevo: ";
    }
    std::cin.ignore();
    return numero;
}

float validarFlotante(void){
    float numero;
    while(!(std::cin >> numero)){
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << "Debe ingresar un numero flotante. Intente de nuevo: ";
    }
    std::cin.ignore();
    return numero;
}

#endif
