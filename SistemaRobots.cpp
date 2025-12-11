#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "validaciones.h"
using namespace std;

struct robot { 
    int id; // Identificador unico
    char nombre[20]; 
    char modelo[20];
    char fabricante[20];
    int anio_fabricacion;
    float voltaje_nominal;
    float temperatura_max;
    float velocidad_max;
    int estatus; // 1 - activo, 0 - inactivo
};

struct senal { 
    int idRobot;
    int tipo_senal;
    float valor;
    int marca_tiempo;
    int estado;
};

int menu(void);
int menuConsultas(void);
int menuSenal(void);
int obtenerId(void);
void grabarId(int id);
void capturar(robot &rob, int &id);
void alta(robot &rob);
void bajas(robot &rob);
void cambios(robot &rob);
void consultaTodos(robot &rob);
void consultaUno(robot &rob);
void consultaEstatus(robot &rob);
void consultaRangoEdad(robot &rob);
void consultaVoltaje();
void consultaTemperatura();
void consultaFabricante();
void consultaVelocidad();
void registrarSenal(senal &sen);
void consultaSenal(senal &sen);
void generarDiagnostico(void);
void reporteRobots(void);
void reporteSenales(void);
void reporteEstadistico(void);
void imprimir(robot &rob);
void imprimir(senal &sen);

int main(){
    int op;
    int id;
    robot rob;
    senal sen;

    id = obtenerId();

    do{
        op=menu();
        switch(op){
            case 1:
                    capturar(rob, id);
                    alta(rob);
                    break;
            case 2:
                    cout << "\n>>> Entrando a BAJAS <<<\n";
                    system("pause");
                    bajas(rob);
                    break;
            case 3: // CAMBIOS - Modificar datos de robot
                    cambios(rob);
                    break;
            case 4: // CONSULTAS - Submenu de consultas
                    do{
                        op=menuConsultas();
                        switch(op){
                            case 1: consultaTodos(rob);          
                                    break;
                            case 2: consultaUno(rob);       
                                    break;
                            case 3: consultaEstatus(rob);        
                            
                                    break;
                            case 4: consultaRangoEdad(rob);      
                            
                                    break;
                            case 5: consultaVoltaje();          
                                    break;
                            case 6: consultaTemperatura();       
                                    break;
                            case 7: consultaFabricante();       
                                    break;
                            case 8: consultaVelocidad();         
                                    break;
                            case 9: break;                       
                            default: cout << "Error en la opcion\n";
                        }
                    } while(op!=9);
                    break;
            case 5:
                    do{
                        op=menuSenal();
                        switch(op){
                            case 1: registrarSenal(sen);
                                    break;
                            case 2: consultaSenal(sen);
                                    break;
                            case 3: generarDiagnostico();
                                    break;
                            case 4: break;
                            default: cout << "Error en la opcion\n";
                        }
                    } while(op!=4);
                    break;
            case 6:
                    do{
                        cout << "\n----------  MENU REPORTES  -----------\n";
                        cout << "Reporte de robots .......... 1\n";
                        cout << "Reporte de senales ......... 2\n";
                        cout << "Reporte estadistico ........ 3\n";
                        cout << "Salir de reportes .......... 4\n";
                        cout << "Selecciona: ";
                        cin >> op;
                        cin.ignore();
                        switch(op){
                            case 1: reporteRobots();
                                    break;
                            case 2: reporteSenales();
                                    break;
                            case 3: reporteEstadistico();
                                    break;
                            case 4: break;
                            default: cout << "Error en la opcion\n";
                        }
                    } while(op!=4);
                    break;
            case 7: break;
            default: cout << "Error en la opcion\n";
        }
    } while(op!=7);

    grabarId(id);

    return 0;
} // fin de main

