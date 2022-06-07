/*
 * Passenger.h
 *
 *  Created on: 19 may. 2022
 *
 */

#ifndef PASSENGER_H_
#define PASSENGER_H_

#include "utn.h"
#include "LinkedList.h"
#include "Validations.h"

typedef struct
{
	int id;
	char nombre[50];
	char apellido[50];
	float precio;
	int tipoPasajero;//1-EconomyClass 2-ExecutiveClass 3-FirstClass
	char codigoVuelo[8];
	int estadoVuelo;//1-En Vuelo 2-En Horario 3-Aterrizado 4-Demorado
}Passenger;

Passenger* passenger_new();
Passenger* passenger_newParametros(int idStr,char* nombre,char* apellido,float precio,
								   char* codigoVuelo,int tipoPasajero,
								   int estadoVuelo);
Passenger* passenger_newParametrosStr( char* idStr,char* nombreStr,
									   char* apellidoStr,char* precioStr,
									   char* codigoVueloStr,char* tipoPasajeroStr,
									   char* estadoVueloStr);
void passenger_delete();

void passenger_delete(Passenger* this);

int passenger_setId(Passenger* this,int id);
int passenger_setIdTxt(Passenger* this,char* id);
int passenger_getId(Passenger* this,int* id);

int passenger_setNombre(Passenger* this,char* nombre);
int passenger_getNombre(Passenger* this,char* nombre);

int passenger_setApellido(Passenger* this,char* apellido);
int passenger_getApellido(Passenger* this,char* apellido);

int passenger_setPrecioTxt(Passenger* this,char* precioStr);
int passenger_setPrecio(Passenger* this,float precio);
int passenger_getPrecio(Passenger* this,float* precio);

int passenger_setCodigoVuelo(Passenger* this, char* codigoVueloStr);
int passenger_getCodigoVuelo(Passenger* this, char* codigoVuelo);

int passenger_setTipoPasajeroTxt(Passenger* this, char* tipoPasajeroStr);
int passenger_setTipoPasajero(Passenger* this,int tipoPasajero);
int passenger_getTipoPasajero(Passenger* this, int* tipoPasajero);
int passenger_getTipoPasajeroTxt(Passenger* this, int tipoPasajero, char* tipoPasajeroStr);

int passenger_setEstadoVueloTxt(Passenger* this, char* estadoVueloStr);
int passenger_setEstadoVuelo(Passenger* this, int estadoVuelo);
int passenger_getEstadoVuelo(Passenger* this, int* estadoVuelo);
int passenger_getEstadoVueloTxt(Passenger* this,int estadoVuelo, char* estadoVueloStr);

int passenger_sortByName(void* pElement1, void* pElement2);
int passenger_sortByLastName(void* pElement1, void* pElement2);
int passenger_sortById(void* pElement1, void* pElement2);
int passenger_sortByPrice(void* pElement1, void* pElement2);
int passenger_sortByType(void* pElement1, void* pElement2);
int passenger_sortByFlyCode(void* pElement1, void* pElement2);
int passenger_sortByFlyStatus(void* pElement1, void* pElement2);

//ABM
int passenger_addToList(LinkedList* pArrayListPassenger, int* pIdPassenger);
int passenger_modifyPassenger(Passenger* pPassenger);
int passenger_deleteFromList(LinkedList* pArrayListPassenger, int index);
int passenger_print(LinkedList* pArrayListPassenger, int index);
//Busqueda
Passenger* passenger_getById(LinkedList* pArrayListPassenger, int idToFind);
int passenger_getIndexById(LinkedList* pArrayListPassenger, int idToFind);

#endif /* PASSENGER_H_ */
