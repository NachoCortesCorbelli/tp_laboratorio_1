/*
 * Passenger.c
 *
 *  Created on: 19 may. 2022
 *      Author: Cortés Corbelli, Ignacio Martín
 */
#include "Passenger.h"

Passenger* passenger_new(void)
{
	return (Passenger*) malloc (sizeof(Passenger));
}
Passenger* passenger_newParametros(int id,char* nombre,char* apellido,float precio,
								   char* codigoVuelo,int tipoPasajero,
								   int estadoVuelo)
{
	Passenger* pPassenger = NULL;
	pPassenger = passenger_new();
	if(pPassenger != NULL)
	{
		passenger_setId(pPassenger, id);
	    passenger_setNombre(pPassenger, nombre);
	    passenger_setApellido(pPassenger, apellido);
	    passenger_setPrecio(pPassenger, precio);
	    passenger_setCodigoVuelo(pPassenger, codigoVuelo);
	    passenger_setTipoPasajero(pPassenger, tipoPasajero);
	    passenger_setEstadoVuelo(pPassenger, estadoVuelo);
	}
	return pPassenger;
}
Passenger* passenger_newParametrosStr(char* idStr,char* nombreStr,
									   char* apellidoStr,char* precioStr,
									   char* codigoVueloStr,char* tipoPasajeroStr,
									   char* estadoVueloStr)
{
	Passenger* pPassenger = NULL;
	pPassenger = passenger_new();
	if(pPassenger != NULL)
	{
		passenger_setIdTxt(pPassenger, idStr);
		passenger_setNombre(pPassenger, nombreStr);
		passenger_setApellido(pPassenger, apellidoStr);
		passenger_setPrecioTxt(pPassenger, precioStr);
		passenger_setCodigoVuelo(pPassenger, codigoVueloStr);
		passenger_setTipoPasajeroTxt(pPassenger, tipoPasajeroStr);
		passenger_setEstadoVueloTxt(pPassenger, estadoVueloStr);
	}
	return pPassenger;
}

void passenger_delete(Passenger* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

int passenger_setNombre(Passenger* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		if(nombre[strlen(nombre)-1] == '\n')
		{
			nombre[strlen(nombre)-1] = '\0';
		}
		if(esNombreApellido(nombre, 50)==1)
		{
			retorno = 0;
			strncpy(this->nombre,nombre,50);
		}
	}
	return retorno;
}
int passenger_getNombre(Passenger* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre,this->nombre,50);
	}
	return retorno;
}
int passenger_setApellido(Passenger* this,char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL)
	{
		if(apellido[strlen(apellido)-1] == '\n')
		{
			apellido[strlen(apellido)-1] = '\0';
		}
		/*
		if(esNombreApellido(apellido, 50)==1)
		{
			retorno = 0;
			strncpy(this->apellido,apellido,50);
		}
		*/
		retorno = 0;
		strncpy(this->apellido,apellido,50);
	}
	//printf("\nRETORNO: %d",retorno);
	return retorno;
}
int passenger_getApellido(Passenger* this,char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL)
	{
		retorno = 0;
		strncpy(apellido,this->apellido,50);
	}
	return retorno;
}
int passenger_getId(Passenger* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		*id = this->id;
	}
	return retorno;
}
int passenger_setIdTxt(Passenger* this,char* id)
{
	int retorno = -1;
	int auxId;
	if(this != NULL && id != NULL)
	{
		if(esNumerica(id, SIZE_STRING)==1)//valido el id
		{
			auxId = atoi(id);
			if(auxId > 0)
			{
				retorno = 0;
				this->id = auxId;
			}
		}
	}
	return retorno;
}

int passenger_setId(Passenger* this,int id)
{
	int retorno = -1;
	if(this != NULL && id > 0)
	{
		retorno = 0;
		this->id = id;
	}
	return retorno;
}
int passenger_setPrecioTxt(Passenger* this,char* precioStr)
{
	int retorno = -1;
	float auxPrecio;
	if(this != NULL && precioStr != NULL)
	{
		if(esNumerica(precioStr, SIZE_STRING)==1)
		{
			auxPrecio = atof(precioStr);
			if(auxPrecio > 0)
			{
				retorno = 0;
				this->precio = auxPrecio;
			}
		}
	}
	return retorno;
}
int passenger_setPrecio(Passenger* this,float precio)
{
	int retorno = -1;
	if(this != NULL)
	{
		retorno = 0;
		this->precio = precio;
	}
	return retorno;
}
int passenger_getPrecio(Passenger* this,float* precio)
{
	int retorno = -1;
	if(this != NULL && precio != NULL)
	{
		retorno = 0;
		*precio = this->precio;
	}
	return retorno;
}