void cambios(robot &rob){
    int id;
    string res;
    system("cls");
    
    cout << "CAMBIOS DE ROBOT\n";
    cout << "================\n";

    fstream arch;
    arch.open("robots.bin", ios::in | ios::out | ios::binary);
    if(arch){   
        cout << "Dame tu id: ";
        id = validarEntero();
        
        arch.seekg((id-1)*sizeof(robot), ios::beg);
        if(!arch.read((char *)&rob, sizeof(rob))){
            cout << "Robot no encontrado\n";
            system("pause");
            arch.close();
            return;
        }
        
        system("cls");
        cout << "Datos anteriores: \n";
        imprimir(rob);
        system("cls");
        cout << "Estas seguro de cambiar los datos del robot? (s/n) ";
        cin >> res;
        cin.ignore();
        
        if(res == "s" || res == "S"){
            system("cls");
            cout << "INGRESA LOS NUEVOS DATOS\n";
            cout << "========================\n";
            cout << "Id: " << rob.id << " (no se modifica)\n";
            cout << "Nuevo nombre del robot: ";
            cin.getline(rob.nombre, 20);
            cout << "Nuevo modelo: ";
            cin.getline(rob.modelo, 20);
            cout << "Nuevo fabricante: ";
            cin.getline(rob.fabricante, 20);
            cout << "Nuevo anio de fabricacion: ";
            rob.anio_fabricacion = validarEntero();
            cout << "\n(Voltaje, temperatura y velocidad no se modifican)\n";
            
            arch.write((char *)&rob, sizeof(rob));
            cout << "\n***CAMBIO REALIZADO CON EXITO*** \n";
            system("pause");
        }
        else {
            cout << "Operacion cancelada\n";
            system("pause");
        }
    }
    else {
        cout << "Error en el archivo\n";
        arch.close();
    }

    arch.close();
} // fin cambios

int menuConsultas(){
    system("cls");
    int op;

    cout << "----------  MENU CONSULTAS  -----------\n";
    cout << "Ver todos los robots ......... 1\n";
    cout << "Consulta un robot ............ 2\n";
    cout << "Consulta por estatus ......... 3\n";
    cout << "Consulta por anio ............ 4\n";
    cout << "Consulta voltaje ............. 5\n";
    cout << "Consulta temperatura ......... 6\n";
    cout << "Consulta fabricante .......... 7\n";
    cout << "Consulta velocidad ........... 8\n";
    cout << "Salir de consultas ........... 9\n";
    cout << "Selecciona: ";
    cin >> op;
    cin.ignore();

    return op;
} // fin de menu Consultas

void consultaUno(robot &rob){
    ifstream arch;
    arch.open("robots.bin", ios::in | ios::binary);
    int id;
    if(arch){
        cout << "Ingrese el id: ";
        id = validarEntero();
        arch.seekg((id-1)*sizeof(rob), ios::beg);
        
        if(!arch.read((char *)&rob, sizeof(rob))){
            cout << "Error: No se pudo leer el robot\n";
            system("pause");
            arch.close();
            return;
        }
        
        // Verificar que el ID coincida
        if(rob.id != id){
            cout << "Error: Robot con ID " << id << " no existe\n";
            system("pause");
            arch.close();
            return;
        }
        
        system("cls");
        imprimir(rob);
    }
    else {
        cout << "Error en el archivo\n";
        arch.close();
    }

    arch.close();
} //fin de consultaUno

void bajas(robot &rob){
    system("cls");
    cout << "PROCESO DE BAJA DE ROBOT\n";
    cout << "=========================\n";
    int id;
    string res;

    cout << "Intentando abrir: robots.bin\n";
    fstream arch;
    arch.open("robots.bin", ios::in | ios::out | ios::binary);
    if(!arch){
        cout << "\nERROR: No se pudo abrir robots.bin\n";
        cout << "Verifica que hayas registrado robots primero (opcion 1)\n";
        system("pause");
        return;
    }
    
    cout << "Archivo abierto correctamente\n";
    cout << "Dame el ID del robot a dar de baja: ";
    id = validarEntero();
    cin.ignore();
    
    arch.seekg((id-1)*sizeof(robot), ios::beg);
    if(!arch.read((char *)&rob, sizeof(rob))){
        cout << "Error: Robot no encontrado con ID: " << id << "\n";
        system("pause");
        arch.close();
        return;
    }
    
    if(rob.estatus == 0){
        system("cls");
        cout << "\n*** ATENCION ***\n";
        cout << "El robot '" << rob.nombre << "' ya esta dado de baja\n";
        system("pause");
        arch.close();
        return;
    }
    
    system("cls");
    cout << "DATOS DEL ROBOT A DAR DE BAJA:\n";
    imprimir(rob);
    cout << "\nEstas seguro de dar de baja este robot? (s/n): ";
    cin >> res;
    cin.ignore();
    
    if(res == "s"){
        rob.estatus=0;
        arch.write((char *)&rob, sizeof(rob));
        cout << "\n*** BAJA EXITOSA ***\n";
        cout << "El robot " << rob.nombre << " ha sido desactivado\n";
        system("pause");
    }
    else{
        cout << "Operacion cancelada\n";
        system("pause");
    }

    arch.close();
} //Fin de bajas

