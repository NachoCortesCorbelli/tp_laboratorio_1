/*
 * ArrayPassenger.h
 *
 *  Created on: 13 may. 2022
 *      Author: nacho
 */

#ifndef ARRAYPASSENGER_H_
#define ARRAYPASSENGER_H_

#define QTY_PASSANGER 2000

#define TRUE 1
#define FALSE 0

#define ACTIVO 1
#define FINALIZADO 2
#define CANCELADO 3

#define TURISTA 1
#define PREMIUM 2
#define BUSINESS 3
#define EJECUTIVO 4

#define ASCENDENTE 1
#define DESCENDENTE 0

typedef struct
{
	int id;
	char name[51];
	char lastName[51];
	float price;
	char flycode[10];
	int typePassenger;//1-TURISTA,2-PREMIUM,3-BUSINESS,4-EJECUTIVO
	int statusFlight;//1-ACTIVO,2-FINALIZADO,3-CANCELADO
	int isEmpty;
}ePassenger;

int isArrayPassengerEmpty(ePassenger* list, int len);
int findEmptyPassenger(ePassenger* list, int len);
int menuInformes(ePassenger* list, int len);
int menuPassenger(ePassenger* list, int len,int* pId);
int initPassengers(ePassenger* list, int len);
int registerPassenger(ePassenger* list, int len,int* pId);
int modifyPassenger(ePassenger* list, int len,int id);
int removePassenger(ePassenger* list, int len, int id);
int addPassenger(ePassenger* list, int len, int id,
				 char name[],char lastName[],
				 float price,int typePassenger,
				 char flycode[],int statusFlight);
int findPassengerById(ePassenger* list, int len,int id);
int isValidId(ePassenger* list, int len, int id);
int isPassangerEmpty(ePassenger aPassenger);
int sortPassengers(ePassenger* list, int len, int order);
int printPassenger(ePassenger* list, int length);
void printOnePassenger(ePassenger aPassanger);
int totalPricePassenger(ePassenger* list, int length, float* pTotalPrice);
int averagePricePerPassenger(ePassenger* list, int length, float totalPrice,float* pAveragePrice);
int passengersAboveAverage(ePassenger* list, int length, float averagePrice, int* pPassengers);
void listPassengersByCodeAndType(ePassenger* list, int length);

#endif /* ARRAYPASSENGER_H_ */
