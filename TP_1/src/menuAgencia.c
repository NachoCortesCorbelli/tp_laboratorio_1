/*
 * menuAgencia.c
 *
 *  Created on: 16 abr. 2022
 *      Author: nacho
 */
#include <stdio_ext.h>
#include <stdlib.h>
#include "utn.h"
#include "menuAgencia.h"
#include "calculos.h"



/**
 * \brief Pide los precios de los vuelos
 * \param pAerolineas puntero a aerolineas
 * \param pLatam puntero a latam
 * \return retorna 0 en caso de OK y -1 de ERROR
 */
int menu_pedirPreciosVuelos(float* pAerolineas, float* pLatam)
{
	int retorno = -1;
	float auxAerolineas;
	float auxLatam;
	if(pAerolineas != NULL && pLatam)
	{
		if(!utn_pedirFlotante(&auxAerolineas,
							  "\nINGRESE EL PRECIO DE AEROLINEAS: ",
							  "\nERROR\nINGRESE UN VALOR VALIDO\n", 100, 500000, 15) &&
		   !utn_pedirFlotante(&auxLatam,
							  "\nINGRESE EL PRECIO DE LATAM: ",
							  "\nERROR\nINGRESE UN VALOR VALIDO\n", 100, 500000, 15))
		{
			*pAerolineas = auxAerolineas;
			*pLatam = auxLatam;
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Pide los kilometros
 * \param pKilometros puntero a kilometros
 * \return retorna 0 en caso de OK y -1 de ERROR
 */
int menu_pedirKilometros(float* pKilometros)
{
	int retorno = -1;
	float auxKilometros;
	if(pKilometros != NULL)
	{
		if(!utn_pedirFlotante(&auxKilometros,
							  "\nINGRESE LOS KILOMETROS: ",
							  "\nERROR\nINGRESE UN VALOR VALIDO\n", 2.7, 50000, 15))
		{
			*pKilometros = auxKilometros;
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Realiza el alta forazda de datos traidos por parametro y los muestra
 * \param aerolineas el precio de aerolineas
 * \param latam el precio de latam
 * \param kilometros los kilometros
 * \return retorna 0 en caso de OK, -1 de ERROR
 */
int menu_cargaForzadaDatos(float aerolineas, float latam, float kilometros)
{
	float precioConDebitoAero;
	float precioConDebitoLatam;
	float precioConCreditoAero;
	float precioConCreditoLatam;
	float precioEnBitcoinsAero;
	float precioEnBitcoinsLatam;
	float precioUnitarioAero;
	float precioUnitarioLatam;
	float diferenciaDePrecio;
	int retorno = -1;

	precioConDebitoAero = calculos_debito(aerolineas);
	precioConDebitoLatam = calculos_debito(latam);
	precioConCreditoAero = calculos_credito(aerolineas);
	precioConCreditoLatam = calculos_credito(latam);
	precioEnBitcoinsAero = calculos_bitcoin(aerolineas);
	precioEnBitcoinsLatam = calculos_bitcoin(latam);
	precioUnitarioAero = calculos_precioUnitario(aerolineas, kilometros);
	precioUnitarioLatam = calculos_precioUnitario(latam, kilometros);
	diferenciaDePrecio = calculos_diferenciaPrecio(aerolineas, latam);
	if(precioConDebitoAero != -1 &&
	   precioConDebitoLatam != -1 &&
	   precioConCreditoAero != -1 &&
	   precioConCreditoLatam != -1 &&
	   precioEnBitcoinsAero != -1 &&
	   precioEnBitcoinsLatam != -1 &&
	   precioUnitarioAero != -1 &&
	   precioUnitarioLatam != -1 &&
	   diferenciaDePrecio != -1)
	{
		printf("\nKMs ingresados: %.2f", kilometros);
		printf("\n\nPrecio Aerolineas: $%.2f", aerolineas);
		printf("\na) Precio con tarjeta de debito: $%.2f", precioConDebitoAero);
		printf("\nb) Precio con tarjeta de credito: $%.2f", precioConCreditoAero);
		printf("\nc) Precio pagando con Bitcoin: %f BTC", precioEnBitcoinsAero);
		printf("\nd) Mostrar precio unitario: $%.2f", precioUnitarioAero);
		printf("\n\nPrecio Latam: $%.2f\n", latam);
		printf("\na) Precio con tarjeta de debito: $%.2f", precioConDebitoLatam);
		printf("\nb) Precio con tarjeta de credito: $%.2f", precioConCreditoLatam);
		printf("\nc) Precio pagando con Bitcoin: %f BTC", precioEnBitcoinsLatam);
		printf("\nd) Mostrar precio unitario: $%.2f", precioUnitarioLatam);
		printf("\n\nLa diferencia de precio es: $%.2f\n", diferenciaDePrecio);
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief El menu de la agencia
 * \return retorna la opcion del menu en caso de OK y -1 de error
 */
int menu()
{
	int opcion;
	float kilometros;
	float aerolineas;
	float latam;
	char buffer[1024];
	char sKilometros[50] = "x";
	char sAerolineas[50] = "y";
	char sLatam[50] = "z";
	float precioConDebitoAero;
	float precioConDebitoLatam;
	float precioConCreditoAero;
	float precioConCreditoLatam;
	float precioEnBitcoinsAero;
	float precioEnBitcoinsLatam;
	float precioUnitarioAero;
	float precioUnitarioLatam;
	float diferenciaDePrecio;
	int flagKilometros = 0;
	int flagPrecios = 0;
	int flagCalculos = 0;

	do
	{
		sprintf(buffer,
			   "\n1. Ingresar Kilómetros:(km=%s)"
			   "\n2. Ingresar Precio de Vuelos: (Aerolíneas=%s, Latam=%s)"
			   "\n   - Precio vuelo Aerolíneas:"
			   "\n   - Precio vuelo Latam:"
			   "\n3. Calcular todos los costos:"
			   "\n a) Tarjeta de débito (descuento 10)"
			   "\n b) Tarjeta de crédito (interés 25)"
			   "\n c) Bitcoin (1BTC -> 4606954.55 Pesos Argentinos)"
			   "\n d) Mostrar precio por km (precio unitario)"
			   "\n e) Mostrar diferencia de precio ingresada (Latam - Aerolíneas)"
			   "\n4.Informar Resultados"
			   "\nLatam:"
			   "\n a) Precio con tarjeta de débito: r"
			   "\n b) Precio con tarjeta de crédito: r"
			   "\n c) Precio pagando con bitcoin : r"
			   "\n d) Precio unitario: r"
			   "\nAerolíneas:"
			   "\n a) Precio con tarjeta de débito: r"
			   "\n b) Precio con tarjeta de crédito: r"
			   "\n c) Precio pagando con bitcoin : r"
			   "\n d) Precio unitario: r"
			   "\n La diferencia de precio es : r “"
			   "\n5. Carga forzada de datos"
			   "\n6. Salir ",sKilometros,sAerolineas,sLatam);
		printf("%s",buffer);
		if(!utn_pedirEntero(&opcion, "\nOPCION: ",
							"\nERROR\nVUELVA A INGRESAR LA OPCION"
							,1,6,15))
		{
			switch(opcion)
			{
				case 1:
					if(!menu_pedirKilometros(&kilometros))
					{
						gcvt(kilometros,10,sKilometros);
						flagKilometros = 1;
						printf("\nOK");
					}
					break;
				case 2:
					if(!menu_pedirPreciosVuelos(&aerolineas, &latam))
					{
						gcvt(aerolineas,10,sAerolineas);
						gcvt(latam,10,sLatam);
						flagPrecios = 1;
						printf("\nOK");
					}
					break;
				case 3:
					if(flagKilometros == 1)
					{
						if(flagPrecios == 1)
						{
							precioConDebitoAero = calculos_debito(aerolineas);
							precioConDebitoLatam = calculos_debito(latam);
							precioConCreditoAero = calculos_credito(aerolineas);
							precioConCreditoLatam = calculos_credito(latam);
							precioEnBitcoinsAero = calculos_bitcoin(aerolineas);
							precioEnBitcoinsLatam = calculos_bitcoin(latam);
							precioUnitarioAero = calculos_precioUnitario(aerolineas, kilometros);
							precioUnitarioLatam = calculos_precioUnitario(latam, kilometros);
							diferenciaDePrecio = calculos_diferenciaPrecio(aerolineas, latam);
							if(precioConDebitoAero != -1 &&
							   precioConDebitoLatam != -1 &&
							   precioConCreditoAero != -1 &&
							   precioConCreditoLatam != -1 &&
							   precioEnBitcoinsAero != -1 &&
							   precioEnBitcoinsLatam != -1 &&
							   precioUnitarioAero != -1 &&
							   precioUnitarioLatam != -1 &&
							   diferenciaDePrecio != -1)
							{
								flagCalculos = 1;
								printf("\nCALCULOS REALIZADOS\n");
							}
						}
						else
						{
							printf("\nNO INGRESO LOS PRECIOS\n");
						}
					}
					else
					{
						printf("\nNO INGRESO LOS KILOMETROS\n");
					}
					break;
				case 4:
					if(flagCalculos == 1)
					{
						printf("\nKMs ingresados: %.2f", kilometros);
						printf("\n\nPrecio Aerolineas: $%.2f", aerolineas);
						printf("\na) Precio con tarjeta de debito: $%.2f", precioConDebitoAero);
						printf("\nb) Precio con tarjeta de credito: $%.2f", precioConCreditoAero);
						printf("\nc) Precio pagando con Bitcoin: %f BTC", precioEnBitcoinsAero);
						printf("\nd) Mostrar precio unitario: $%.2f", precioUnitarioAero);
						printf("\n\nPrecio Latam: $%.2f", latam);
						printf("\na) Precio con tarjeta de debito: $%.2f", precioConDebitoLatam);
						printf("\nb) Precio con tarjeta de credito: $%.2f", precioConCreditoLatam);
						printf("\nc) Precio pagando con Bitcoin: %f BTC", precioEnBitcoinsLatam);
						printf("\nd) Mostrar precio unitario: $%.2f", precioUnitarioLatam);
						printf("\n\nLa diferencia de precio es: $%.2f\n", diferenciaDePrecio);
						flagKilometros = 0;
						flagPrecios = 0;
					}
					else
					{
						printf("\nNO REALIZO LOS CALCULOS PRIMERO\n");
					}
					break;
				case 5:
					if(!menu_cargaForzadaDatos(162965,159339,7090))
					{
						printf("\nMOSTRADOS\n");
					}
					break;
				case 6:
					break;
			}
		}
	}while(opcion != 6);
	return opcion;
}