void consultaEstatus(robot &rob){
    int estatus;
    int contador = 0;
    ifstream arch;
    arch.open("robots.bin", ios::in | ios::binary);
    if(arch){
        arch.seekg(0, ios::beg);
        cout << "1 - Activo     0 - Baja: ";
        cout << "Dame el estatus: ";
        estatus = validarEntero();

        while(arch.read((char *)&rob,sizeof(rob))){
            if(rob.id == 0) continue; // Saltar posiciones vacías
            if(rob.estatus != estatus) continue;
            contador++;
            system("cls");
            imprimir(rob);
        }
        
        if(contador == 0){
            cout << "\nNo hay robots con estatus " << (estatus == 1 ? "ACTIVO" : "INACTIVO") << "\n";
        } else {
            cout << "\nTotal de robots encontrados: " << contador << "\n";
        }
        system("pause");
    }
    else {
        cout << "Error en el archivo";
        system("pause");
        arch.close();
    }
} // fin de consulta estatus

void consultaRangoEdad(robot &rob){
    int min;
    int max;
    int contador = 0;
    ifstream arch;
    arch.open("robots.bin", ios::in | ios::binary);
    if(arch){
        arch.seekg(0, ios::beg);

        cout << "Dame el anio de fabricacion minimo: ";
        min = validarEntero();
        cout << "Dame el anio de fabricacion maximo: ";
        max = validarEntero();

        system("cls");
        cout << "ROBOTS FABRICADOS ENTRE " << min << " Y " << max << "\n";
        cout << "==========================================\n\n";

        while(arch.read((char *)&rob,sizeof(rob))){
            if(rob.id == 0) continue; // Saltar posiciones vacías
            if(rob.estatus == 0) continue; // Saltar inactivos
            if(rob.anio_fabricacion >= min && rob.anio_fabricacion <= max){
                contador++;
                cout << "Robot " << contador << ":\n";
                cout << "  ID: " << rob.id << "\n";
                cout << "  Nombre: " << rob.nombre << "\n";
                cout << "  Modelo: " << rob.modelo << "\n";
                cout << "  Fabricante: " << rob.fabricante << "\n";
                cout << "  Anio: " << rob.anio_fabricacion << "\n";
                cout << "---\n\n";
            }
        }
        
        if(contador == 0){
            cout << "No hay robots fabricados entre " << min << " y " << max << "\n";
        } else {
            cout << "\nTotal encontrados: " << contador << "\n";
        }
        system("pause");
    }
    else {
        cout << "Error en el archivo";
        system("pause");
        arch.close();
    }
} // fin de consulta rango edad

void consultaTodos(robot &rob){
    ifstream arch;
    arch.open("robots.bin", ios::in | ios::binary);
    if(arch){
        arch.seekg(0, ios::beg);
        while(!arch.eof()){
            arch.read((char *)&rob,sizeof(rob));
            system("cls");
            imprimir(rob);
        }
        cout << "\nFin del archivo\n";
    }
    else {
        cout << "Error en el archivo";
        system("pause");
        arch.close();
    }
} // fin de consulta todos

void consultaVoltaje(){
    ifstream arch;
    ifstream archSen;
    senal sen;
    robot rob;
    int contador = 0;
    
    system("cls");
    cout << "CONSULTA DE VOLTAJE\n";
    cout << "===================\n\n";
    
    archSen.open("senales.bin", ios::in | ios::binary);
    if(!archSen){
        cout << "No hay senales registradas\n";
        system("pause");
        return;
    }
    
    arch.open("robots.bin", ios::in | ios::binary);
    if(!arch){
        cout << "Error en el archivo de robots\n";
        system("pause");
        return;
    }
    
    while(archSen.read((char *)&sen, sizeof(sen))){
        if(sen.tipo_senal == 1 && sen.estado == 2){
            contador++;
            arch.seekg((sen.idRobot-1)*sizeof(robot), ios::beg);
            arch.read((char *)&rob, sizeof(rob));
            
            cout << "Problema " << contador << ":\n";
            cout << "Robot: " << rob.nombre << " (ID: " << rob.id << ")\n";
            cout << "Voltaje detectado: " << sen.valor << " V\n";
            cout << "Voltaje nominal: " << rob.voltaje_nominal << " V\n";
            cout << "---\n\n";
        }
    }
    
    if(contador == 0){
        cout << "No hay problemas de alto voltaje detectados\n";
    }
    
    arch.close();
    archSen.close();
    system("pause");
} // fin consulta alto voltaje

