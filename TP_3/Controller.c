#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "parser.h"
#include "Passenger.h"
#include "Validations.h"


/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char* la ruta del archivo
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna 0 si pudo parsear -1 error
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	int retornoParser;
	FILE* pFile;
	if(pArrayListPassenger != NULL && path != NULL)
	{

		pFile = fopen(path,"r");
		if(pFile != NULL)
		{
			retornoParser = parser_PassengerFromText(pFile, pArrayListPassenger);
			if(retornoParser == 0)
			{
				retorno = 0;
			}
			fclose(pFile);
		}
	}
    return retorno;
}
/**
 * \brief Retorna el ultimo id
 * \param path la ruta del archivo
 * \param pLastId
 * \return retorna 0 si pudo parsear -1 error
 */
int controller_loadFromLastId(char* path,int* pLastId)
{
	FILE* pFileId;
	int retornoParser;
	int retorno = -1;

	if(path != NULL && pLastId != NULL)
	{

		pFileId = fopen(path,"r");
		if(pFileId != NULL)
		{
			retornoParser = parser_PassengerLastIdFromText(pFileId);
			if(retornoParser > -1)
			{
				*pLastId = retornoParser;
				retorno = 0;
			}
			fclose(pFileId);
		}

	}
	return retorno;
}
/**
 * \brief crea el archivo lastId.txt
 * \param path la ruta del archivo
 * \return retorna 0 si pudo parsear -1 error
 */
int controller_createLastIdTxt(char* path)
{
	FILE* pFileId;
	int retorno = -1;

	if(path != NULL)
	{
		//LEVANTAR EL DATA CSV Y TOMAR EL ULTIMO ID
		pFileId = fopen(path,"w");
		if(pFileId != NULL)
		{
			fprintf(pFileId,"1000");
			retorno = 0;
		}
		fclose(pFileId);
	}
	return retorno;
}
/**
 * \brief crea el archivo lastId.txt
 * \param path la ruta del archivo
 * \return retorna 0 si pudo parsear -1 error
 */
int controller_createLastIdTxt2(char* pathNew,char* pathCsv)
{
	FILE* pFileCsv;
	FILE* pFileId;
	int retorno = -1;
	char idString[SIZE_STRING];

	pFileCsv = fopen(pathCsv,"r");
	if(pFileCsv != NULL)
	{
		printf("\n1\n");
		if(parser_lastIdFromCsv(pFileCsv, idString)==0)
		{
			printf("\n2\n");
			pFileId = fopen(pathNew,"w");
			if(pFileId != NULL)
			{
				printf("\n3\n");
				fprintf(pFileId,"%s",idString);
				retorno = 0;
			}
			fclose(pFileId);
		}
		printf("\n4\n");
	}
	fclose(pFileCsv);
	return retorno;
}
/**
 * \brief actualiza el el valor del ultimo id utilizado
 * \param path la ruta del archivo
 * \param pLastId
 * \return retorna 0 si pudo parsear -1 error
 */
int controller_refreshLastId(char* path,int* pLastId)
{
	FILE* pFileId;
	int retorno = -1;
	char lastId[SIZE_STRING];
	if(path != NULL && pLastId != NULL && *pLastId > -1)
	{
	    snprintf(lastId,SIZE_STRING,"%d",*pLastId);
		pFileId = fopen(path,"w");
		if(pFileId != NULL)
		{
			fprintf(pFileId,"%s",lastId);
			retorno = 0;
		}
		fclose(pFileId);
	}
	return retorno;
}
/** \brief Carga los datos de los pasajeros desde el archivo data.bin (modo binario).
 *
 * \param path char* la ruta del archivo
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna 0 si pudo parsear -1 error
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger)
{
	int retorno;
	int retornoParser;
	FILE* pFile;

	retorno = -1;

	if(pArrayListPassenger != NULL && path != NULL)
	{
		pFile = fopen(path,"r");
		if(pFile != NULL)
		{
			retornoParser = parser_PassengerFromBinary(pFile, pArrayListPassenger);
			if(retornoParser == 0)
			{
				retorno = 0;
			}
			fclose(pFile);
		}
	}
    return retorno;
}

/** \brief Alta de pasajeros
 * \param path char* la ruta del archivo
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna 0 si pudo parsear -1 error
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger)
{
	int lastId;
	int retorno = -1;
	if(pArrayListPassenger != NULL)
	{

		if(controller_loadFromLastId("lastId.csv", &lastId)==0)
		{
			lastId++;
			if(passenger_addToList(pArrayListPassenger, &lastId)==0 &&
			   controller_refreshLastId("lastId.csv", &lastId)==0)
			{
				retorno = 0;
			}
		}
	}
    return retorno;
}

/** \brief Modificar datos de empleado
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna 0 si fue exitoso -1 error
 */
