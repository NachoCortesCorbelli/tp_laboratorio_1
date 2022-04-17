/*
 ============================================================================
 Name        : TP_1.c
 Author      : Cortés Corbelli, Ignacio Martín
 Version     : 0.1
 Copyright   : Your copyright notice
 Description : 1. Ingresar Kilómetros: ( km=x)
			   2. Ingresar Precio de Vuelos: (Aerolíneas=y, Latam=z)
			   - Precio vuelo Aerolíneas:
			   - Precio vuelo Latam:
			   3. Calcular todos los costos:
			   a) Tarjeta de débito (descuento 10%)
			   b) Tarjeta de crédito (interés 25%)
			   c) Bitcoin (1BTC -> 4606954.55 Pesos Argentinos)
			   d) Mostrar precio por km (precio unitario)
			   e) Mostrar diferencia de precio ingresada (Latam - Aerolíneas)
			   4. Informar Resultados
			   “Latam:
			   a) Precio con tarjeta de débito: r
			   b) Precio con tarjeta de crédito: r
			   c) Precio pagando con bitcoin : r
			   d) Precio unitario: r
			   Aerolíneas:
			   a) Precio con tarjeta de débito: r
			   b) Precio con tarjeta de crédito: r
			   c) Precio pagando con bitcoin : r
			   d) Precio unitario: r
		       La diferencia de precio es : r “
			   5. Carga forzada de datos
			   6. Salir
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