void consultaTemperatura(){
    ifstream arch;
    ifstream archSen;
    senal sen;
    robot rob;
    int contador = 0;
    
    system("cls");
    cout << "CONSULTA DE TEMPERATURA\n";
    cout << "=======================\n\n";
    
    archSen.open("senales.bin", ios::in | ios::binary);
    if(!archSen){
        cout << "No hay senales registradas\n";
        system("pause");
        return;
    }
    
    arch.open("robots.bin", ios::in | ios::binary);
    if(!arch){
        cout << "Error en el archivo de robots\n";
        system("pause");
        return;
    }
    
    while(archSen.read((char *)&sen, sizeof(sen))){
        if(sen.tipo_senal == 2 && sen.estado >= 1){
            contador++;
            arch.seekg((sen.idRobot-1)*sizeof(robot), ios::beg);
            arch.read((char *)&rob, sizeof(rob));
            
            cout << "Problema " << contador << ":\n";
            cout << "Robot: " << rob.nombre << " (ID: " << rob.id << ")\n";
            cout << "Temperatura detectada: " << sen.valor << " C\n";
            cout << "Temperatura maxima: " << rob.temperatura_max << " C\n";
            cout << "---\n\n";
        }
    }
    
    if(contador == 0){
        cout << "No hay problemas de alta temperatura detectados\n";
    }
    
    arch.close();
    archSen.close();
    system("pause");
} // fin consulta temperatura

void consultaFabricante(){
    ifstream arch;
    robot rob;
    string fabricante;
    int contador = 0;
    
    system("cls");
    cout << "CONSULTA POR FABRICANTE\n";
    cout << "=======================\n\n";
    
    cout << "Ingresa el nombre del fabricante: ";
    cin.ignore();
    getline(cin, fabricante);
    
    arch.open("robots.bin", ios::in | ios::binary);
    if(!arch){
        cout << "Error en el archivo de robots\n";
        system("pause");
        return;
    }
    
    cout << "\nRobots del fabricante '" << fabricante << "':\n";
    cout << "-------------------------------------------\n\n";
    
    while(arch.read((char *)&rob, sizeof(rob))){
        if(rob.estatus == 1 && string(rob.fabricante).find(fabricante) != string::npos){
            contador++;
            cout << "Robot " << contador << ":\n";
            cout << "  ID: " << rob.id << "\n";
            cout << "  Nombre: " << rob.nombre << "\n";
            cout << "  Modelo: " << rob.modelo << "\n";
            cout << "  Fabricante: " << rob.fabricante << "\n";
            cout << "  Anio: " << rob.anio_fabricacion << "\n";
            cout << "---\n\n";
        }
    }
    
    if(contador == 0){
        cout << "No se encontraron robots del fabricante '" << fabricante << "'\n";
    } else {
        cout << "\nTotal encontrados: " << contador << "\n";
    }
    
    arch.close();
    system("pause");
} // fin consulta fabricante

void consultaVelocidad(){
    ifstream arch;
    ifstream archSen;
    senal sen;
    robot rob;
    int contador = 0;
    
    system("cls");
    cout << "CONSULTA DE VELOCIDAD\n";
    cout << "=====================\n\n";
    
    archSen.open("senales.bin", ios::in | ios::binary);
    if(!archSen){
        cout << "No hay senales registradas\n";
        system("pause");
        return;
    }
    
    arch.open("robots.bin", ios::in | ios::binary);
    if(!arch){
        cout << "Error en el archivo de robots\n";
        system("pause");
        return;
    }
    
    while(archSen.read((char *)&sen, sizeof(sen))){
        if(sen.tipo_senal == 3 && sen.estado >= 1){
            contador++;
            arch.seekg((sen.idRobot-1)*sizeof(robot), ios::beg);
            arch.read((char *)&rob, sizeof(rob));
            
            cout << "Problema " << contador << ":\n";
            cout << "Robot: " << rob.nombre << " (ID: " << rob.id << ")\n";
            cout << "Velocidad detectada: " << sen.valor << " km/h\n";
            cout << "Velocidad maxima: " << rob.velocidad_max << " km/h\n";
            cout << "---\n\n";
        }
    }
    
    if(contador == 0){
        cout << "No hay problemas de velocidad detectados\n";
    }
    
    arch.close();
    archSen.close();
    system("pause");
} // fin consulta velocidad

void imprimir(robot &rob){
    cout << "============= DATOS DEL ROBOT =============\n";
    cout << "id: " << rob.id << endl;
    cout << "Nombre del robot: " << rob.nombre << endl;
    cout << "Modelo: " << rob.modelo << endl;
    cout << "Fabricante: " << rob.fabricante << endl;
    cout << "Anio de fabricacion: " << rob.anio_fabricacion << endl;
    cout << "Voltaje nominal: " << rob.voltaje_nominal << " V" << endl;
    cout << "Temperatura maxima: " << rob.temperatura_max << " C" << endl;
    cout << "Velocidad maxima: " << rob.velocidad_max << " km/h" << endl;
    cout << "Estatus: " << ((rob.estatus == 1) ? "ACTIVO" : "INACTIVO") << endl;
    system("pause");
} // fin de imprimir

