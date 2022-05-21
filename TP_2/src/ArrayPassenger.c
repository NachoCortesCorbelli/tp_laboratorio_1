/*
 * ArrayPassenger.c
 *
 *  Created on: 13 may. 2022
 *      Author: nacho
 */
#include <stdio_ext.h>
#include <stdlib.h>
#include "utn.h"
#include "ArrayPassenger.h"

/**\brief To indicate that all position in the array are empty,
* \brief  this function put the flag (isEmpty) in TRUE in all
* \brief  position of the array
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initPassengers(ePassenger* list, int len)
{
	int result = -1;
	if(list != NULL && len > 0)
	{
		for(int i = 0; i<len; i++)
		{
			list[i].isEmpty = TRUE;
		}
		result = 0;
	}
	return result;
}
/**
 * \brief Verifica si el array de pasageros esta vacio
 * \param list Passenger* Pointer to array of passenger
 * \param len Array length
 * \return int Retorna 1 en caso de verdadero y 0 de falso
 */
int isArrayPassengerEmpty(ePassenger* list, int len)
{
	int result = 1;
	if(list != NULL && len > 0)
	{
		for(int i = 0; i<len; i++)
		{
			if(list[i].isEmpty == TRUE)
			{
				result = 0;
			}
		}
	}
	return result;
}
/**
 * \brief Busca una posicion vacia en el array de pasageros
 * \param list Passenger* Pointer to array of passenger
 * \param len Array length
 * \return retorna en inice en caso OK o -1 de error
 */
