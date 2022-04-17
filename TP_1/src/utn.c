/*
 * utn.c
 *
 *  Created on: 10 sep. 2021
 *      Author: nacho
 */
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

#define SIZE_STRING 1024

static int obtengoCadena(char pCadena[], int longitud);
static int obtengoEntero(int *pEntero);
static int obtengoFloat(float* pFloat);
static int esNumerica(char pCadena[], int longitud);
static int esFlotante(char pCadena[], int longitud);

/**
 * \brief Funcion que verifica si la cadena recibida es solamente numerica
 * \param pCadena La cadena de caracteres recibida
 * \param longitud El tamaño de la cadena de caracteres recibida
 * \return Devuelve un 1 en caso de ser verdadero y un 0 en caso de falso
 */
static int esNumerica(char pCadena[], int longitud)
{
	int retorno;

	retorno = -1;

	if(pCadena != NULL &&
	   longitud > 0)
	{
		for(int i = 0;i < longitud; i++)
		{
			if(pCadena[i] != '\0')
			{
				if( (pCadena[i] < '0' || pCadena[i] > '9') &&
					(pCadena[i] != '-') )
				{
					retorno = 0;
					break;
				}
			}
			else
			{
				retorno = 1;
				break;
			}

		}
	}

	return retorno;
}
/**
 * @brief Valida si el la cadena recibida está tomada como un float
 * @param pCadena La cadena de caracteres recibida
 * @param longitud El tamaño de la cadena de caracteres recibida
 * @return Devuelve un 1 en caso de ser verdadero y un 0 en caso de falso
 */
static int esFlotante(char pCadena[], int longitud)
{
	int retorno;
	int flagFlotante;

	flagFlotante = 0;
	retorno = -1;

	if(pCadena != NULL &&
	   longitud > 0)
	{
		for(int i = 0;i < longitud; i++)
		{
			if(pCadena[i] != '\0')
			{
				if(pCadena[i] == '.' &&
				   flagFlotante == 0)
				{
					flagFlotante = 1;
				}
				else if(( (pCadena[i] < '0' || pCadena[i] > '9') &&
					(pCadena[i] != '-') ) ||
					(pCadena[i] == '.' &&
				    flagFlotante == 1))
				{
					retorno = 0;
					break;
				}

			}
			else
			{
				retorno = 1;
				break;
			}

		}
	}
	return retorno;

}

/**
 * \brief Funcion que obtiene la cadena de caracteres y en caso de que no tenga problemas
 * \brief la devuelve por referencia
 * \param pCadena La cadena de caracteres recibida
 * \param longitud El tamaño de la cadena de caracteres recibida
 * \return Devuelve 0 en caso de no tener problemas o -1 si no pudo
 */
static int obtengoCadena(char pCadena[],int longitud)
{

	int retorno;
	char bufferString[SIZE_STRING];

	if(pCadena != NULL &&
	   longitud > 0 &&
	   fgets(bufferString,SIZE_STRING,stdin)!= NULL)
	{
		__fpurge(stdin);
		strncpy(pCadena,bufferString,SIZE_STRING);
		if(pCadena[strlen(pCadena)-1] == '\n')
		{
			pCadena[strlen(pCadena)-1] = '\0';
		}
		retorno = 0;
	}
	else
	{
		retorno = -1;
	}

	return retorno;
}
/**
 * \brief Verifica que la cadena sea numérica
 * \param pBufferInt La cadena recibida
 * \return Devuelve 0 en caso de no tener problemas y -1 de no poder
 */
static int obtengoEntero(int* pInt)
{

	int retorno;
	int auxInt;
	char bufferString[SIZE_STRING];

	retorno = -1;

	if(pInt != NULL &&
	   obtengoCadena(bufferString,SIZE_STRING) == 0 &&
	   esNumerica(bufferString, SIZE_STRING) == 1)
	{
		auxInt= atoi(bufferString);
		*pInt = auxInt;
		retorno = 0;
	}

	return retorno;

}
/**
 * @brief Verifica que la cadena sea flotante
 * @param pFloat La cadena recibida
 * @return Devuelve 0 en caso de no tener problemas y -1 de no poder
 */
static int obtengoFloat(float* pFloat)
{

	int retorno;
	float auxFloat;
	char bufferString[SIZE_STRING];

	retorno = -1;

	if(pFloat != NULL &&
	   obtengoCadena(bufferString,SIZE_STRING) == 0 &&
	   esFlotante(bufferString, SIZE_STRING) == 1)
	{
		auxFloat= atof(bufferString);
		*pFloat = auxFloat;
		retorno = 0;
	}

	return retorno;

}

/**
 * @brief Le pide un entero al usuario
 * @param pEntero Devuelve el resultado por referencia
 * @param mensaje El mensaje a ser mostrado
 * @param mensajeError El mensaje de error a ser mostrado
 * @param minimo El numero minimo
 * @param maximo El numero maximo
 * @param reintentos La cantidad de reintentos
 * @return Devuelve 0 en caso de no tener problemas y -1 de no poder
 */
int utn_pedirEntero(int* pEntero,char mensaje[],char mensajeError[], int minimo, int maximo, int reintentos)
{

	int retorno;
	int bufferInt;

	retorno = -1;

	if(pEntero != NULL &&
	   mensaje != NULL &&
	   mensajeError != NULL &&
	   minimo <= maximo &&
	   reintentos >= 0)
	{

		do
		{
			printf("%s",mensaje);
			if(obtengoEntero(&bufferInt)==0 &&
			   bufferInt >= minimo &&
			   bufferInt <= maximo)
			{
				*pEntero = bufferInt;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos > 0);
	}

	return retorno;

}
/**
 * @brief Le pide un numero flotante al usuario
 * @param pFloat Devuelve el resultado por referencia
 * @param mensaje El mensaje a ser mostrado
 * @param mensajeError El mensaje de error a ser mostrado
 * @param minimo El numero minimo
 * @param maximo El numero maximo
 * @param reintentos La cantidad de reintentos
 * @return Devuelve 0 en caso de no tener problemas y -1 de no poder
 */
int utn_pedirFlotante(float* pFloat,char mensaje[],char mensajeError[], float minimo, float maximo, int reintentos)
{
	int retorno;
	float bufferFloat;

	retorno = -1;

	if(pFloat != NULL &&
	   mensaje != NULL &&
	   mensajeError != NULL &&
	   minimo <= maximo &&
	   reintentos >= 0)
	{

		do
		{
			printf("%s",mensaje);
			if(obtengoFloat(&bufferFloat)==0 &&
			   bufferFloat >= minimo &&
			   bufferFloat <= maximo)
			{
				*pFloat = bufferFloat;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos > 0);
	}

	return retorno;

}
