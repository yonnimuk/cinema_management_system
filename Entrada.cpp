#include <iostream>
using namespace std;
#include <cstdio>
#include <cstdlib>
#include "funcionesGenerales.h"
#include "rlutil.h"
using namespace rlutil;

const char * PATH_ENTRADAS = "datos/entradas.dat";

#include "Entrada.h"

bool Entrada::setPrecio(){
float precio1, precio2;
cout<<"Ingrese el precio: ";
precio1 = validarIngresoFlotante();
cin.ignore();
if(precio1<=0){
    cout << endl;
    msj_error("---El valor ingresado no es válido---");
    cout << endl;
    return false;
    }
msj_ok("Para confirmar, ingrese nuevamente el precio: ");
precio2 = validarIngresoFlotante();
cin.ignore();
if(precio2<=0){
    cout << endl;
    msj_error("---El valor ingresado no es válido---");
    cout << endl;
    anykey("Presione cualquier tecla para continuar. . .");
    return false;
   }
else if(precio1!=precio2){
    msj_error("---Los valores no son coincidentes---");
    anykey();
    return false;
 }
precio=precio1;
return true;
}

bool Entrada::grabarPrecio(int num){
FILE *p;
int aux = num-1;
p=fopen(PATH_ENTRADAS, "rb+");
if(p==NULL){
    msj_error("---Error en la apertura del archivo---");
    anykey();
    return false;
  }
fseek(p, sizeof(Entrada)*aux, 0);
bool escribio=fwrite(this, sizeof(Entrada), 1, p);
fclose(p);
return escribio;
}
