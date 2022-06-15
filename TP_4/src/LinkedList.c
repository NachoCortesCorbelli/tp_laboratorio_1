#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = (LinkedList*)malloc(sizeof(this));//CONSTRUYE LA LISTA EN MEMORIA
    if(this != NULL)
    {
    	this->pFirstNode = NULL;//COMO RECIEN SE CREA LA LISTA NO APUNTA A NINGUN NODO()
    	this->size = 0;//SE SETEA EL TAMAÑO EN 0
    }
    return this;//RETORNA NULL SI NO SE PUDO CONTRUIR LA LISTA
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(this->size >= 0)//VERIFICA QUE EL TAMAÑO(SIZE) DEL PUNTERO A LA LISTA SEA MAYOR O IGUAL A 0
    	{
    		returnAux = this->size;//DE SER VALIDA, RETORNA EL TAMAÑO DE LA LISTA POR RETORNO
    	}
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{

	Node* pAuxNode = NULL;//EL NODO A SER RETORNADO
	if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))//VALIDACION
	{
		pAuxNode = this->pFirstNode;//TODA LISTA ENLAZADA TIENE QUE COMENZAR DESDE EL PRINCIPIO(LL->pFirstNode), LA DIRECCION DE MEMORIA DEL PRIMER NODO
		for(int i = 0; i < nodeIndex ;i++)//EL BUCLE QUE LLEGA HASTA EL NODO ANTERIOR DEL QUE SE NECESITA
		{
			if(pAuxNode->pNextNode != NULL)//VERIFICA QUE EL NODO SIGUIENTE(EL QUE SE QUIERE OBTENER) ES DECIR LA DIRECCION DE MEMORIA NO SEA NULA
			{
				pAuxNode = pAuxNode->pNextNode;//AL ENCONTRARLO DEVUELVE LA DIRECCION DE MEMORIA DEL NODO POR RETORNO
			}
		}
	}
	return pAuxNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{

    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{

	Node* pNode = NULL;
	Node* pPreNode = NULL;
    int retorno = -1;
    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this) ) // INDICE DEL NODO PUEDE SER IGUAL AL SIZE DE LA LISTA PORQUE PODRIA AGREGARSE AL FINAL DE LA MISMA
    {
    	pNode = (Node*) malloc(sizeof(Node));//SE CONTRUYE EL NODO PARA SER AGREGADO
    	if(pNode != NULL)
    	{
        	if(nodeIndex == 0)//SI EL INDEX ES 0 QUIERE DECIR QUE ES EL PRIMER NODO
        	{
        		pNode->pNextNode = this->pFirstNode;//GUARDO LA DIRECCION DE MEMORIA DEL NODO QUE ESTABA ENLAZADO PRIMERO EN LA LL
        		this->pFirstNode = pNode;//DESPUES DE GUARDAR EL NODO AL QUE APUNTABA LA LINKED LIST EN EL MISMO, LE PASO LA DIR DE MEMORIA DEL NODO A SER AGREGADO
        	}
        	else
        	{
        		pPreNode = getNode(this, nodeIndex - 1);//SI EL NODO NO ES EL DEL PRINCIPIO, SIEMPRE VA A HABER UN NODO UNA POSICION ANTES(ESTE EN EL MEDIO O EN EL FINAL)
        		if(pPreNode !=NULL)
        		{
        			pNode->pNextNode = pPreNode->pNextNode;//GUARDA LA DIRECCION DE MEMORIA DEL NODO SIGUIENTE DEL NODO ANTERIOR A SER AGREGADO
        			pPreNode->pNextNode = pNode;//AL NODO ANTERIOR SE LE GUARDA LA DIRECCION DEL NODO A SER AGREGADO
        		}
        	}
        	pNode->pElement = pElement;//SE ENLAZA LA DIRECCION DE MEMORIA DEL ELEMENTO AL NODO
    		this->size++;//SE AGREGA EN 1 EL TAMANO DE LA LISTA
    		retorno = 0;
    	}
    }
    return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
	int retorno = -1;
	int returnNode;
	if(this != NULL)
	{
		returnNode = addNode(this, ll_len(this), pElement);//AGREGA UN ELEMENTO A LA LISTA QUE EN ESTE CASO SIEMPRE VA A SER EL ULTIMO
		if(!returnNode)
		{
			retorno = 0;//SI PUDO AGREGARLO DEVUELVE 0
		}
	}
    return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 * DEVUELVE EL pElement del NODO
 */