void alta(robot &rob){
    fstream arch;
    
    arch.open("robots.bin", ios::in | ios::out | ios::binary);
    if(!arch){
        cout << "ERROR: Archivo robots.bin no encontrado\n";
        system("pause");
        return;
    }
    else{
        // Escribir en la posición correspondiente al ID
        arch.seekp((rob.id-1)*sizeof(robot), ios::beg);
        arch.write((char *)&rob, sizeof(rob));
        cout << "\n*** EXITO ***\n";
        cout << "Robot '" << rob.nombre << "' registrado con ID: " << rob.id << "\n";
    }

    arch.close();
    system("pause");
}

void grabarId(int id){
    ofstream arch;
    arch.open("controlId_Robots.txt", ios::out);
    if(arch)
        arch << id;
    else
        cout << "Error en el archivo\n";
    arch.close();
} //fin de grabar Id;

void capturar(robot &rob, int &id){
    system("cls");
    cout << "CAPTURA DE LOS DATOS DEL ROBOT\n";
    cout << "===============================\n";
    cin.ignore();
    cout << "Id: " << id << endl;
    cout << "Ingresar el nombre del robot: ";
    cin.getline(rob.nombre, 20);
    cout << "Ingresa el modelo: ";
    cin.getline(rob.modelo, 20);
    cout << "Ingresa el fabricante: ";
    cin.getline(rob.fabricante, 20);
    cout << "Ingresa el anio de fabricacion: ";
    rob.anio_fabricacion = validarEntero();
    cout << "Ingresa el voltaje nominal (V): ";
    rob.voltaje_nominal = validarFlotante();
    cout << "Ingresa la temperatura maxima (C): ";
    rob.temperatura_max = validarFlotante();
    cout << "Ingresa la velocidad maxima (km/h): ";
    rob.velocidad_max = validarFlotante();
    
    rob.estatus = 1;
    rob.id = id;

    id = id + 1;
} // fin de capturar

int obtenerId(void){
    int id = 1; // Inicializar en 1 por defecto
    ifstream arch;
    arch.open("controlId_Robots.txt", ios::in);
    if(arch){
        arch >> id;
        arch.close();
    }
    else{
        cout << "Error al abrir el archivo\n";
        arch.close();
    }

    return id;
} // fin de obtenerId

int menu(void){
    system("cls");
    int op;

    cout << "----------  MENU PRINCIPAL  -----------\n";
    cout << "Registrar robot (ALTA) .......... 1\n";
    cout << "Desactivar robot (BAJA) ........ 2\n";
    cout << "Modificar robot (CAMBIOS) ...... 3\n";
    cout << "Consultar robots ............... 4\n";
    cout << "Gestion de senales ............. 5\n";
    cout << "Reportes estadisticos .......... 6\n";
    cout << "Salir ........................... 7\n";
    cout << "Selecciona: ";
    cin >> op;
    cin.ignore();

    return op;
}// fin de menu

int menuSenal(void){
    system("cls");
    int op;

    cout << "----------  MENU SENALES  -----------\n";
    cout << "Registrar senal ................ 1\n";
    cout << "Consultar senales .............. 2\n";
    cout << "Generar diagnostico ............ 3\n";
    cout << "Salir ........................... 4\n";
    cout << "Selecciona: ";
    cin >> op;
    cin.ignore();

    return op;
}// fin de menu senal

