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

#define SIZE_STRING 1024

int utn_pedirEntero(int* pEntero,char mensaje[],char mensajeError[],
					int minimo, int maximo, int reintentos);
int utn_pedirCaracter(char* pChar,char mensaje[],char mensajeError[],
					  char minimo, char maximo, int reintentos);
int utn_pedirFlotante(float* pChar,char mensaje[],char mensajeError[],
					  float minimo, float maximo, int reintentos);
int utn_pedirCadena(char* pCadena,int tamano,char mensaje[],
					char mensajeError[], int minimo, int maximo, int reintentos);
int utn_pedirNombreApellido(char* pNombre,int tamano,char mensaje[],
					        char mensajeError[], int minimo, int maximo, int reintentos);
int utn_pedirLocalidad(char* pLocalidad,int tamano,char mensaje[],
					   char mensajeError[], int minimo, int maximo, int reintentos);
int utn_pedirDireccion(char* pDireccion,int tamano,char mensaje[],
					   char mensajeError[], int minimo, int maximo, int reintentos);
int utn_pedirCuit(char* pResult, int limite, char* msg, char* msgError, int retry);
int utn_menuOpciones(int* pOpcion,char mensaje[],
					 char mensajeError[], int opcionMinima, int opcionMaxima, int reintentos);

#endif /* UTN_H_ */