int findEmptyPassenger(ePassenger* list, int len)
{
	int index = -1;
	if(list != NULL && len > 0)
	{
		for(int i = 0; i< len; i++)
		{
			if(list[i].isEmpty == TRUE)
			{
				index = i;
				break;
			}
		}
	}
	return index;
}
/** \brief add in a existing list of passengers the values received as parameters
* \brief  in the first empty position
* \param list passenger* Pointer to array of passenger
* \param len int Array length
* \param id int el id del pasagero
* \param name[] char puntero al array de nombre
* \param lastName[] char puntero al array de apellido
* \param price float el precio
* \param typePassenger int el tipo de pasagero
* \param flycode[] char el codigo de vuelo
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
*/
int addPassenger(ePassenger* list, int len, int id, char name[],char
			     lastName[],float price,int typePassenger, char flycode[],
				 int statusFlight)
{
	int retorno = -1;
	int index;
	if(list != NULL && len > 0 && id >= 0 &&
	   lastName != NULL && name != NULL &&
	   flycode != NULL && price > 0 && flycode > 0)
	{
		index = findEmptyPassenger(list, len);
		if(index != -1)
		{
			list[index].id = id;//(*list).id = id; -> ARIRTMETICA DE PUNTEROS
			strncpy(list[index].name,name,51);
			strncpy(list[index].lastName,lastName,51);
			strncpy(list[index].flycode,flycode,10);
			list[index].price = price;
			list[index].typePassenger = typePassenger;
			list[index].statusFlight = statusFlight;
			list[index].isEmpty = FALSE;
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief find a Passenger by Id en returns the index position in array.
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \param id int el id del pasagero
* \return Return passenger index position or (-1) if [Invalid length or
NULLpointer received or passenger not found]
*/
int findPassengerById(ePassenger* list, int len,int id)
{
	int index = -1;
	if(list != NULL && len > 0 && id > 0)
	{
		for(int i = 0; i<len; i++)
		{
			if(list[i].id == id)
			{
				index = i;
				break;
			}
		}
	}
	return index;
}
/** \brief Sort the elements in the array of passengers, the argument order
indicate UP or DOWN order
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int sortPassengers(ePassenger* list, int len, int order)
{
	int retorno = -1;
	int flagSwap;
	int nuevoLimite;
	ePassenger auxPassanger;

	if(list != NULL && len > 0 && (order == ASCENDENTE || order == DESCENDENTE))
	{
		nuevoLimite = len -1;
		do
		{
			flagSwap = 0;
			for(int i = 0; i< nuevoLimite; i++)
			{
				if( (order == ASCENDENTE &&
					(list[i].isEmpty == FALSE) &&//|| list[i+1].isEmpty == FALSE) &&
					(list[i].typePassenger > list[i+1].typePassenger ||
					(list[i].typePassenger == list[i+1].typePassenger &&
					(strncmp(list[i].lastName,list[i+1].lastName,51) > 0))))
					||
					(order == DESCENDENTE &&
					(list[i].isEmpty == FALSE) &&// || list[i+1].isEmpty == FALSE) &&
					(list[i].typePassenger < list[i+1].typePassenger ||
					(list[i].typePassenger == list[i+1].typePassenger &&
					(strncmp(list[i].lastName,list[i+1].lastName,51) < 0))))
				  )
				{
					flagSwap = 1;
					auxPassanger = list[i];
					list[i] = list[i+1];
					list[i+1]= auxPassanger;
					retorno = 0;
				}

			}
		}while(flagSwap);
	}

	return retorno;
}
/**
 * \brief Imprime todos los campos de la estructura ePassenger
 * \param aPassanger un pasagero
 */
void printOnePassenger(ePassenger aPassanger)
{
	printf("\n|%-4d",aPassanger.id);
	printf("|%-10s",aPassanger.flycode);
	printf("|%-10s",aPassanger.name);
	printf("|%-10s",aPassanger.lastName);
	printf("|%-10.2f",aPassanger.price);
	if(aPassanger.statusFlight == 1)
	{
		printf("|ACTIVO    ");
	}
	else if(aPassanger.statusFlight == 2)
	{
		printf("|FINALIZADO");
	}
	else if(aPassanger.statusFlight == 3)
	{
		printf("|CANCELADO ");
	}
	if(aPassanger.typePassenger == 1)
	{
		printf("|TURISTA  |");
	}
	if(aPassanger.typePassenger == 2)
	{
		printf("|PREMIUM  |");
	}
	if(aPassanger.typePassenger == 3)
	{
		printf("|BUSINESS |");
	}
	if(aPassanger.typePassenger == 4)
	{
		printf("|EJECUTIVO|");
	}
}
/** \brief print the content of passengers array
* \param list Passenger* Pointer to array of passenger
* \param length int Array length
* \return int retorna 0 en caso de OK y -1 de error
*/
int printPassenger(ePassenger* list, int length)
{
	int retorno = -1;
	if(list != NULL && length > 0)
	{
		if(isArrayPassengerEmpty(list, length) == FALSE)
		{
			printf("\n _____________________________________________________________________");
			printf("\n|ID  |CODIGO    |NOMBRE    |APELLIDO  |PRECIO    |ESTADO    |TIPO     |");
			printf("\n|---------------------------------------------------------------------|");
			for(int i= 0;i< length;i++)
			{
				if(list[i].isEmpty == FALSE)
				{
					printOnePassenger(list[i]);
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief El alta de un pasagero
 * \param list Pointer to array of passenger
 * \param len Array length
 * \param pId puntero al id de pasageros
 * \return retorna 0 en caso de OK, -2 en caso de no encontrar un indice libre y -1 de ERROR
 */
int registerPassenger(ePassenger *list, int len, int *pId)
{
	ePassenger auxPassenger;
	int retorno = -1;
	int index;
	if(list != NULL && len > 0 && pId != NULL)
	{
		index = findEmptyPassenger(list, len);
		if(index != -1)
		{
			if(!utn_pedirCadena(auxPassenger.flycode, 10, "\nINGRESE CODIGO DE VUELO[9 DIGITOS ALFANUM]: \n",
								"\nERROR\nREINGRESE NUEVAMENTE", 9, 9, 5) &&
			   !utn_pedirNombreApellido(auxPassenger.name, 51, "\nINGRESE EL NOMBRE DEL PASAGERO: \n",
									    "\nERROR\nREINGRESE NUEVAMENTE", 2, 51, 5) &&
			   !utn_pedirNombreApellido(auxPassenger.lastName, 51, "\nINGRESE EL APELLIDO DEL PASAGERO: \n",
									    "\nERROR\nREINGRESE NUEVAMENTE", 2, 51, 5) &&
		       !utn_pedirFlotante(&auxPassenger.price, "\nINGRESE EL PRECIO DEL VUELO: \n",
		    		   	   	   	  "\nERROR\nREINGRESE NUEVAMENTE", 100, 300000.0, 5) &&
			   !utn_pedirEntero(&auxPassenger.statusFlight, "\nINGRESE EL ESTADO DEL VUELO:\n1-ACTIVO\n2-FINALIZADO\n3-CANCELADO\n",
					   	   	   	"\nERROR\nREINGRESE NUEVAMENTE", 1, 3, 5) &&
			   !utn_pedirEntero(&auxPassenger.typePassenger, "\nINGRESE EL TIPO DE PASAGERO:\n1-TURISTA\n2-PREMIUM\n3-BUSINESS\n4-EJECUTIVO\n",
								"\nERROR\nREINGRESE NUEVAMENTE", 1, 4, 5))
			{
				auxPassenger.isEmpty = FALSE;
				auxPassenger.id= *pId + 1;
				list[index] = auxPassenger;
				(*pId)++;
				retorno = 0;
			}
		}
		else
		{
			retorno = -2;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si el id pasado por valor es valido en el array de pasageros
 * \param list Pointer to array of passenger
 * \param len array length
 * \param id el id del pasagero
 * \return retorna 1 en caso de ser verdadero y 0 de falso
 */
int isValidId(ePassenger* list, int len, int id)
{
	int result = 0;
	if(list != NULL && len > 0 && id > 0)
	{
		for(int i = 0; i<len; i++)
		{
			list[i].id = id;
			result = 1;
			break;
		}
	}
	return result;
}
/**
 * \brief Modifica el campo de un pasagero en la lista
 * \param list Pointer to array of passenger
 * \param len Array length
 * \param id el id del pasagero a modificar
 * \return retorna 0 en caso de OK y -1 de error
 */
int modifyPassenger(ePassenger* list, int len,int id)
{
	ePassenger auxPassenger;
	int option;
	int retorno = -1;
	int index;
	if(list != NULL && len > 0 && id > 0)
	{
		index = findPassengerById(list, len, id);
			if(	index != -1 &&
				!utn_pedirEntero(&option, "\nINGRESE CAMPO A MODIFICAR:\n"
								"\n1-N0MBRE\n2-APELLIDO\n3-PRECIO\n4-TIPO DE PASAGERO\n5-CODIGO DE VUELO\n",
								"\nERROR\nREINGRESE NUEVAMENTE",1, 5, 15))
			{
				switch(option)
				{
				case 1:
					if(!utn_pedirNombreApellido(auxPassenger.name, 51, "\nINGRESE EL NOMBRE DEL PASAGERO: \n",
										"\nERROR\nREINGRESE NUEVAMENTE", 2, 51, 5))
					{
						//strncpy( (*(list + index)).name,auxPassenger.name,51);->CON ARITMETICA DE PUNTEROS
						strncpy(list[index].name,auxPassenger.name,51);
					}
					break;
				case 2:
					if(!utn_pedirNombreApellido(auxPassenger.lastName, 51, "\nINGRESE EL APELLIDO DEL PASAGERO: \n",
										"\nERROR\nREINGRESE NUEVAMENTE", 2, 51, 5))
					{
						strncpy(list[index].lastName,auxPassenger.lastName,51);
					}
					break;
				case 3:
					if(!utn_pedirFlotante(&auxPassenger.price, "\nINGRESE EL PRECIO DEL VUELO: \n",
								  "\nERROR\nREINGRESE NUEVAMENTE", 100, 300000.0, 5) )
					{
						//(*(list + index)).price = auxPassenger.price;
						list[index].price = auxPassenger.price;
					}
					break;
				case 4:
					if(!utn_pedirEntero(&auxPassenger.typePassenger, "\nINGRESE EL TIPO DE PASAGERO:\n1-TURISTA\n2-PREMIUM\n3-BUSINESS\n4-EJECUTIVO\n",
										"\nERROR\nREINGRESE NUEVAMENTE", 1, 4, 5))
					{
						list[index].typePassenger = auxPassenger.typePassenger;
					}
					break;
				case 5:
					if(!utn_pedirCadena(auxPassenger.flycode, 10, "\nINGRESE CODIGO DE VUELO[9 DIGITOS ALFANUM]: \n",
								"\nERROR\nREINGRESE NUEVAMENTE", 9, 9, 5))
					{
						strncpy(list[index].flycode,auxPassenger.flycode,10);
					}
					break;
				}
				retorno = 0;
			}
	}
	return retorno;
}
/** \brief Remove a Passenger by Id (put isEmpty Flag in 1)
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \param id int el id del pasagero
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a passenger] - (0) if Ok
*/
int removePassenger(ePassenger* list, int len, int id)
{
	int retorno = -1;
	int index;
	if(list != NULL && len > 0 && id > 0)
	{
		index = findPassengerById(list, len, id);
		if(index !=-1)
		{
			list[index].isEmpty = TRUE;
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Calcula el precio acumulado en el array de passageros
 * \param list Pointer to array of passenger
 * \param length Array length
 * \param pTotalPrice el puntero del total
 * \return Retorna 0 en caso de OK y -1 en caso de ERROR
 */
int totalPricePassenger(ePassenger* list, int length, float* pTotalPrice)
{
	int retorno = -1;
	int flag = 0;
	float accumulator = 0;
	if(list != NULL && length > 0 && pTotalPrice != NULL)
	{
		for(int i = 0; i < length; i++)
		{
			if(isPassangerEmpty(list[i])==FALSE)
			{
				flag = 1;
				accumulator += list[i].price;
			}
		}
		if(flag == 1)
		{
			retorno = 0;
			*pTotalPrice = accumulator;
		}
	}
	return retorno;
}
/**
 * \brief Imprime la lista de pasageros por codigo de vuelo y estado ACTIVO
 * \param list Pointer to array of passenger
 * \param length Array length
 */
void listPassengersByCodeAndType(ePassenger* list, int length)
{
	for(int i = 0; i < length; i++)
	{
		if(isPassangerEmpty(list[i]) == FALSE &&
		   list[i].statusFlight == ACTIVO)
		{
			printf("|%-10s",list[i].flycode);
			printf("|%-10s",list[i].name);
			printf("|%-10s",list[i].lastName);
			printf("\n");
		}
	}
}
/**
 * \brief Verifica si el pasagero pasado esta vacio
 * \param aPassenger un Pasagero
 * \return retorna 0 en caso de FALSO y 1 en caso de VERDADERO
 */
int isPassangerEmpty(ePassenger aPassenger)
{
	int retorno = 1;
	if(aPassenger.isEmpty == FALSE)
	{
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief La cantidad de pasageros que supera el promedio de precios
 * \param list Pointer to array of passenger
 * \param length Array length
 * \param averagePrice el promedio
 * \param pPassengers puntero de la cantidad de pasageros
 * \return retorna 0 en caso de OK y -1 de ERROR
 */
int passengersAboveAverage(ePassenger* list, int length, float averagePrice, int* pPassengers)
{
	int retorno = -1;
	int flag = 0;
	if(list != NULL && length > 0 &&
	   pPassengers!= NULL && averagePrice > 0)
	{
		for(int i = 0; i< length; i++)
		{
			if(isPassangerEmpty(list[i])==FALSE &&
			   list[i].price > averagePrice)
			{
				flag = 1;
				(*pPassengers)++;
			}
		}
		if(flag == 1)
		{
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Calcula el promedio de precio total del array
 * \param list Pointer to array of passenger
 * \param length Array length
 * \param totalPrice El precio total
 * \param pAveragePrice puntero del promedio
 * \return Retorna 0 en caso de Ok y -1 de ERROR
 */
int averagePricePerPassenger(ePassenger* list, int length, float totalPrice,float* pAveragePrice)
{
	int retorno = -1;
	int counterPassenger = 0;
	if(list != NULL && length > 0 &&
	   pAveragePrice!= NULL && totalPrice > 0)
	{
		for(int i = 0; i < length; i++)
		{
			if(isPassangerEmpty(list[i])==FALSE)
			{
				counterPassenger++;
			}
		}
		if(counterPassenger > 0)
		{
			retorno = 0;
			*pAveragePrice = totalPrice / counterPassenger;
		}
	}
	return retorno;
}
/**
 * \brief El menu con los distintos informes
 * \param list Pointer to array of passenger
 * \param len Array length
 * \return Retorna 0 en caso de exito y -1 de ERROR
 */
int menuInformes(ePassenger* list, int len)
{
	int option = -1;
	int order;
	float totalPrice;
	float averagePassenger;
	int passengersCounter = 0;

	if(list != NULL && len > 0)
	{
		if(!utn_pedirEntero(&option,
				"\n ______________________________________________"
			    "\n|                 MENU INFORMES                |"
			    "\n|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|"
			    "\n|1-LISTADO PASAGEROS ORDENADOS(APELLIDO/TIPO)  |"
			    "\n|2-TOTAL, PROMEDIO Y CUANTOS SUPERAN LA MEDIA  |"
			    "\n|3-LISTADO PASAGEROS POR CODIGO Y ESTADO ACTIVO|"
			    "\n|4-SALIR DE INFORMES                           |"
			    "\n ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯"
			    "\n|INGRESE OPCION: ",
			    "\n***|ERROR|***\nREINGRESE NUEVAMENTE", 1, 4, 5))
		{
			switch(option)
			{
				case 1:
					if( !utn_pedirEntero(&order, "\nASCENDENTE(1)"
												 "\nDESCENDENTE(0)"
												 "\nINGRESE OPCION: ",
												 "\nERROR\nREINGRESE NUEVAMENTE", 0, 1, 5) &&
						!sortPassengers(list,len, order) )
					{
						printf("\nPASAGEROS ORDENADOS\n");
					}
				break;
				case 2:
					if(!totalPricePassenger(list, len, &totalPrice) &&
					   !averagePricePerPassenger(list, len, totalPrice, &averagePassenger))
					{
						printf("\nEL PRECIO TOTAL DE TODOS LOS PASAGES ES: %.2f",totalPrice);
						printf("\nEL PROMEDIO DE TODOS LOS PASAGES ES: %.2f",averagePassenger);
						if(!passengersAboveAverage(list, len, averagePassenger, &passengersCounter))
						{
							printf("\nCANTIDAD DE PASAGEROS QUE SUPERAN EL PRECIO PROMEDIO: %d",passengersCounter);
						}
					}
					else
					{
						printf("\nNO HAY PASAGEROS CARGADOS EN EL SISTEMA\n");
					}
				break;
				case 3:
					listPassengersByCodeAndType(list, len);
				break;
			}
		}
	}
	return option;
}
/**
* \brief El menu del ABM de pasageros
* \param list Pointer to array of passenger
* \param len Array length
* \return Retorna la opcion en caso de OK y -1 de ERROR
*/
int menuPassenger(ePassenger* list, int len,int* pId)
{
	int option = -1;
	int optionInformes;
	int output;
	int id;
	int altaPassanger;

	if(list != NULL && len > 0 && pId != NULL)
	{
		output = utn_pedirEntero(&option,
								"\n ____________________"
								"\n|MENU PASAGEROS      |"
								"\n|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|"
								"\n|1-ALTA              |"
								"\n|2-MODIFICAR         |"
								"\n|3-BAJA              |"
								"\n|4-MENU INFORMES     |"
								"\n|5-IMPRIMIR PASAGEROS|"
								"\n|6-SALIR             |"
								"\n ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯"
								"\n|INGRESE OPCION: ",
								"\n***|ERROR|***\n", 1, 6, 5);
		if(!output)
		{
			switch(option)
			{
				case 1:
					altaPassanger = registerPassenger(list, len, pId);
					if(altaPassanger == 0)
					{
						printf("\n|****PASAGERO AGREGADO****|\n");
					}
					else if(altaPassanger == -2)
					{
						printf("\n|****NO HAY ESPACIO PARA MAS PASAGEROS****|\n");
					}
					else
					{
						printf("\n|****NO PUDO AGREGARSE EL PASAGERO****|\n");
					}
					break;
				case 2:
					if(isArrayPassengerEmpty(list, len) == FALSE)
					{
						if(!printPassenger(list, len) &&
						   !utn_pedirEntero(&id, "\nINGRESE ID A MODIFICAR: \n",
								   	   	   "\nERROR\nREINGRESE NUEVAMENTE", 1, 100000, 5) &&
						   isValidId(list, len, id)==TRUE)
						{
							if(!modifyPassenger(list, len, 1))
							{
								printf("\n|****PASAGERO MODIFICADO****|\n");
							}

						}
						else
						{
							printf("\n|****EL ID NO ES VALIDO****|\n");
						}
					}
					else
					{
						printf("\n|****LA LISTA DE PASAGEROS ESTA VACIA****|\n");
					}
					break;
				case 3:
					if(isArrayPassengerEmpty(list, len) == FALSE)
					{
						if(removePassenger(list, len, 1)==-1)
						{
							printf("\n|****PASAGERO BORRADO****|\n");
						}
					}
					else
					{
						printf("\n|****LA LISTA DE PASAGEROS ESTA VACIA****|\n");
					}
					break;
				case 4:
					do
					{
						optionInformes = menuInformes(list, len);
					}while(optionInformes != 4);
					break;
				case 5:
					if(isArrayPassengerEmpty(list, len) == FALSE &&
					   !printPassenger(list, len))
					{
						printf("\n ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
					}
					else
					{
						printf("\n|****LA LISTA DE PASAGEROS ESTA VACIA****|\n");
					}
					break;
				case 6:

					break;
			}
		}
	}
	return option;
}



















