//Progrma de gestión que vincula robots con sus señales telemáticas mediante archivos binarios para realizar administración de inventario, diagnósticos de fallas y reportes estadísticos
//Autor: Erik Daniel Rodríguez Ramirez
//Jose Ramon Chavez Toro
//Fecha: 11/12/2025
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;
struct robot { 
        int id;  
        int tipo;  
        char nombreD[20];  
        char pat[20];      
        char mat[20];      
        int sexo;  
        int edad;  
        int tipo; 
        char raza[20]; 
        int estatus; };
|