int controller_editPassenger(LinkedList* pArrayListPassenger)
{
	//USAR LL_SET Y LL_GETINDEXOF??
	Passenger* pPassenger = NULL;
	int retorno = -1;
	int idToFind;
	if(pArrayListPassenger != NULL)
	{
		if(!utn_pedirEntero(&idToFind, "\nINGRESE EL ID DEL PASAJERO A MODIFICAR: \n", "\nERROR\n", 0, 2147483647, 5))
		{
			pPassenger = (Passenger*)passenger_getById(pArrayListPassenger, idToFind);
			if(pPassenger != NULL)
			{
				if( passenger_modifyPassenger(pPassenger)==0 )
				{
					retorno = 0;
				}
			}
		}
	}
    return retorno;

}

/** \brief Baja de empleado
 *
 * \param path char* la ruta del archivo
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna 0 si pudo parsear -1 error
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger)
{
	Passenger* pPassenger = NULL;
	int retorno = -1;
	int idToFind;
	int index;
	if(pArrayListPassenger != NULL)
	{
		if(utn_pedirEntero(&idToFind, "\nINGRESE EL ID DEL EMPLEADO A BORRAR: \n", "\nERROR\n", 0, 1000000, 5)==0)
		{
			pPassenger = passenger_getById(pArrayListPassenger, idToFind);
			if(pPassenger != NULL)
			{
				index = ll_indexOf(pArrayListPassenger, pPassenger);
				if(passenger_deleteFromList(pArrayListPassenger, index)==0)
				{
					retorno = 0;
				}
			}
		}
	}
    return retorno;
}

/** \brief Listar pasajeros
 *
 * \param path char* la ruta del archivo
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna 0 si pudo parsear -1 error
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	int length;
	if(pArrayListPassenger !=NULL)
	{
		length = ll_len(pArrayListPassenger);
		if(length > 0)
		{
			for(int i = 0; i < length; i++)
			{
				if(!passenger_print(pArrayListPassenger, i) )
				{
					printf("\n");
				}
			}
			retorno = 0;
		}
	}
    return retorno;
}
/** \brief Ordenar pasajeros
 *
 * \param path char* la ruta del archivo
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna 0 si pudo parsear -1 error
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger)
{
	int order;
	int option;
	int retorno = -1;

	if(pArrayListPassenger != NULL)
	{
		if(!utn_pedirEntero(&option,
						   "\nQUE TIPO DE ORDENAMIENTO QUIERE REALIZAR"
						   "\n1-POR ID"
						   "\n2-POR NOMBRE"
						   "\n3-APELLIDO"
						   "\n4-PRECIO"
						   "\n5-CODIGO DE VUELO"
						   "\n6-CLASE DE PASAJERO"
						   "\n7-ESTADO DEL VIAJE"
						   "\n8-SALIR"
						   "\nOPCION: ",
						   "\nERROR\n",
						   1, 8, 5) &&
		   !utn_pedirEntero(&order,
				   	   	   "\nEN QUE ORDEN DESEA LA LISTA?"
						   "\n1-ASCENDENTE"
						   "\n0-DESCENDENTE\nOPCION: ",
						   "\nERROR\nREINGRESE NUEVAMENTE: ",
						   0, 1, 5))
		{
			switch(option)
			{
			case 1:
				if(!ll_sort(pArrayListPassenger, passenger_sortById, order))
				{
					retorno = 0;
				}
				break;
			case 2:
				if(!ll_sort(pArrayListPassenger, passenger_sortByName, order))
				{
					retorno = 0;
				}
				break;
			case 3:
				if(!ll_sort(pArrayListPassenger, passenger_sortByLastName, order))
				{
					retorno = 0;
				}
				break;
			case 4:
				if(!ll_sort(pArrayListPassenger, passenger_sortByPrice, order))
				{
					retorno = 0;
				}
				break;
			case 5:
				if(!ll_sort(pArrayListPassenger, passenger_sortByFlyCode, order))
				{
					retorno = 0;
				}
				break;
			case 6:
				if(!ll_sort(pArrayListPassenger, passenger_sortByType, order))
				{
					retorno = 0;
				}
				break;
			case 7:
				if(!ll_sort(pArrayListPassenger, passenger_sortByFlyStatus, order))
				{
					retorno = 0;
				}
				break;
			case 8:
				break;
			}
		}
	}
    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char* la ruta del archivo
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna 0 si pudo parsear -1 error
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	int length;
	FILE* pFile;
	Passenger* auxPassenger = NULL;

	if(pArrayListPassenger != NULL && path != NULL && ll_len(pArrayListPassenger) > 0)
	{
		length = ll_len(pArrayListPassenger);
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			fprintf(pFile, "id,name,lastname,price,flycode,typePassenger,statusFlight\n");
			for(int i = 0; i < length; i++)
			{
				auxPassenger = (Passenger*)ll_get(pArrayListPassenger, i);
				if(auxPassenger != NULL)
				{
					fprintf(pFile,"%d,%s,%s,%.2f,%s,%d,%d\n",
						    auxPassenger->id,
						    auxPassenger->nombre,
						    auxPassenger->apellido,
						    auxPassenger->precio,
						    auxPassenger->codigoVuelo,
						    auxPassenger->tipoPasajero,
  						    auxPassenger->estadoVuelo);
				}
			}
			retorno = 0;
			fclose(pFile);
		}
	}
    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char* la ruta del archivo
 * \param pArrayListPassenger LinkedList* la linked list
 * \return int retorna 0 si pudo parsear -1 error
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	int length;
	FILE* pFile;
	Passenger* auxPassenger = NULL;

	if(pArrayListPassenger != NULL && path != NULL && ll_len(pArrayListPassenger) > 0)
	{
		length = ll_len(pArrayListPassenger);
		pFile = fopen(path,"wb");
		if(pFile != NULL)
		{
			for(int i = 0; i < length; i++)
			{
				auxPassenger = (Passenger*)ll_get(pArrayListPassenger, i);
				if(auxPassenger != NULL)
				{
					fwrite(auxPassenger,sizeof(Passenger),1,pFile);
				}
			}
			retorno = 0;
			fclose(pFile);
		}
	}
    return retorno;

}
int controller_accessFileByName(char* path)
{
	int retorno = -1;
	char auxFileName[SIZE_STRING];
	FILE* pFile;
	//PODRIA HACER UN UTN_PEDIR ARCHIVO QUE VALIDE EL FORMATO (.TXT, .CSV, .BIN)
	if(!utn_pedirCadena(auxFileName, SIZE_STRING,
						"\nINGRESE EL NOMBRE DEL ARCHIVO: ",
						"\nERROR\nREINGRESE NUEVAMENTE\n",
						3, SIZE_STRING, 5))
	{
		pFile = fopen(auxFileName,"r");
		if(pFile != NULL)
		{
			strncpy(path,auxFileName,SIZE_STRING);
			retorno = 0;
			fclose(pFile);
		}
	}
	return retorno;
}
