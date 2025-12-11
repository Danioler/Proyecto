#ifndef VALIDACIONES_H
#define VALIDACIONES_H

using namespace std;

int validarEntero(void){
    int numero;
    while(!(cin >> numero)){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Intente de nuevo: ";
    }
    cin.ignore();
    return numero;
}

float validarFlotante(void){
    float numero;
    while(!(cin >> numero)){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Intente de nuevo: ";
    }
    cin.ignore();
    return numero;
}

#endif
