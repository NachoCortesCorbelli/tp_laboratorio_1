/*
 * utn.h
 *
 *  Created on: 10 sep. 2021
 *      Author: nacho
 */

#ifndef UTN_H_
#define UTN_H_

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
//#define SIZE_STRING 4096 MEDIO EXAGERADO CREO
#define SIZE_STRING 1024

int utn_pedirEntero(int* pResultado,char mensaje[],char mensajeError[],
					int minimo, int maximo, int reintentos);
int utn_pedirCaracter(char* pResultado,char mensaje[],char mensajeError[],
					  char minimo, char maximo, int reintentos);
int utn_pedirFlotante(float* pResultado,char mensaje[],char mensajeError[],
					  float minimo, float maximo, int reintentos);
int utn_pedirCadena(char* pResultado,int tamano,char mensaje[],
					char mensajeError[], int minimo, int maximo, int reintentos);
int utn_pedirNombreApellido(char* pResultado,int tamano,char mensaje[],
					        char mensajeError[], int minimo, int maximo, int reintentos);
int utn_pedirLocalidad(char* pResultado,int tamano,char mensaje[],
					   char mensajeError[], int minimo, int maximo, int reintentos);
int utn_pedirDireccion(char* pResultado,int tamano,char mensaje[],
					   char mensajeError[], int minimo, int maximo, int reintentos);
int utn_pedirCuit(char* pResult, int limite, char* msg, char* msgError, int retry);

int utn_pedirDescripcion(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);

int utn_pedirDni(char* pResultado, int longitud,char* mensaje, char* mensajeError, int limite, int reintentos);
int utn_menuDeseaSeguir(char* pOpcion,char mensaje[],char mensajeError[], char opcionSeguir, char opcionNoSeguir, int reintentos);



#endif /* UTN_H_ */
