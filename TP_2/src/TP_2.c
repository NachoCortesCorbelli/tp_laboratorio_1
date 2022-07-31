/*
 ============================================================================
 Name        : TP_2.c
 Author      : Cortés Corbelli, Ignacio Martín
 Version     : 1.1
 O.S 		 : Linux
 Copyright   : General Public License v2.0
 Description : TRABAJO PRACTICO 2, Ansi-style
 ============================================================================
 */
#include <stdio_ext.h>
#include <stdlib.h>
#include "utn.h"
#include "ArrayPassenger.h"

int main(void){

	ePassenger arrayPassanger[QTY_PASSANGER];
	int idPassenger = 8;
	int option;


	if(!initPassengers(arrayPassanger, QTY_PASSANGER))
	{
		//HARCODEO DE PASAGEROS
		addPassenger(arrayPassanger, QTY_PASSANGER,
		1, "Nacho", "Cortes", 1500, 3, "123456789", 1);
		addPassenger(arrayPassanger, QTY_PASSANGER,
		2, "Ricardo", "Cobelli", 500, 1, "624456583", 1);
		addPassenger(arrayPassanger, QTY_PASSANGER,
		3, "Jose", "Beltran", 2500, 4, "873446884", 2);
		addPassenger(arrayPassanger, QTY_PASSANGER,
		4, "Filomeno", "Dominguez", 800, 2, "323456753", 3);
		addPassenger(arrayPassanger, QTY_PASSANGER,
		5, "Josue", "Ayala", 4500, 4, "113416181", 3);
		addPassenger(arrayPassanger, QTY_PASSANGER,
		6, "Fermin", "Altamirano", 1500, 3, "222426229", 1);
		addPassenger(arrayPassanger, QTY_PASSANGER,
		7, "Carlos", "Zaracho", 500, 1, "323576246", 1);
		addPassenger(arrayPassanger, QTY_PASSANGER,
		8, "Eustasio", "Alegria", 500, 1, "184446777", 2);
		do
		{
			option = menuPassenger(arrayPassanger, QTY_PASSANGER, &idPassenger);
		}while(option != 6);
	}
	return EXIT_SUCCESS;
}



















