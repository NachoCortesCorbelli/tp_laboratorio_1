/*
 * utn.c
 *
 *  Created on: 10 sep. 2021
 *      Author: nacho
 */

#include "utn.h"

static int obtengoCadena(char pCadena[], int longitud);
static int obtengoEntero(int *pEntero);
static int obtengoCaracter(char* pCadena);
static int obtengoFloat(float* pFloat);
static int obtengoNombreApellido(char pCadena[],int longitud);
static int obtengoLocalidad(char pCadena[],int longitud);
static int obtengoDescripcion(char* cadena,int longitud);
static int obtengoDni(char* pResultado, int longitud);
static int obtengoCuit(char* pResultado, int tamano);
static int esNumerica(char pCadena[], int longitud);
static int esFlotante(char pCadena[], int longitud);
static int esCaracter(char pCadena[], int longitud);
static int esNombreApellido(char pCadena[], int longitud);
static int esUnCuitValido(char* cadena,int limit);
static int esLocalidad(char pCadena[], int longitud);
static int esDireccion(char pCadena[], int longitud);
static int esDescripcion(char* cadena,int longitud);
/**
 * \brief Verifica si la cadena ingresada es una descripcion valida
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int esDescripcion(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if(cadena[i] != '.' && cadena[i] != ' ' && (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ) && (cadena[i] < '0' || cadena[i] > '9' ) )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
static int esDireccion(char pCadena[], int longitud)
{
	int retorno;
	int contadorEspacios;
	int indexDireccion;
	int contadorNumeros;
	int flagNumeros;

	contadorEspacios = 0;
	contadorNumeros = 0;
	flagNumeros = 0;
	retorno = -1;

	if(pCadena != NULL &&
	   longitud > 0)
	{
		for(int i = 0;i < longitud; i++)
		{
			if(pCadena[i] != '\0' ||
			   pCadena[i] == 0)
			{

				if(( (i < 3 && (pCadena[i] >= 'A' && pCadena[i] <= 'Z'))||
				     (i < 3 && (pCadena[i] >= 'a' && pCadena[i] <= 'z'))) ||
			      (( (i >= 3 || contadorEspacios < 4) &&(pCadena[i] >= 'a' && pCadena[i] <= 'z')) ||
				   ( (i == indexDireccion)&&(pCadena[i] >= 'A' &&(pCadena[i] <= 'Z')))||
				   ( (i == indexDireccion)&&(pCadena[i] >= 'a' &&(pCadena[i] <= 'z'))))
				     )
				{
					//printf("\nVALIDO EN: %c",pCadena[i]);
					retorno = 1;
				}
				else if( (i > 2 && pCadena[i] == ' ') &&
						 (contadorEspacios < 4) )
				{
					indexDireccion = i+1;
					contadorEspacios++;
					//printf("\nVALIDO EN: %c",pCadena[i]);
					retorno = 1;
				}
				else if( (i > 3 && (pCadena[i] >= '1' && pCadena[i] <= '9')) &&
						 (contadorNumeros < 5) )
				{
					contadorNumeros++;
					flagNumeros = 1;
					//printf("\nVALIDO EN: %c",pCadena[i]);
					retorno = 1;
				}
				else if(flagNumeros == 0)
				{
					retorno = 0;
					break;
				}
			}
		}
	}

	return retorno;
}

static int esLocalidad(char pCadena[], int longitud)
{
	int retorno;
	int contadorEspacios;
	int indexLocalidad;

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
			      (( (i > 0 || contadorEspacios < 3) &&(pCadena[i] >= 'a' && pCadena[i] <= 'z')) ||
				   ( (i == indexLocalidad)&&(pCadena[i] >= 'A' &&(pCadena[i] <= 'Z')))||
				   ( (i == indexLocalidad)&&(pCadena[i] >= 'a' &&(pCadena[i] <= 'z')))) )
				{
					retorno = 1;
				}
				else if( (i > 2 && pCadena[i] == ' ') &&
						 (contadorEspacios < 3) )
				{
					indexLocalidad = i+1;
					contadorEspacios++;
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

static int esUnCuitValido(char* cadena,int limit)
{
	int retorno;
	int notValid = 0;
	if(cadena != NULL && limit > 11)
	{
		for(int indice=0; indice<=limit && cadena[indice] != '\0';indice++)
		{
			if(indice == 0 && cadena[indice]!='2')
			{
				//printf("\nError en la posicion 0");
				notValid++;
			}
			else if(indice == 1 &&(
					cadena[indice]!='0' &&
					cadena[indice]!='3' &&
					cadena[indice]!='4' &&
					cadena[indice]!='7'))
			{
				//printf("\nError en la posicion 1");
				notValid++;
			}
			else if(indice > 1 && (cadena[indice]<'0' || cadena[indice]>'9') )
			{
				//printf("\nError en posidcion superior");
				notValid++;
			}
		}
		if(notValid == 0)
		{
			retorno = 1;
		}
		else
		{
			retorno = 0;
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
static int esNombreApellido(char pCadena[], int longitud)
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
				   ( (i == indexSegundoNombreApellido)&&(pCadena[i] >= 'A' &&(pCadena[i] <= 'Z')))||
				   ( (i == indexSegundoNombreApellido)&&(pCadena[i] >= 'a' &&(pCadena[i] <= 'z')))) )
				{
					retorno = 1;
				}
				else if( (i > 2 && pCadena[i] == ' ') &&
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
/**
 * \brief Funcion estática que verifica si la cadena recibida es solamente numerica
 * \param pCadena La cadena de caracteres recibida
 * \param longitud El tamaño de la cadena de caracteres recibida
 * \return Devuelve un 1 en caso de ser verdadero y un 0 en caso de falso
 * -1 si no pudo realizar la verificacion
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
			if( pCadena[0] == '\0' ||
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
 * @brief Funcion estática que verifica si la cadena recibida
 * es un numero flotante
 * @param pCadena La cadena de caracteres recibida
 * @param longitud El tamaño de la cadena recibida
 * @return Devuelve un 1 en caso de ser verdadero y un 0 en caso de falso
 * -1 si no pudo realizar la verificacion
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
 * @brief Función estática que valida si la cadena recibida
 * es un caracter
 * @param pCadena La cadena de caracteres recibida
 * @param longitud El tamaño de la cadena de caracteres
 * @return Devuelve un 1 en caso de ser verdadero y un 0 en caso de falso
 * -1 si no pudo realizar la verificacion
 */
