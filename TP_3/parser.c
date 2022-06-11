#include <stdio.h>
#include <stdlib.h>
#include "Passenger.h"

/** \brief Parsea los datos de los empleados desde el archivo data.csv (modo texto).
 * \param path char* la ruta del archivo
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna 0 si pudo parsear -1,-2,-3 error
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	Passenger* pPassenger = NULL;
	char auxId[SIZE_STRING];
	char auxNombre[SIZE_STRING];
	char auxApellido[SIZE_STRING];
	char auxPrecio[SIZE_STRING];
	char auxCodigoVuelo[SIZE_STRING];
	char auxTipoPasajero[SIZE_STRING];
	char auxEstadoVuelo[SIZE_STRING];
	int retorno = -1;
	int flag = 0;
	if(pFile != NULL && pArrayListPassenger != NULL)
	{
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
					  auxId,auxNombre,auxApellido,auxPrecio,auxCodigoVuelo,
					  auxTipoPasajero,auxEstadoVuelo)==7)
			{
				if(flag == 1)
				{
					pPassenger = passenger_newParametrosStr( auxId, auxNombre,
															 auxApellido, auxPrecio,
															 auxCodigoVuelo,auxTipoPasajero,
															 auxEstadoVuelo);
					if(pPassenger != NULL)
					{
						if(!ll_add(pArrayListPassenger, pPassenger))
						{
							retorno = 0;
						}
					}
					else
					{
						retorno = -3;
					}
				}
				else if(flag == 0)
				{
					flag = 1;
					continue;
				}
			}
			else
			{
				retorno = -2;
			}
		}while(!feof(pFile));
	}
    return retorno;
}
/** \brief Parsea el ultimo id de los empleados desde el archivo lastId.csv.
 * \param path char* la ruta del archivo
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna el id si pudo parsear, -1 error
 */
int parser_PassengerLastIdFromText(FILE* pFileId)
{
	int retorno = -1;
	char auxId[SIZE_STRING];
	int id;

	if(pFileId != NULL)
	{
		do
		{
			if(fscanf(pFileId,"%s",auxId)==1)
			{
				id = atoi(auxId);
				if(id >= 0)
				{
					retorno = id;
				}
			}
		}while(!feof(pFileId));
	}
	return retorno;
}
/** \brief Parsea los datos los datos de los empleados desde el archivo data.bin(modo binario).
 * \param path char* la ruta del archivo
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna 0 si pudo parsear -1 error
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger)
{
	Passenger* pAuxPassenger = NULL;
	Passenger* pPassenger = NULL;
	int retorno = -1;
	if(pFile != NULL && pArrayListPassenger != NULL)
	{
		do
		{
			pAuxPassenger = passenger_new();
			if(pAuxPassenger != NULL)
			{
				if(fread(pAuxPassenger,sizeof(Passenger),1,pFile)== 1)
				{
					pPassenger = passenger_newParametros(pAuxPassenger->id, pAuxPassenger->nombre,
														 pAuxPassenger->apellido,pAuxPassenger->precio,
														 pAuxPassenger->codigoVuelo,pAuxPassenger->tipoPasajero,
														 pAuxPassenger->estadoVuelo);
					if( pPassenger != NULL &&
						!ll_add(pArrayListPassenger, pPassenger))
					{
						//DEBERÍA USAR FUNCION QUE ESTE EN LA LLIST NO?
						passenger_delete(pAuxPassenger);
						retorno = 0;
					}
				}
			}
		}while(!feof(pFile));
	}
    return retorno;
}
int parser_lastIdFromCsv(FILE* pFile,char* pLastId)
{
	char auxId[SIZE_STRING];
	char auxNombre[SIZE_STRING];
	char auxApellido[SIZE_STRING];
	char auxPrecio[SIZE_STRING];
	char auxCodigoVuelo[SIZE_STRING];
	char auxTipoPasajero[SIZE_STRING];
	char auxEstadoVuelo[SIZE_STRING];
	int retorno = -1;
	int flag = 0;
	if(pFile != NULL)
	{
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
					  auxId,auxNombre,auxApellido,auxPrecio,auxCodigoVuelo,
					  auxTipoPasajero,auxEstadoVuelo)==7)
			{
				if(flag == 1)
				{
					retorno = 0;
				}
				if(flag == 0)
				{
					flag = 1;
					continue;
				}
			}
		}while(!feof(pFile));
		if(retorno == 0)
		{
			strncpy(pLastId,auxId,SIZE_STRING);
//			printf("\nID: %s\n",pLastId);
		}
	}
    return retorno;
}