int passenger_setCodigoVuelo(Passenger* this, char* codigoVueloStr)
{
	int retorno = -1;
	if(this != NULL && codigoVueloStr != NULL)
	{
		if(codigoVueloStr[strlen(codigoVueloStr)-1] == '\n')
		{
			codigoVueloStr[strlen(codigoVueloStr)-1] = '\0';
		}

		retorno = 0;
		strncpy(this->codigoVuelo,codigoVueloStr,8);
	}
	return retorno;
}
int passenger_getCodigoVuelo(Passenger* this, char* codigoVuelo)
{
	int retorno = -1;
	if(this != NULL && codigoVuelo != NULL)
	{
		retorno = 0;
		strncpy(codigoVuelo,this->codigoVuelo,8);
	}
	return retorno;
}
//CREAR VALIDATION - USO DEFINES PARA LOS TIPOS DE VUELOS
int passenger_setTipoPasajeroTxt(Passenger* this, char* tipoPasajeroStr)
{
	int retorno = -1;
	int retornoValidacion;
	if(this != NULL && tipoPasajeroStr != NULL)
	{
		//ENCUENTRA EL /n Y LO REEMPLAZA POR /0
		if(tipoPasajeroStr[strlen(tipoPasajeroStr)-1] == '\n')
		{
			tipoPasajeroStr[strlen(tipoPasajeroStr)-1] = '\0';
		}
		retornoValidacion = esTipoPasajero(tipoPasajeroStr,sizeof(tipoPasajeroStr));
		if(retornoValidacion == 1 || retornoValidacion == 2 ||
		   retornoValidacion == 3 )
		{
			this->tipoPasajero = retornoValidacion;
			retorno = 0;
		}
	}
	return retorno;
}
int passenger_getTipoPasajeroTxt(Passenger* this, int tipoPasajero, char* tipoPasajeroStr)
{
	int retorno = 0;
	if(this != NULL && tipoPasajeroStr != NULL)
	{
		if(tipoPasajero == 1)
		{
			strncpy(tipoPasajeroStr,"EconomyClass",50);
		}
		else if(tipoPasajero == 2)
		{
			strncpy(tipoPasajeroStr,"ExecutiveClass",50);
		}
		else if(tipoPasajero == 3)
		{
			strncpy(tipoPasajeroStr,"FirstClass",50);
		}
		else
		{
			retorno = -1;
		}
		if(retorno == 0 &&
		    tipoPasajeroStr[strlen(tipoPasajeroStr)-1] == '\n')
		{
			tipoPasajeroStr[strlen(tipoPasajeroStr)-1] = '\0';
		}
	}
	return retorno;
}
int passenger_setTipoPasajero(Passenger* this,int tipoPasajero)
{
	int retorno = -1;
	if(this != NULL)
	{
		retorno = 0;
		this->tipoPasajero = tipoPasajero;
	}
	return retorno;
}
int passenger_getTipoPasajero(Passenger* this, int* tipoPasajero)
{
	int retorno = -1;
	if(this != NULL && tipoPasajero!= NULL)
	{
		retorno = 0;
		*tipoPasajero = this->tipoPasajero;
	}
	return retorno;
}
int passenger_setEstadoVueloTxt(Passenger* this, char* estadoVueloStr)
{
	int retorno = -1;
	int retornoValidacion;
	if(this != NULL && estadoVueloStr != NULL)
	{
		//ENCUENTRA EL /n Y LO REEMPLAZA POR /0
		if(estadoVueloStr[strlen(estadoVueloStr)-1] == '\n')
		{
			estadoVueloStr[strlen(estadoVueloStr)-1] = '\0';
		}
		retornoValidacion = esEstadoVuelo(estadoVueloStr,sizeof(estadoVueloStr));
		if(retornoValidacion >= 1 && retornoValidacion <= 4)
		{
			this->estadoVuelo = retornoValidacion;
			retorno = 0;
		}
	}
	return retorno;
}
int passenger_setEstadoVuelo(Passenger* this,int estadoVuelo)
{
	int retorno = -1;
	if(this != NULL)
	{
		retorno = 0;
		this->estadoVuelo = estadoVuelo;
	}
	return retorno;
}
int passenger_getEstadoVuelo(Passenger* this, int* estadoVuelo)
{
	int retorno = -1;
	if(this != NULL && estadoVuelo!= NULL)
	{
		retorno = 0;
		*estadoVuelo = this->estadoVuelo;
	}
	return retorno;
}
int passenger_getEstadoVueloTxt(Passenger* this,int estadoVuelo, char* estadoVueloStr)
{
	int retorno = 0;
	if(this != NULL && estadoVueloStr != NULL)
	{
		if(estadoVuelo == 1)
		{
			strncpy(estadoVueloStr,"En Vuelo",50);
		}
		else if(estadoVuelo == 2)
		{
			strncpy(estadoVueloStr,"En Horario",50);
		}
		else if(estadoVuelo == 3)
		{
			strncpy(estadoVueloStr,"Aterrizado",50);
		}
		else if(estadoVuelo == 4)
		{
			strncpy(estadoVueloStr,"Demorado",50);
		}
		else
		{
			retorno = -1;
		}
		if(retorno == 0 &&
		   estadoVueloStr[strlen(estadoVueloStr)-1] == '\n')
		{
			estadoVueloStr[strlen(estadoVueloStr)-1] = '\0';
		}
	}
	return retorno;
}
int passenger_addToList(LinkedList* pArrayListPassenger, int* pIdPassenger)
{
	int retorno = -1;
	Passenger auxPassenger;
	Passenger* pAuxPassenger = NULL;
	if(pArrayListPassenger != NULL &&
	   pIdPassenger != NULL)
	{
		if(!utn_pedirNombreApellido(auxPassenger.nombre, 50,
								   "\nINGRESE EL NOMBRE DEL PASAJERO: ",
								   "\nERROR\n", 2, 50, 5) &&
		   !utn_pedirNombreApellido(auxPassenger.apellido, 50,
								   "\nINGRESE EL APELLIDO DEL PASAJERO: ",
								   "\nERROR", 2, 50, 5) &&
		   !utn_pedirCadena(auxPassenger.codigoVuelo, 8,
						   "\nINGRESE EL CODIGO DE VUELO DEL PASAJERO[7 DIGITOS]: ",
						   "\nERROR\n", 7, 8, 5) &&
		   !utn_pedirFlotante(&auxPassenger.precio,
							   "\nINGRESE EL PRECIO DEL PASAJE: ",
							   "\nERROR", 100, 1000000, 5) &&
		   !utn_pedirEntero(&auxPassenger.tipoPasajero,
							"\nINGRESE EL TIPO DE PASAJERO: "
							"\n1-CLASE ECONOMICA"
							"\n2-CLASE EJECUTIVA"
							"\n3-PRIMERA CLASE"
							"\nINGRESE OPCION: ",
							"\nERROR\n", 1, 3, 5) &&
		   !utn_pedirEntero(&auxPassenger.estadoVuelo,
							"\nINGRESE EL ESTADO DEL VUELO: "
							"\n1-EN VUELO"
							"\n2-EN HORARIO"
							"\n3-ATERRIZADO"
							"\nINGRESE OPCION: ",
							"\nERROR\n", 1, 3, 5))
		{
			pAuxPassenger = passenger_newParametros((*pIdPassenger), auxPassenger.nombre,
													auxPassenger.apellido, auxPassenger.precio,
													auxPassenger.codigoVuelo, auxPassenger.tipoPasajero,
													auxPassenger.estadoVuelo);
			if( pAuxPassenger != NULL &&
				!ll_add(pArrayListPassenger, pAuxPassenger))
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}
int passenger_modifyPassenger(Passenger* pPassenger)
{
	int retorno = -1;
	Passenger auxPassenger;
	int opcion;

	if(pPassenger != NULL)
	{
		if(utn_pedirEntero(&opcion,"\nCAMPO A MODIFICAR:"
								   "\n1-NOMBRE"
								   "\n2-APELLIDO"
				           	       "\n3-PRECIO"
								   "\n4-CLASE"
				   	   	   	   	   "\n5-CODIGO DE VUELO"
	   	   	   	   	   	   	   	   "\n6-ESTADO"
								   "\n7-SALIR"
								   "\nOPCION: ", "\nERROR\n", 1, 7, 5)==0)
		{
			switch(opcion)
			{
			case 1:
				if(utn_pedirNombreApellido(auxPassenger.nombre, 50,
									       "\nINGRESE EL NOMBRE DEL PASAJERO: ",
									       "\nERROR\n", 3, 50, 5) == 0)
				{
					if(!passenger_setNombre(pPassenger, auxPassenger.nombre))
					{
						printf("\nMODIFICADO\n");

					}
				}
				break;
			case 2:
				if(utn_pedirNombreApellido(auxPassenger.apellido, 50,
										   "\nINGRESE EL APELLIDO DEL PASAJERO: ",
										   "\nERROR\n", 3, 50, 5) == 0)
				{
					if(!passenger_setApellido(pPassenger, auxPassenger.apellido))
					{
						printf("\nMODIFICADO\n");
					}
				}
				break;
			case 3:
				if(utn_pedirFlotante(&auxPassenger.precio,
								     "\nINGRESE EL PRECIO DEL VIAJE: ",
								     "\nERROR\n", 100, 150000, 5) == 0)
				{
					if(!passenger_setPrecio(pPassenger, auxPassenger.precio))
					{
						printf("\nMODIFICADO\n");
					}
				}
				break;
			case 4:
				if(utn_pedirEntero(&auxPassenger.tipoPasajero,
								  "\nSELECCIONE LA CLASE: "
								  "\n1-ECONOMICA\n2-EJECUTIVA\n3-PRIMERA"
								  "\nOPCION:",
								  "\nERROR\n", 1, 3, 5) == 0)
				{
					if(!passenger_setTipoPasajero(pPassenger, auxPassenger.tipoPasajero))
					{
						printf("\nMODIFICADO\n");
					}
				}
				break;
			case 5:
				if(utn_pedirCadena(auxPassenger.codigoVuelo, 8,
								  "\nINGRESE EL CODIGO DEL VUELO: ",
								  "\nERROR\n", 7, 7, 5) == 0)
				{
					if(!passenger_setCodigoVuelo(pPassenger, auxPassenger.codigoVuelo))
					{
						printf("\nMODIFICADO\n");
					}
				}
				break;
			case 6:
				if(utn_pedirEntero(&auxPassenger.estadoVuelo,
								  "\nSELECCIONE EL ESTADO DEL VUELO: "
								  "\n1-EN VUELO\n2-EN HORARIO\n3-ATERRIZADO\n4-DEMORADO"
								  "\nOPCION: ",
								  "\nERROR\n", 1, 4, 5) == 0)
				{
					if(!passenger_setEstadoVuelo(pPassenger, auxPassenger.estadoVuelo))
					{
						printf("\nMODIFICADO\n");
					}
				}
				break;
			}
			retorno = 0;
		}
	}
	return retorno;
}
Passenger* passenger_getById(LinkedList* pArrayListPassenger, int idToFind)
{
	Passenger* pPassenger;
	int length;
	int index;

	if(pArrayListPassenger != NULL &&
	   idToFind >= 0)
	{
		length = ll_len(pArrayListPassenger);
		for(index = 0; index < length; index++)
		{
			pPassenger = (Passenger*)ll_get(pArrayListPassenger, index);
			if(pPassenger != NULL && pPassenger->id == idToFind)
			{
				break;
			}
		}
	}
	return pPassenger;
}
int passenger_getIndexById(LinkedList* pArrayListPassenger, int idToFind)
{
	Passenger* pAuxPassenger;
	int length;
	int index;

	if(pArrayListPassenger != NULL &&
	   idToFind >= 0)
	{
		length = ll_len(pArrayListPassenger);
		for(int i = 0; i < length; i++)
		{
			index = ll_indexOf(pArrayListPassenger, pAuxPassenger);
			if(index != -1)
			{
				pAuxPassenger = (Passenger*)ll_get(pArrayListPassenger, index);
				if(pAuxPassenger != NULL && pAuxPassenger->id == idToFind)
				{
					break;
				}
			}
		}
	}
	return index;
}
/**
 * \brief imprime un pasajero
 * \param pArrayListPassenger la linked list
 * \param index la posicion en la lista
 * \return retorna 0 si pudo imprimir y -1 de error
 */
int passenger_print(LinkedList* pArrayListPassenger, int index)
{
	Passenger* pAuxPassenger;
	int retorno = -1;
	int id;
	char nombre[SIZE_STRING];
	char apellido[SIZE_STRING];
	float precio;
	char codigoVuelo[SIZE_STRING];
	int tipoPasajero;
	char tipoPasajeroStr[SIZE_STRING];
	int estadoVuelo;
	char estadoVueloStr[SIZE_STRING];

	if(pArrayListPassenger != NULL && index >= 0)
	{
		pAuxPassenger = (Passenger*)ll_get(pArrayListPassenger, index);
		if(pAuxPassenger != NULL &&
		  !passenger_getId(pAuxPassenger, &id) &&
		  !passenger_getNombre(pAuxPassenger, nombre)&&
		  !passenger_getApellido(pAuxPassenger, apellido) &&
		  !passenger_getPrecio(pAuxPassenger, &precio) &&
		  !passenger_getCodigoVuelo(pAuxPassenger, codigoVuelo) &&
		  !passenger_getTipoPasajero(pAuxPassenger, &tipoPasajero) &&
		  !passenger_getEstadoVuelo(pAuxPassenger, &estadoVuelo) &&
		  !passenger_getTipoPasajeroTxt(pAuxPassenger, tipoPasajero, tipoPasajeroStr) &&
		  !passenger_getEstadoVueloTxt(pAuxPassenger, estadoVuelo, estadoVueloStr))
		{
		  	  printf("\n%d,%s,%s,%.2f,%s,%s,%s",id,nombre,apellido,precio,
		  			  	  	  	  	  	  	    codigoVuelo,tipoPasajeroStr,estadoVueloStr);
		  	  retorno = 0;
		}
	}
	return retorno;
}
int passenger_deleteFromList(LinkedList* pArrayListPassenger, int index)
{
	Passenger* pAuxPassenger;
	int retorno = -1;

	if(pArrayListPassenger != NULL && index >= 0)
	{
		pAuxPassenger = (Passenger*)ll_pop(pArrayListPassenger, index);
		if(pAuxPassenger != NULL)
		{
			//ll_remove -> podría usar el remove ???
			passenger_delete(pAuxPassenger);
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief Realiza el ordenamiento de 2 empleados por el nombre
 * \param pElement1 el puntero a void del primer elemento
 * \param pElement2 el puntero a void del segundo elemento
 * \return reotrna 0 si son iguales, -1 si es menor el primero y 1 si es mayor
 */
int passenger_sortByName(void* pElement1, void* pElement2)
{
	Passenger* pPassenger1 = NULL;
	Passenger* pPassenger2 = NULL;
	int retorno;
	int returnCmp;

	pPassenger1 = (Passenger*)pElement1;
	pPassenger2 = (Passenger*)pElement2;
	returnCmp = strncmp(pPassenger1->nombre,pPassenger2->nombre,50);

	if(returnCmp < 0)
	{
		retorno = -1;
	}
	else if(returnCmp > 0)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;
}
/**
 * \brief Realiza el ordenamiento de 2 empleados por el apellido
 * \param pElement1 el puntero a void del primer elemento
 * \param pElement2 el puntero a void del segundo elemento
 * \return reotrna 0 si son iguales, -1 si es menor el primero y 1 si es mayor
 */
int passenger_sortByLastName(void* pElement1, void* pElement2)
{
	Passenger* pPassenger1 = NULL;
	Passenger* pPassenger2 = NULL;
	int retorno;
	int returnCmp;

	pPassenger1 = (Passenger*)pElement1;
	pPassenger2 = (Passenger*)pElement2;
	returnCmp = strncmp(pPassenger1->apellido,pPassenger2->apellido,50);

	if(returnCmp < 0)
	{
		retorno = -1;
	}
	else if(returnCmp > 0)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;
}
/**
 * \brief Realiza el ordenamiento de 2 pasajeros por el id
 * \param pElement1 el puntero a void del primer elemento
 * \param pElement2 el puntero a void del segundo elemento
 * \return reotrna 0 si son iguales, -1 si es menor el primero y 1 si es mayor
 */
int passenger_sortById(void* pElement1, void* pElement2)
{
	int retorno;
	Passenger* auxPassenger1 = NULL;
	Passenger* auxPassenger2 = NULL;

	auxPassenger1 = (Passenger*) pElement1;
	auxPassenger2 = (Passenger*) pElement2;

	if(auxPassenger1->id < auxPassenger2->id)
	{
		retorno = -1;
	}
	else if(auxPassenger1->id > auxPassenger2->id)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;
}
/**
 * \brief Realiza el ordenamiento de 2 empleados por el precio
 * \param pElement1 el puntero a void del primer elemento
 * \param pElement2 el puntero a void del segundo elemento
 * \return reotrna 0 si son iguales, -1 si es menor el primero y 1 si es mayor
 */
int passenger_sortByPrice(void* pElement1, void* pElement2)
{
	int retorno;
	Passenger* auxPassenger1 = NULL;
	Passenger* auxPassenger2 = NULL;

	auxPassenger1 = (Passenger*) pElement1;
	auxPassenger2 = (Passenger*) pElement2;

	if(auxPassenger1->precio < auxPassenger2->precio)
	{
		retorno = -1;
	}
	else if(auxPassenger1->precio > auxPassenger2->precio)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;

}
/**
 * \brief Realiza el ordenamiento de 2 pasajeros por el tipo
 * \param pElement1 el puntero a void del primer elemento
 * \param pElement2 el puntero a void del segundo elemento
 * \return reotrna 0 si son iguales, -1 si es menor el primero y 1 si es mayor
 */
int passenger_sortByType(void* pElement1, void* pElement2)
{
	int retorno;
	Passenger* auxPassenger1 = NULL;
	Passenger* auxPassenger2 = NULL;

	auxPassenger1 = (Passenger*) pElement1;
	auxPassenger2 = (Passenger*) pElement2;

	if(auxPassenger1->tipoPasajero < auxPassenger2->tipoPasajero)
	{
		retorno = -1;
	}
	else if(auxPassenger1->tipoPasajero > auxPassenger2->tipoPasajero)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;

}
/**
 * \brief Realiza el ordenamiento de 2 pasajeros por el codigo de vuelo
 * \param pElement1 el puntero a void del primer elemento
 * \param pElement2 el puntero a void del segundo elemento
 * \return reotrna 0 si son iguales, -1 si es menor el primero y 1 si es mayor
 */
int passenger_sortByFlyCode(void* pElement1, void* pElement2)
{
	Passenger* pPassenger1 = NULL;
	Passenger* pPassenger2 = NULL;
	int retorno;
	int returnCmp;

	pPassenger1 = (Passenger*)pElement1;
	pPassenger2 = (Passenger*)pElement2;
	returnCmp = strncmp(pPassenger1->codigoVuelo,pPassenger2->codigoVuelo,8);

	if(returnCmp < 0)
	{
		retorno = -1;
	}
	else if(returnCmp > 0)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;
}
/**
 * \brief Realiza el ordenamiento de 2 pasajeros por el estado del vuelo
 * \param pElement1 el puntero a void del primer elemento
 * \param pElement2 el puntero a void del segundo elemento
 * \return reotrna 0 si son iguales, -1 si es menor el primero y 1 si es mayor
 */
int passenger_sortByFlyStatus(void* pElement1, void* pElement2)
{
	int retorno;
	Passenger* auxPassenger1 = NULL;
	Passenger* auxPassenger2 = NULL;

	auxPassenger1 = (Passenger*) pElement1;
	auxPassenger2 = (Passenger*) pElement2;

	if(auxPassenger1->estadoVuelo < auxPassenger2->estadoVuelo)
	{
		retorno = -1;
	}
	else if(auxPassenger1->estadoVuelo > auxPassenger2->estadoVuelo)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;
}

