/*
 * Validations.c
 *
 *  Created on: 9 nov. 2021
 *      Author: nacho
 */

#include "Validations.h"
/**
 * \brief Funcion estática que verifica si la cadena recibida es solamente numerica
 * \param pCadena La cadena de caracteres recibida
 * \param longitud El tamaño de la cadena de caracteres recibida
 * \return Devuelve un 1 en caso de ser verdadero y un 0 en caso de falso
 * -1 si no pudo realizar la verificacion
 */
int esNumerica(char* pCadena, int longitud)
{
	int retorno = -1;

	if(pCadena != NULL &&
	   longitud > 0)
	{
		for(int i = 0;i < longitud; i++)
		{
			if( //pCadena[0] == '\0' ||
				pCadena[i] != '\0')
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
 * @brief Funcion estática que verifica que la cadena recibida
 * sea un nombre o apellido
 * @param pCadena la cadena de caracteres recibida
 * @param longitud el tamaño de la cadena
 * @return retorna 1 si es un nombre o apellido, 0 si no lo es y
 * -1 si no pudo realizar la verificacion
 */
int esNombreApellido(char* pCadena, int longitud)
{
	int retorno;
	int contadorEspacios;
	int indexSegundoNombreApellido;

	contadorEspacios = 0;
	retorno = -1;

	if(pCadena != NULL &&
	   longitud > 0)
	{
		for(int i = 0;i < longitud; i++)
		{
			if(pCadena[i] != '\0')
			{

				if(( (i == 0 && (pCadena[i] >= 'A' && pCadena[i] <= 'Z'))||
				     (i == 0 && (pCadena[i] >= 'a' && pCadena[i] <= 'z')) ) ||
			      (( (i > 0 || contadorEspacios == 1) &&(pCadena[i] >= 'a' && pCadena[i] <= 'z')) ||
				   ( (i > 0 || contadorEspacios == 1) &&(pCadena[i] == '-')) ||
				   ( (i == indexSegundoNombreApellido)&&(pCadena[i] >= 'A' &&(pCadena[i] <= 'Z')))||
				   ( (i == indexSegundoNombreApellido)&&(pCadena[i] >= 'a' &&(pCadena[i] <= 'z')))) )
				{
					retorno = 1;
				}
				else if( (i > 1 && pCadena[i] == ' ') &&
						 (contadorEspacios == 0) )
				{
					indexSegundoNombreApellido = i+1;
					contadorEspacios = 1;
					retorno = 1;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}
int esTipoPasajero(char* pCadena, int longitud)
{
	int retorno = -1;
	int retornoCmp;

	retornoCmp = strncmp("EconomyClass",pCadena,longitud);
	if(retornoCmp == 0)
	{
		retorno = 1;
	}
	retornoCmp = strncmp("ExecutiveClass",pCadena,longitud);
	if(retornoCmp == 0)
	{
		retorno = 2;
	}
	retornoCmp = strncmp("FirstClass",pCadena,longitud);
	if(retornoCmp == 0)
	{
		retorno = 3;
	}

	return retorno;
}
int esEstadoVuelo(char* pCadena, int longitud)
{
	int retorno = -1;
	int retornoCmp;

	retornoCmp = strncmp("En Vuelo",pCadena,longitud);
	if(retornoCmp == 0)
	{
		retorno = 1;
	}
	retornoCmp = strncmp("En Horario",pCadena,longitud);
	if(retornoCmp == 0)
	{
		retorno = 2;
	}
	retornoCmp = strncmp("Aterrizado",pCadena,longitud);
	if(retornoCmp == 0)
	{
		retorno = 3;
	}
	retornoCmp = strncmp("Demorado",pCadena,longitud);
	if(retornoCmp == 0)
	{
		retorno = 4;
	}

	return retorno;
}
int esPrecio (char *pCadena, int longitud)
{
	int retorno = 1;
	int flagComa = 0;
	if (pCadena != NULL && longitud > 0)
	{
		for (int i = 0; i < longitud; i++)
		{
		  if(//pCadena[0] == '\0' ||
		     pCadena[i] != '\0')
		  {
			    if((pCadena[i] < '0' || pCadena[i] > '9') &&
				  ((pCadena[i] != '.' && flagComa == 0) ||
			      (pCadena[i] == '.' && flagComa == 1)))
				{
			    	retorno = 0;
				  	break;
				}
				else if (pCadena[i] == '.' && flagComa == 0)
				{
					flagComa = 1;
					continue;
				}
		  }
		  else
		  {
			  break;
		  }
		}
	}
	return retorno;
}



