void registrarSenal(senal &sen){
    system("cls");
    int id;
    robot rob;
    ifstream archRob;
    ofstream archSen;
    
    cout << "REGISTRO DE SENAL TELEMATICA\n";
    cout << "============================\n";
    
    cout << "Id del robot: ";
    id = validarEntero();
    
    archRob.open("robots.bin", ios::in | ios::binary);
    if(!archRob){
        cout << "Error en el archivo de robots\n";
        system("pause");
        return;
    }
    
    bool encontrado = false;
    while(!archRob.eof()){
        archRob.read((char *)&rob, sizeof(rob));
        if(rob.id == id && rob.estatus == 1){
            encontrado = true;
            break;
        }
    }
    archRob.close();
    
    if(!encontrado){
        cout << "Robot no existe o esta inactivo\n";
        system("pause");
        return;
    }
    
    sen.idRobot = id;
    
    cout << "\nTipos de senales:\n";
    cout << "1. Voltaje (V)\n";
    cout << "2. Temperatura (C)\n";
    cout << "3. Velocidad (km/h)\n";
    cout << "4. Carga de bateria (%)\n";
    cout << "5. Humedad (%)\n";
    cout << "Selecciona tipo: ";
    sen.tipo_senal = validarEntero();
    
    if(sen.tipo_senal < 1 || sen.tipo_senal > 5){
        cout << "Tipo invalido\n";
        system("pause");
        return;
    }
    
    cout << "Ingresa el valor: ";
    sen.valor = validarFlotante();
    
    sen.marca_tiempo = 0;
    sen.estado = 0;
    
    // Determinar estado basado en tipo y valor
    switch(sen.tipo_senal){
        case 1: // Voltaje
            if(sen.valor < rob.voltaje_nominal * 0.8){ //tolerancia 20% BAJO
                sen.estado = 2;
                cout << "ADVERTENCIA: Voltaje bajo\n";
            } else if(sen.valor > rob.voltaje_nominal * 1.2){  //tolerancia 20% ALTO        
                sen.estado = 2;
                cout << "ADVERTENCIA: Voltaje alto\n";
            }
            break;
        case 2: // Temperatura
            if(sen.valor > rob.temperatura_max){ // Sobre temperatura
                sen.estado = 2;
                cout << "ALERTA: Temperatura excedida\n";
            }
            break;
        case 3: // Velocidad
            if(sen.valor > rob.velocidad_max){ // Sobre velocidad
                sen.estado = 2;
                cout << "ALERTA: Velocidad excedida\n";
            }
            break;
        case 4: // Bateria
            if(sen.valor < 20){ // Bateria baja
                sen.estado = 2;
                cout << "ALERTA: Bateria baja\n";
            }
            break;
        case 5: // Humedad
            if(sen.valor > 90 || sen.valor < 30){
                sen.estado = 1;
                cout << "AVISO: Humedad fuera de rango\n";
            }
            break;
    }
    
    archSen.open("senales.bin", ios::out | ios::app | ios::binary);
    if(archSen){
        archSen.write((char *)&sen, sizeof(sen));
        cout << "Senal registrada con exito\n";
    } else {
        cout << "Error en el archivo de senales\n";
    }
    archSen.close();
    
    system("pause");
} // fin de registrar senal

void consultaSenal(senal &sen){
    system("cls");
    int id;
    robot rob;
    ifstream archSen, archRob;
    int contador = 0;
    
    cout << "CONSULTA DE SENALES DE UN ROBOT\n";
    cout << "================================\n";
    
    cout << "Id del robot: ";
    id = validarEntero();
    
    archRob.open("robots.bin", ios::in | ios::binary);
    if(!archRob){
        cout << "Error en el archivo de robots\n";
        system("pause");
        return;
    }
    
    bool encontrado = false;
    while(!archRob.eof()){
        archRob.read((char *)&rob, sizeof(rob));
        if(rob.id == id && rob.estatus == 1){
            encontrado = true;
            break;
        }
    }
    archRob.close();
    
    if(!encontrado){
        cout << "Robot no existe o esta inactivo\n";
        system("pause");
        return;
    }
    
    archSen.open("senales.bin", ios::in | ios::binary);
    if(!archSen){
        cout << "No hay senales registradas\n";
        system("pause");
        return;
    }
    
    while(!archSen.eof()){
        archSen.read((char *)&sen, sizeof(sen));
        if(sen.idRobot == id){
            contador++;
            system("cls");
            cout << "CONSULTA DE SENALES DE UN ROBOT\n";
            cout << "================================\n\n";
            cout << "Robot: " << rob.nombre << endl;
            cout << "Modelo: " << rob.modelo << endl;
            cout << "-----------------------------------\n";
            cout << "\nSenal " << contador << ":\n";
            imprimir(sen);
        }
    }
    
    if(contador == 0){
        cout << "No hay senales para este robot\n";
    }
    
    archSen.close();
    system("pause");
} // fin consulta senal

