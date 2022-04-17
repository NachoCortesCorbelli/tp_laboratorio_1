/*
 * utn.h
 *
 *  Created on: 10 sep. 2021
 *      Author: nacho
 */

#ifndef UTN_H_
#define UTN_H_

int utn_pedirEntero(int* pEntero,char mensaje[],char mensajeError[], int minimo, int maximo, int reintentos);
int utn_pedirFlotante(float* pChar,char mensaje[],char mensajeError[], float minimo, float maximo, int reintentos);

#endif /* UTN_H_ */
