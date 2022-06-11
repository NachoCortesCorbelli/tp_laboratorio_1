#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Passenger.h"
#include "utn.h"
/****************************************************
    Menu:
     1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
     2. Cargar los datos de los pasajeros desde el archivo data.bin (modo binario).
     3. Alta de pasajero
     4. Modificar datos de pasajero
     5. Baja de pasajero
     6. Listar pasajeros
     7. Ordenar pasajeros
     8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
     9. Guardar los datos de los pasajeros en el archivo data.bin (modo binario).
    10. Salir
*****************************************************/
int main()
{
    int option = 0;
    char pathCsv[SIZE_STRING];
    char pathBin[SIZE_STRING];
    char pathNewSavedCsv[SIZE_STRING];
    char pathNewSavedBin[SIZE_STRING];
    int flagTextController = 0;
    int flagBinController = 0;
    int flagSaveCsv = 0;
    int flagSaveBin = 0;
    char seguir;
    int returnLastIdTxt;

    LinkedList* listaPasajeros = ll_newLinkedList();

    returnLastIdTxt = controller_createLastIdTxt("lastId.csv","data.csv");

    do{

    	if(!returnLastIdTxt &&
    	   utn_pedirEntero(&option,
    			   	   	   "\n\tMENU"
    					   "\n1-CARGAR PASAJEROS DESDE EL .CSV"
    					   "\n2-CARGAR PASAJEROS DESDE EL .BIN"
    					   "\n3-ALTA DE PASAJERO"
    			           "\n4-MODIFICAR DATOS DE PASAJERO"
    					   "\n5-BAJA DE PASAJERO"
    					   "\n6-LISTAR PASAJEROS"
    					   "\n7-ORDENAR PASAJEROS"
    					   "\n8-GUARDAR DATOS DEL PASAJERO EN EL ARCHIVO .CSV"
    					   "\n9-GUARDAR DATOS DEL PASAJERO EN EL ARCHIVO .BIN"
    					   "\n10-SALIR"
    					   "\nOpcion: ", "\nERROR\n", 1, 10, 5)==0)
    	{
			switch(option)
			{
				case 1:
					if( (flagTextController == 0 && flagBinController == 0) )
					{
						if( !controller_accessFileByName(pathCsv) &&
							!controller_loadFromText(pathCsv,listaPasajeros))
						{
							printf("\nPASAJEROS CARGADOS\n");
							flagTextController = 1;
						}
						else
						{
							printf("\nNO EXISTE DICHO ARCHIVO PARA CARGAR\n");
						}
					}
					else
					{
						printf("\nYA FUE CARGADO UN ARCHIVO\n");
					}
					break;
				case 2:
					if( (flagTextController == 0 && flagBinController == 0) )
					{
						if( !controller_accessFileByName(pathBin) &&
							!controller_loadFromBinary(pathBin, listaPasajeros))
						{
							flagBinController = 1;
							printf("\nPASAJEROS AGREGADOS\n");
						}
						else
						{
							printf("\nNO HAY ARCHIVO BIN PARA CARGAR\n");
						}
					}
					else
					{
						printf("\nYA FUE CARGADO UN ARCHIVO\n");
					}
					break;
				case 3:
					if( (flagTextController == 1 || flagBinController == 1) &&
						!controller_addPassenger(listaPasajeros))
					{
						printf("\nAGREGADO\n");
					}
					else if( (flagTextController == 0 && flagBinController == 0) &&
							  utn_menuDeseaSeguir(&seguir,
									  	  	  	  "\n¿DESEA INGRESAR PASAJERO SIN HABER CARGADO LA LIST?(s/n)\n",
												  "\nERROR\n",'s','n',5)==0 &&
							!controller_addPassenger(listaPasajeros))
					{
						printf("\nAGREGADO\n");
					}
					else
					{
						printf("\nNO SE CARGO NINGUN ARCHIVO\n");
					}
					break;
				case 4:
					if( ll_isEmpty(listaPasajeros)==0 ||
					   (flagTextController == 1 || flagBinController == 1) )
					{

						if(controller_editPassenger(listaPasajeros)==0)
						{
							printf("\nPASAJERO MODIFICADO");
						}
						else
						{
							printf("\nNO EXISTE EL ID INDICADO");
						}
					}
					else
					{
						printf("\nNO SE CARGO NINGUN PASAJERO\n");
					}
					break;
				case 5:
					if(ll_isEmpty(listaPasajeros) == 0)
					{
						if(flagTextController == 1 || flagBinController == 1)
						{
							controller_removePassenger(listaPasajeros);
						}
						else
						{
							printf("\nNO SE CARGO NINGUN ARCHIVO\n");
						}
					}

					break;
				case 6:
					if(ll_isEmpty(listaPasajeros) == 0)
					{
						if(controller_listPassenger(listaPasajeros) == 0)
						{
							printf("\nMOSTRADOS\n");
						}
					}
					else
					{
						printf("\nLA LISTA ESTA VACIA\n");
					}
					break;
				case 7:
					if(ll_isEmpty(listaPasajeros)==0 &&
					   flagTextController == 1 &&
					   !controller_sortPassenger(listaPasajeros))
					{
						printf("\nORDENADOS\n");
					}
					else
					{
						printf("\nNO SE PUDO ORDENAR\n");
					}
					break;
				case 8:
					if(flagTextController == 1 &&
					   !utn_pedirCadena(pathNewSavedCsv, SIZE_STRING,
									   "\nINGRESE EL NOMBRE DEL CSV A SER GUARDADO: ",
									   "\nERROR\n", 3, SIZE_STRING, 5)&&
					   !controller_saveAsText(pathNewSavedCsv,listaPasajeros))
					{
						printf("\nPASAJEROS GUARDADOS\n");
						flagSaveCsv = 1;
					}
					else
					{
						printf("\nNO SE CARGO NINGUN ARCHIVO\n");
					}
					break;
				case 9:
					if((flagTextController == 1 || flagBinController == 1 )&&
						!utn_pedirCadena(pathNewSavedBin, SIZE_STRING,
										"\nINGRESE EL NOMBRE DEL BIN A SER GUARDADO: ",
										"\nERROR\n", 3, SIZE_STRING, 5)&&
					   !controller_saveAsBinary(pathNewSavedBin,listaPasajeros))
					{
						printf("\nPASAJEROS GUARDADOS\n");
						flagSaveBin = 1;
					}
					else
					{
						printf("\nNO SE CARGO NINGUN ARCHIVO\n");
					}
					break;
				case 10:
					if(flagSaveBin == 1 && flagSaveCsv == 1)
					{
						printf("\nFINALIZANDO...\n");
					}
					else
					{
						printf("\n*****************************************************"
							   "\n****-------------------ALERTA--------------------****"
							   "\n****GUARDE EL ARCHIVO BIN Y EL CSV ANTES DE SALIR****"
							   "\n*****************************************************\n");
						option = 0;
					}
					break;
			}
    	}
    }while(option != 10);
    return 0;
}