void generarDiagnostico(void){
    system("cls");
    ifstream archSen;
    ofstream archDiag;
    senal sen;
    robot rob;
    ifstream archRob;
    int problemas = 0;
    
    cout << "GENERANDO DIAGNOSTICO...\n";
    cout << "Espere por favor...\n\n";
    
    archSen.open("senales.bin", ios::in | ios::binary);
    archDiag.open("diagnostico.txt", ios::out);
    
    if(!archSen || !archDiag){
        cout << "Error en los archivos\n";
        system("pause");
        return;
    }
    
    archDiag << "DIAGNOSTICO DE ROBOTS\n";
    archDiag << "====================\n\n";
    
    cout << "PROBLEMAS DETECTADOS:\n";
    cout << "====================\n\n";
    
    while(!archSen.eof()){
        archSen.read((char *)&sen, sizeof(sen));
        
        if(sen.estado >= 1){
            problemas++;
            
            archRob.open("robots.bin", ios::in | ios::binary);
            robot robTemp;
            bool robEncontrado = false;
            
            while(!archRob.eof()){
                archRob.read((char *)&robTemp, sizeof(robTemp));
                if(robTemp.id == sen.idRobot){
                    rob = robTemp;
                    robEncontrado = true;
                    break;
                }
            }
            archRob.close();
            
            if(robEncontrado){
                cout << "PROBLEMA " << problemas << ":\n";
                cout << "Robot: " << rob.nombre << " (ID: " << rob.id << ")\n";
                
                string tipoProblema = "";
                string detalles = "";
                
                switch(sen.tipo_senal){
                    case 1: 
                        tipoProblema = "Voltaje anomalo"; 
                        detalles = "Voltaje nominal: " + to_string(rob.voltaje_nominal) + " V";
                        break;
                    case 2: 
                        tipoProblema = "Temperatura elevada"; 
                        detalles = "Temperatura maxima: " + to_string(rob.temperatura_max) + " C";
                        break;
                    case 3: 
                        tipoProblema = "Velocidad excedida"; 
                        detalles = "Velocidad minima: 0 km/h | Velocidad maxima: " + to_string(rob.velocidad_max) + " km/h";
                        break;
                    case 4: 
                        tipoProblema = "Bateria baja"; 
                        detalles = "Minimo recomendado: 20%";
                        break;
                    case 5: 
                        tipoProblema = "Humedad fuera de rango"; 
                        detalles = "Rango normal: 30% - 90%";
                        break;
                }
                
                cout << "Tipo: " << tipoProblema << endl;
                cout << "Valor detectado: " << sen.valor << endl;
                cout << detalles << endl;
                cout << "Severidad: " << (sen.estado == 2 ? "CRITICA" : "AVISO") << endl;
                cout << "---\n\n";
                
                archDiag << "PROBLEMA " << problemas << ":\n";
                archDiag << "Robot: " << rob.nombre << " (ID: " << rob.id << ")\n";
                archDiag << "Tipo: " << tipoProblema << endl;
                archDiag << "Valor detectado: " << sen.valor << endl;
                archDiag << detalles << endl;
                archDiag << "Severidad: " << (sen.estado == 2 ? "CRITICA" : "AVISO") << endl;
                archDiag << "---\n\n";
            }
        }
    }
    
    if(problemas == 0){
        cout << "NO HAY PROBLEMAS DETECTADOS\n";
        archDiag << "NO HAY PROBLEMAS DETECTADOS\n";
    } else {
        cout << "\nTOTAL DE PROBLEMAS: " << problemas << endl;
        archDiag << "\nTOTAL DE PROBLEMAS: " << problemas << endl;
    }
    
    archSen.close();
    archDiag.close();
    
    cout << "\nDiagnostico guardado en diagnostico.txt\n";
    system("pause");
} // fin de diagnostico

void imprimir(senal &sen){
    string tipo;
    switch(sen.tipo_senal){
        case 1: tipo = "Voltaje"; break;
        case 2: tipo = "Temperatura"; break;
        case 3: tipo = "Velocidad"; break;
        case 4: tipo = "Bateria"; break;
        case 5: tipo = "Humedad"; break;
        default: tipo = "Desconocido";
    }
    
    cout << "  Tipo: " << tipo << endl;
    cout << "  Valor: " << sen.valor << endl;
    cout << "  Estado: " << (sen.estado == 0 ? "Normal" : sen.estado == 1 ? "Aviso" : "Critico") << endl;
} // fin de imprimir senal
void reporteRobots(void){
    system("cls");
    ifstream archivo;
    robot rob;
    int activos = 0, inactivos = 0;
    
    archivo.open("robots.bin", ios::in | ios::binary);
    if(!archivo){
        cout << "ERROR: Archivo robots.bin no encontrado\n";
        system("pause");
        return;
    }
    
    ofstream arch_txt("reportes.txt", ios::app);
    if(!arch_txt){
        cout << "ERROR: No se puede crear archivo reportes.txt\n";
        system("pause");
        archivo.close();
        return;
    }
    
    cout << "REPORTE DE ROBOTS\n";
    cout << "=================\n\n";
    
    arch_txt << "REPORTE DE ROBOTS\n";
    arch_txt << "=================\n";
    
    while(archivo.read((char *)&rob, sizeof(rob))){
        if(rob.id != 0){
            if(rob.estatus == 1) activos++;
            else inactivos++;
        }
    }
    
    cout << "Total de robots registrados: " << (activos + inactivos) << "\n";
    cout << "Robots activos: " << activos << "\n";
    cout << "Robots inactivos: " << inactivos << "\n";
    cout << "Porcentaje activos: " << (activos > 0 ? (activos * 100 / (activos + inactivos)) : 0) << "%\n";
    
    arch_txt << "Total de robots registrados: " << (activos + inactivos) << "\n";
    arch_txt << "Robots activos: " << activos << "\n";
    arch_txt << "Robots inactivos: " << inactivos << "\n";
    arch_txt << "Porcentaje activos: " << (activos > 0 ? (activos * 100 / (activos + inactivos)) : 0) << "%\n\n";
    
    archivo.close();
    arch_txt.close();
    system("pause");
}

