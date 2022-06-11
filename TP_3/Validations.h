/*
 * Validations.h
 *
 *  Created on: 9 nov. 2021
 *      Author: nacho
 */

#ifndef VALIDATIONS_H_
#define VALIDATIONS_H_

#include <stdio.h>
#include <string.h>

int esNumerica(char* pCadena, int longitud);
int esNombreApellido(char* pCadena, int longitud);
int esPrecio(char* pCadena, int longitud);
int esTipoPasajero(char* pCadena, int longitud);
int esEstadoVuelo(char* pCadena, int longitud);

#endif /* VALIDATIONS_H_ */