void* ll_get(LinkedList* this, int index)
{
	Node* pNode = NULL;
    void* returnAux = NULL;//RETORNA PUNTERO A VOID PORQUE NO SE DE QUE TIPO ES EL ELEMENTO. SE ABSTRAE
    if(this != NULL && index >= 0 && index < ll_len(this))//VERIFICACIONES
    {
    	pNode = getNode(this, index);//OBTENGO EL NODO EN LA POSICION A OBTENER
    	if(pNode != NULL)
    	{
    		returnAux = pNode->pElement;//SI PUDO OBTENERLO RETORNA LA DIRECCIOND DE MEMORIA DEL MISMO
    	}
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
	Node* pAuxNode = NULL;
    int returnAux = -1;
    if(this != NULL && index >= 0 && index < ll_len(this))//VERIFICACIONES
    {
    	pAuxNode = getNode(this, index);//OBTENGO EL NODO DE LA POSICION NECESITADA
    	if(pAuxNode != NULL)
    	{
    		//DEBERIA HACER UN FREE AL ELEMENTO QUE ESTABA ENLAZADO EL NODO??¡¡¡NO!!!NO HACER FREE A ELEMENTOS
    		pAuxNode->pElement = pElement;//LE PASO LA DIRECCION DE MEMORIA DEL ELEMENTO A SER AGREGADO(PASADO POR PARAMETRO) EN EL NODO
    		returnAux = 0;
    	}
    }
    return returnAux;
}


/** \brief Elimina un (elemento?)NODO de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
	Node* pNode = NULL;
	Node* pPreviousNode = NULL;
    int returnAux = -1;
    if(this != NULL && index >= 0 && index < ll_len(this))//VALIDACIONES
    {
    	pNode = getNode(this, index);//OBTENGO EL NODO A SER ELIMINADO
    	if(pNode != NULL)
    	{
    		if(index == 0)
    		{
    			this->pFirstNode = pNode->pNextNode;//SI ES EL PRIMER NODO HAY QUE CORRIGIR EL LA REFERENCIA DEL PRIMER NODO DE LA LL
    		}
    		else
    		{
    			pPreviousNode = getNode(this,(index-1));//SI NO ES EL PRIMERO HAY QUE TRAER EL ANTERIOR
    			if(pPreviousNode != NULL)
    			{
					pPreviousNode->pNextNode = pNode->pNextNode;//SE LE PASA LA REFERENCIA DEL NODO SIGUIENTE AL QUE VA A SER ELIMINADO
    			}
    		}
    		free(pNode);//SE LIBERA DE LA MEMORIA
    		this->size--;//SE REDUCE LA LISTA
    		returnAux = 0;
    	}
    }
    return returnAux;
}


/** \brief Elimina todos los (elementos?)NODOS de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int length;

    if(this != NULL && ll_len(this) > 0)//VERIFICAS
    {
    	length = ll_len(this) - 1;//OBTENES EL ULTIMO NODO DE LA LISTA
    	for(int i = length; i >= 0; i--)//EL BUCLE DESDE EL ULTIMO NODO
    	{
    		if(!ll_remove(this, i))//SE VAN ELIMINANDO
    		{
    			returnAux = 0;
    		}
    	}
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)//VERIFICACION
    {
    	if(!ll_clear(this))//SE BORRAN TODOS LOS NODOS DE LA LISTA
    	{
    		free(this);//SE LIBERA LA LISTA DE MEMORIA
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
	void* pAuxElement;
    int returnAux = -1;
    int length;
    int i;
    if(this != NULL)//VERIFICACION
    {
    	length = ll_len(this);//TAMANIO DE LA LISTA
    	for(i = 0; i < length; i++)//BUCLE HASTA EL FINAL
    	{
    		pAuxElement = ll_get(this, i);//OBTENGO EL NODO EN CADA ITERACION
			if(pAuxElement == pElement)//CHEQUEA LA DIRECCION DE MEMORIA DEL ELEMENTO PASADO POR PARAMETRO CON LA ENLAZADA
			{
				returnAux = i;//DE ENCONTRARLO RETORNA LA POSICION Y ROMPE BUCLE
				break;
			}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)//VERIFICA
    {
		returnAux = 0;//LA LISTA ESTA CREADA
    	if(ll_len(this) == 0)
    	{
    		returnAux = 1;//LA LISTA TIENE 0 ELEMENTOS
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this != NULL && index >= 0 && index <= ll_len(this))//VERIFICACIONES
    {
    	if(!addNode(this, index, pElement))//AGREGA EL ELEMENTO PASADO POR PARAMETRO EN LA UBICACION TAMBIEN PASADA POR PARAMETRO
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* pElement = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this))//VERIFICACIONES
    {
		pElement = ll_get(this, index); //OBTENGO EL ELEMENTO EN LA POSICION PASADA POR PARAMENTRO
		ll_remove(this, index);//BORRO EL NODO DE LA LISTA ENLAZADA
    }
    return pElement;//LO RETORNO
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)//VERIFICACIONES
    {
    	returnAux = 0;
    	if(ll_indexOf(this, pElement) != -1)//LE PASO EL ELEMENTO PASADO POR PARAMETRO
    	{
    		returnAux = 1;//SI ME PUDO RETORNAR DISTINTO DE -1 SIGNIFICA QUE ESTA EN LA LISTA
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int length;
    void* pAuxElement = NULL;

    if(this != NULL && this2 != NULL) //VERIFICACIONES
    {
    	returnAux = 1;//LAS LISTA NO SON NULAS Y SETEO EL RETORNO EN 1
    	length = ll_len(this2);//EL TAMANIO DE LA LISTA 1
		for(int i = 0; i < length; i++)//BUCLE DE LA LISTA 2
		{
			pAuxElement = ll_get(this2, i);//OBTENGO ELEMENTO DE LA LISTA 2
			if( pAuxElement != NULL &&
				ll_contains(this, pAuxElement)==0)//VERIFICO Y CHEQUEO QUE EL ELEMENTO DE LA LISTA 2 ¡NO! ESTA EN LA LISTA 1
			{
				returnAux = 0;//RETORNO 0 YA QUE NO ESTAN TODOS LOS ELEMENTOS LOS ELEMENTO CONTENIDOS
				break;//ROMPO BUCLE
			}
		}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la lista es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* pElement = NULL;
    int length;
    int returnAddNode;

    if( this != NULL)
    {
    	length = ll_len(this);
    	if(from >= 0 && from < length && to <= length && from < to)//AGREGAR IF FROM TO
    	{
        	cloneArray = ll_newLinkedList();//CREO UNA NUEVA LINKED LIST
        	if(cloneArray != NULL)
        	{
        		for(int i = from; i <= to;i++)//REALIZO EL BUCLE DESEDE Y HASTA LAS POSICIONES PASADAS POR PARAMETRO
        		{
        			pElement = ll_get(this, i);//OBTENGO EL ELEMENTO
        			if(pElement != NULL)
        			{
        				returnAddNode = addNode(cloneArray, i, pElement);//AGREGO LOS NODOS A LA NUEVA LISTA
        				if(returnAddNode != 0 &&
    					   !ll_deleteLinkedList(cloneArray))//EN CASO DE NO PODER AGREGAR LOS NODOS SE BORRA LA NUEVA LISTA
        				{
    						cloneArray = NULL;
    						break;//SE ROMPE EL BUCLE
        				}
        			}
        		}
        	}
    	}
    }
    return cloneArray;//RETORNA LA NUEVA LISTA
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this != NULL)
    {
    	cloneArray = ll_subList(this, 0, ll_len(this));//CLONA TODA LA LISTA ENLAZADA
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
	void* pElement1 = NULL;
	void* pElement2 = NULL;
	int returnAux = -1;
	int returnPfunc;
	int flagSwap;
	int length;

    if(this != NULL && pFunc != NULL && ll_len(this) > 1 && (order == 0 || order == 1))//VERIFICACIONES
    {
    	//REALIZO ALGORITMO DE ORDENAMIENTO
    	length = ll_len(this) - 1;
    	do
    	{
    		flagSwap = 0;//FLAG DE ORDENAMIENTO
			for(int i = 0; i < length; i++)
			{
				pElement1 = ll_get(this,i);//OBTENGO EL PRIMER ELEMENTO
				pElement2 = ll_get(this,i + 1);//OBTENGO EL SIGUIENTE ELEMENTO
				returnPfunc = pFunc(pElement1,pElement2);//UTILIZO EL PUNTERO A LA FUNCION(QUE SE ABSTRAE DEL TIPO DE ORDENAMIENTO)
				if((order == 1 && returnPfunc ==  1) ||
				   (order == 0 && returnPfunc == -1))//DE ACUERDO AL ORDEN ASCENDENTE O DESCENDENTE Y EL TIPO DE ORDENAMIENTO
				{
					//SE REALIZA EL SWAPEO
					ll_set(this, i, pElement2);//AGREGO EL ELEMENTO EN LA POSICION INDICADA
					ll_set(this, i+1, pElement1);
					flagSwap = 1;
				}
			}
    	}while(flagSwap);
    	returnAux = 0;
    }
    return returnAux;
}
