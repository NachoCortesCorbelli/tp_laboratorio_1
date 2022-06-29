/*
 ============================================================================
 Name        : TP_1.c
 Author      : Cortés Corbelli, Ignacio Martín
 Version     : 1.1
 Description : Trabajo Practico 1.
 ============================================================================
 */
#include "menuAgencia.h"

int main(void){
	int opcionIngresada;

	do
	{
		opcionIngresada = menu();
	}while(opcionIngresada != 6);
	return 0;
}