static int esCaracter(char pCadena[], int longitud)
{
	int retorno;

	retorno = -1;

	if(pCadena != NULL &&
	   longitud > 0)
	{
		if(strlen(pCadena) == 1)
		{
			if((pCadena[0] != '\0') &&
			   (pCadena[0] >= '0' && pCadena[0] <= '9') &&
			   (pCadena[1] == '\0') )
			{
				retorno = 0;
			}
			else
			{
				retorno = 1;
			}
		}

	}

	return retorno;
}

/**
 * \brief Funcion que obtiene una cadena de caracteres
 * \param pCadena puntero a la cadena de caracteres
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
 * \brief Funcion que obtiene la cadena de caracteres como nombre o apellido
 * \param pCadena puntero a la cadena de caracteres
 * \param longitud El tamaño de la cadena de caracteres
 * \return Devuelve 0 en caso de no tener problemas o -1 si no pudo
 */
static int obtengoNombreApellido(char pCadena[],int longitud)
{

	int retorno;
	int firstUpperCase;
	int secondUpperCase;
	int bufferLen;
	char bufferString[SIZE_STRING];

	retorno = -1;

	if(pCadena != NULL &&
	   obtengoCadena(bufferString,SIZE_STRING) == 0 &&
	   esNombreApellido(bufferString,SIZE_STRING) == 1)
	{
		firstUpperCase= toupper(bufferString[0]);
		bufferLen = strlen(bufferString);
		for(int i = 0; i < bufferLen;i++)
		{
			if(firstUpperCase != bufferString[0])
			{
				bufferString[0] = firstUpperCase;
			}
			else if(bufferString[i] == ' ')
			{
				secondUpperCase = toupper(bufferString[i+1]);
				if(secondUpperCase != bufferString[i+1])
				{
					bufferString[i+1] = secondUpperCase;
				}
			}
		}
		strncpy(pCadena,bufferString,SIZE_STRING);
		retorno = 0;
	}

	return retorno;

}
static int obtengoCuit(char* pResultado, int tamano)
{
    int retorno = -1;
    char buffer[SIZE_STRING];

    if(pResultado != NULL)
    {
    	if(	obtengoCadena(buffer,SIZE_STRING) == 0 &&
			strnlen(buffer,SIZE_STRING) < tamano &&
    		esUnCuitValido(buffer,SIZE_STRING) == 1 )
    	{
    		strncpy(pResultado,buffer,SIZE_STRING);
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief Obtiene un string valido como DNI
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
static int obtengoDni(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[SIZE_STRING];

    if(pResultado != NULL)
    {
    	if(	obtengoCadena(buffer,SIZE_STRING) == 0 &&
			strnlen(buffer,SIZE_STRING) < longitud &&
    		esNumerica(buffer,SIZE_STRING) == 1 )
    	{
    		strncpy(pResultado,buffer,SIZE_STRING);
			retorno = 0;
		}
    }
    return retorno;
}

/**
 * \brief Obtiene un string valido como descripcion
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
static int obtengoDescripcion(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[SIZE_STRING];

    if(pResultado != NULL)
    {
    	if(	obtengoCadena(buffer,SIZE_STRING)==0 &&
    		esDescripcion(buffer,SIZE_STRING) &&
			strnlen(buffer,SIZE_STRING)<longitud)
    	{
    		strncpy(pResultado,buffer,SIZE_STRING);
			retorno = 0;
		}
    }
    return retorno;
}
static int obtengoLocalidad(char pCadena[],int longitud)
{

	int retorno;
	int firstUpperCase;
	int secondUpperCase;
	int thirdUpperCase;
	int space;
	int bufferLen;
	char bufferString[SIZE_STRING];

	retorno = -1;
	space = 0;

	if(pCadena != NULL &&
	   obtengoCadena(bufferString,SIZE_STRING) == 0 &&
	   esLocalidad(bufferString, SIZE_STRING) == 1)
	{
		firstUpperCase= toupper(bufferString[0]);
		bufferLen = strlen(bufferString);
		for(int i = 0; i < bufferLen;i++)
		{
			if(firstUpperCase != bufferString[0])
			{
				bufferString[0] = firstUpperCase;
			}
			else if(bufferString[i] == ' ')
			{
				space++;
				if(space == 1)
				{
					secondUpperCase = toupper(bufferString[i+1]);
					if(secondUpperCase != bufferString[i+1])
					{
						bufferString[i+1] = secondUpperCase;
					}
				}
				else if(space == 2)
				{
					thirdUpperCase = toupper(bufferString[i+1]);
					if(thirdUpperCase != bufferString[i+1])
					{
						bufferString[i+1] = thirdUpperCase;
					}
				}
			}
		}
		strncpy(pCadena,bufferString,SIZE_STRING);
		retorno = 0;
	}

	return retorno;

}

static int obtengoDireccion(char pCadena[],int tamano)
{

	int retorno;
	int firstUpperCase;
	int secondUpperCase;
	int thirdUpperCase;
	int space;
	int bufferLen;
	char bufferString[SIZE_STRING];

	retorno = -1;
	space = 0;

	if(pCadena != NULL &&
	   obtengoCadena(bufferString,SIZE_STRING) == 0 &&
	   esDireccion(bufferString, SIZE_STRING) == 1)
	{
		firstUpperCase= toupper(bufferString[0]);
		bufferLen = strlen(bufferString);

		for(int i = 0; i < bufferLen;i++)
		{
			if(firstUpperCase != bufferString[0])
			{
				bufferString[0] = firstUpperCase;
			}
			else if(bufferString[i] == ' ')
			{
				space++;
				if(space == 1)
				{
					secondUpperCase = toupper(bufferString[i+1]);
					if(secondUpperCase != bufferString[i+1])
					{
						bufferString[i+1] = secondUpperCase;
					}
				}
				else if(space == 2)
				{
					thirdUpperCase = toupper(bufferString[i+1]);
					if(thirdUpperCase != bufferString[i+1])
					{
						bufferString[i+1] = thirdUpperCase;
					}
				}
			}

		}

		strncpy(pCadena,bufferString,SIZE_STRING);
		retorno = 0;
	}

	return retorno;

}

/**
 * \brief Función estática que obtiene un numero entero
 * \param pBufferInt el puntero a entero
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
 * @brief Función estática que obtiene un numero flotante
 * @param pFloat puntero a numero flotante
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
 * @brief Función estática que obtiene un carácter
 * @param pChar puntero a carácter
 * @return Devuelve 0 en caso de no tener problemas y -1 de no poder
 */
static int obtengoCaracter(char* pChar)
{
	int retorno;
	char bufferChar;
	char bufferString[SIZE_STRING];

	retorno = -1;

	if(pChar != NULL &&
	   obtengoCadena(bufferString,SIZE_STRING) == 0 &&
	   esCaracter(bufferString, SIZE_STRING) == 1)
	{
		bufferChar = bufferString[0];
		*pChar = bufferChar;
		retorno = 0;
	}

	return retorno;

}
/**
 * @brief Función que pide un carácter al usuario
 * @param pChar puntero al caracter
 * @param mensaje el mensaje a mostrar
 * @param mensajeError el mensaje de error a mostrar
 * @param minimo el caracter minimo aceptado
 * @param maximo el caracter maximo aceptado
 * @param reintentos el numero de reintentos
 * @return retorna 0 en caso de poder realizar la función
 * y -1 en caso de Error
 */
int utn_pedirCaracter(char* pChar,char mensaje[],char mensajeError[], char minimo, char maximo, int reintentos)
{
	int retorno;
	char bufferChar;

	retorno = -1;

	if(pChar != NULL &&
	   mensaje != NULL &&
	   mensajeError != NULL &&
	   minimo <= maximo &&
	   reintentos >= 0)
	{

		do
		{
			printf("%s",mensaje);
			if(obtengoCaracter(&bufferChar)==0 &&
			   bufferChar >= minimo &&
			   bufferChar <= maximo)
			{
				*pChar = bufferChar;
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
 * \brief Funcion que pide un entero al usuario
 * \param pEntero Puntero​​ a entero
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError El mensaje de error a ser a mostrado
 * \param minimo El minimo numero que se puede tomar
 * \param maximo El maximo numero que se puede tomar
 * \param reintentos La cantidad de reintentos posibles
 * \return retorna 0 en caso de poder realizar la función
 * y -1 en caso de Error
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
 * \brief Funcion que pide un flotante al usuario
 * \param pFloat puntero a float
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError El mensaje de error a ser a mostrado
 * \param minimo El minimo flotante que se puede tomar
 * \param maximo El maximo flotante que se puede tomar
 * \param reintentos La cantidad de reintentos posibles
 * \return retorna 0 en caso de poder realizar la función
 * y -1 en caso de Error
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
/**
 * \brief Funcion que pide una cadena al usuario
 * \param pCadena puntero a la cadena
 * \param tamano  El tamaño de la cadena
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError El mensaje de error a ser a mostrado
 * \param minimo El minimo de caracteres que el usuario puede escribir
 * \param maximo El maximo de caracteres que el usuario puede escribir
 * \param reintentos La cantidad de reintentos posibles
 * \return retorna 0 en caso de poder realizar la función
 * y -1 en caso de Error
 */
int utn_pedirCadena(char* pCadena,int tamano,char mensaje[],char mensajeError[], int minimo, int maximo, int reintentos)
{
	int retorno;
	char bufferCadena[SIZE_STRING];

	retorno = -1;

	if(pCadena != NULL &&
	   mensaje != NULL &&
	   mensajeError != NULL &&
	   minimo <= maximo &&
	   reintentos >= 0)
	{

		do
		{
			printf("%s",mensaje);
			if(obtengoCadena(bufferCadena, SIZE_STRING) ==0 &&
			   strlen(bufferCadena) >= minimo &&
			   strlen(bufferCadena) <= maximo)
			{
				strncpy(pCadena,bufferCadena,tamano);
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
int utn_pedirCuit(char* pResultado, int tamano, char* mensaje, char* mensajeError, int retry)
{
	int retorno = -1;
	char bufferString[SIZE_STRING];

	if(	mensaje != NULL &&
		mensajeError != NULL &&
		pResultado != NULL &&
		retry >= 0 &&
		tamano > 10)
	{
		do
		{
			printf("%s",mensaje);
			if( obtengoCuit(bufferString,SIZE_STRING) == 0
				//&&
				//obtengoCadena(bufferString,SIZE_STRING) == 0 &&
				//strnlen(bufferString,sizeof(bufferString)-1) <= limite &&
				//esUnCuitValido(bufferString,limite) != 0
				)
			{
				retorno = 0;
				strncpy(pResultado,bufferString,tamano);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				retry--;
			}
		}while(retry >= 0);

	}

	return retorno;
}
int utn_pedirLocalidad(char* pLocalidad,int tamano,char mensaje[],
					char mensajeError[], int minimo, int maximo, int reintentos)
{
	int retorno;
	int upperCase;

	char bufferCadena[SIZE_STRING];
	retorno = -1;

	if(pLocalidad != NULL && tamano > 0 && tamano <= SIZE_STRING &&
	   mensaje != NULL && mensajeError != NULL &&
	   minimo > 0 && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			if(obtengoLocalidad(bufferCadena, SIZE_STRING) ==0 &&
			   strlen(bufferCadena) >= minimo &&
			   strlen(bufferCadena) <= maximo)
			{
				upperCase = toupper(bufferCadena[0]);
				if(upperCase != bufferCadena[0])
				{
					bufferCadena[0] = upperCase;
				}
				strncpy(pLocalidad,bufferCadena,tamano);
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
int utn_pedirDireccion(char* pDireccion,int tamano,char mensaje[],
					   char mensajeError[], int minimo, int maximo, int reintentos)
{
	int retorno;

	char bufferCadena[SIZE_STRING];
	retorno = -1;

	if(pDireccion != NULL && tamano > 0 && tamano <= SIZE_STRING &&
	   mensaje != NULL && mensajeError != NULL &&
	   minimo > 0 && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			if(obtengoDireccion(bufferCadena, SIZE_STRING) ==0 &&
			   strlen(bufferCadena) >= minimo &&
			   strlen(bufferCadena) <= maximo)
			{
				strncpy(pDireccion,bufferCadena,tamano);
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
 * \brief Funcion que pide un nombre o apelliro
 * \param pNombre puntero a la cadena
 * \param tamano  El tamaño de la cadena
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError El mensaje de error a ser a mostrado
 * \param minimo El minimo de caracteres que el usuario puede escribir
 * \param maximo El maximo de caracteres que el usuario puede escribir
 * \param reintentos La cantidad de reintentos posibles
 * \return retorna 0 en caso de poder realizar la función
 * y -1 en caso de Error
 */
int utn_pedirNombreApellido(char* pNombre,int tamano,char mensaje[],
					char mensajeError[], int minimo, int maximo, int reintentos)
{
	int retorno;
	int upperCase;

	char bufferCadena[SIZE_STRING];
	retorno = -1;

	if(pNombre != NULL && tamano > 0 && tamano <= SIZE_STRING &&
	   mensaje != NULL && mensajeError != NULL &&
	   minimo > 0 && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			if(obtengoNombreApellido(bufferCadena, SIZE_STRING) ==0 &&
			   strlen(bufferCadena) >= minimo &&
			   strlen(bufferCadena) <= maximo)
			{
				upperCase = toupper(bufferCadena[0]);
				if(upperCase != bufferCadena[0])
				{
					bufferCadena[0] = upperCase;
				}
				strncpy(pNombre,bufferCadena,tamano);
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
 * \brief Función que pide una respuesta para terminar o seguir
 * \param pOpcion puntero a char
 * \param mensaje el mensaje a mostar
 * \param mensajeError el mensaje de error a mostrar
 * \param opcionSeguir la opcion que continua con el programa
 * \param opcionNoSeguir la opcion para salir del programa
 * \param reintentos la cantidad de reintentos
 * \return retorna 0 en caso de ingresar la opcion para seguir,
 * 1 en caso de ingresar la opcion para salir y -1 en caso de Error
 */
int utn_menuDeseaSeguir(char* pOpcion,char mensaje[],char mensajeError[], char opcionSeguir, char opcionNoSeguir, int reintentos)
{
	int retorno;
	char bufferChar;

	retorno = -1;

	if(pOpcion != NULL &&
	   mensaje != NULL &&
	   mensajeError != NULL &&
	   reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			if(obtengoCaracter(&bufferChar)==0 &&
			   (bufferChar == opcionSeguir ||
			    bufferChar == opcionNoSeguir))
			{
				if(bufferChar == opcionSeguir)
				{
					retorno = 0;
				}
				else if(bufferChar == opcionNoSeguir)
				{
					retorno = 1;
				}
				*pOpcion = bufferChar;
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
 * \brief Solicita una descripcion al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el numero flotante y -1 si no
 *
 */
int utn_pedirDescripcion(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(obtengoDescripcion(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}
/**
 * \brief Solicita un DNI al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el numero flotante y -1 si no
 *
 */
int utn_pedirDni(char* pResultado, int longitud,char* mensaje, char* mensajeError, int limite, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	if(pResultado != NULL && longitud > 0 &&
	   mensaje != NULL && mensajeError != NULL &&
	   limite > 0 && reintentos >= 0)
	{
		do
		{
			reintentos--;
			printf("%s",mensaje);
			if(obtengoDni(bufferString,sizeof(bufferString)) == 0 &&
			   strnlen(bufferString,sizeof(bufferString)) <= limite)
			{
				strncpy(pResultado,bufferString,longitud);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);
			}
		}while(reintentos>=0);
	}
	return retorno;
}