void reporteSenales(void){
    system("cls");
    ifstream archivo;
    senal sen;
    int normal = 0, aviso = 0, critico = 0;
    
    archivo.open("senales.bin", ios::in | ios::binary);
    if(!archivo){
        cout << "ERROR: Archivo senales.bin no encontrado\n";
        system("pause");
        return;
    }
    
    ofstream arch_txt("reportes.txt", ios::app);
    if(!arch_txt){
        cout << "ERROR: No se puede crear archivo reportes.txt\n";
        system("pause");
        archivo.close();
        return;
    }
    
    cout << "REPORTE DE SENALES\n";
    cout << "==================\n\n";
    
    arch_txt << "REPORTE DE SENALES\n";
    arch_txt << "==================\n";
    
    while(archivo.read((char *)&sen, sizeof(sen))){
        if(sen.estado == 0) normal++;
        else if(sen.estado == 1) aviso++;
        else if(sen.estado == 2) critico++;
    }
    
    cout << "Total de senales registradas: " << (normal + aviso + critico) << "\n";
    cout << "Senales normales: " << normal << "\n";
    cout << "Senales en aviso: " << aviso << "\n";
    cout << "Senales criticas: " << critico << "\n";
    
    arch_txt << "Total de senales registradas: " << (normal + aviso + critico) << "\n";
    arch_txt << "Senales normales: " << normal << "\n";
    arch_txt << "Senales en aviso: " << aviso << "\n";
    arch_txt << "Senales criticas: " << critico << "\n\n";
    
    archivo.close();
    arch_txt.close();
    system("pause");
}

void reporteEstadistico(void){
    system("cls");
    ifstream archivo;
    robot rob;
    float voltajePromedio = 0, tempPromedio = 0, velPromedio = 0;
    int contador = 0;
    
    archivo.open("robots.bin", ios::in | ios::binary);
    if(!archivo){
        cout << "ERROR: Archivo robots.bin no encontrado\n";
        system("pause");
        return;
    }
    
    ofstream arch_txt("reportes.txt", ios::app);
    if(!arch_txt){
        cout << "ERROR: No se puede crear archivo reportes.txt\n";
        system("pause");
        archivo.close();
        return;
    }
    
    cout << "REPORTE ESTADISTICO\n";
    cout << "===================\n\n";
    
    arch_txt << "REPORTE ESTADISTICO\n";
    arch_txt << "===================\n";
    
    while(archivo.read((char *)&rob, sizeof(rob))){
        if(rob.id != 0 && rob.estatus == 1){
            voltajePromedio += rob.voltaje_nominal;
            tempPromedio += rob.temperatura_max;
            velPromedio += rob.velocidad_max;
            contador++;
        }
    }
    
    if(contador > 0){
        cout << "Promedio de voltaje nominal: " << (voltajePromedio / contador) << " V\n";
        cout << "Promedio de temperatura maxima: " << (tempPromedio / contador) << " C\n";
        cout << "Promedio de velocidad maxima: " << (velPromedio / contador) << " km/h\n";
        cout << "Cantidad de robots analizados: " << contador << "\n";
        
        arch_txt << "Promedio de voltaje nominal: " << (voltajePromedio / contador) << " V\n";
        arch_txt << "Promedio de temperatura maxima: " << (tempPromedio / contador) << " C\n";
        arch_txt << "Promedio de velocidad maxima: " << (velPromedio / contador) << " km/h\n";
        arch_txt << "Cantidad de robots analizados: " << contador << "\n\n";
    } else {
        cout << "No hay robots activos para analizar\n";
        arch_txt << "No hay robots activos para analizar\n\n";
    }
    
    archivo.close();
    arch_txt.close();
    system("pause");
}