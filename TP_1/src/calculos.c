/*
 * calculos.c
 *
 *  Created on: 16 abr. 2022
 *      Author: nacho
 */
#include <stdio_ext.h>
#include <stdlib.h>
#include "utn.h"
#include "calculos.h"

/**
 * \brief Calcula el precio con descuento del 10%
 * \param precio el precio
 * \return retorna el precio con descuento si esta OK, -1 en caso de ERROR
 */
float calculos_debito(float precio)
{
	float retorno = -1;
	float descuento = 0.10;

	if(precio > 0)
	{
		retorno = precio * descuento;
		retorno = precio - retorno;
	}
	return retorno;
}
/**
 * \brief Calcula el precio con un interes del 25%
 * \param precio el precio
 * \return retorna el precio con interes si esta OK, -1 en caso de ERROR
 */
float calculos_credito(float precio)
{
	float retorno = -1;
	float interes = 0.25;

	if(precio > 0)
	{
		retorno = precio * interes;
		retorno = precio + retorno;
	}
	return retorno;
}
/**
 * \brief calcula el precio en bitcoins
 * \param precio el precio
 * \return retorna el valor en bitcoin si esta OK, -1 en caso de ERROR
 */
float calculos_bitcoin(float precio)
{
	float retorno = -1;
	float bitcoin = 4606954.55;

	if(precio > 0)
	{
		retorno = precio / bitcoin;
	}
	return retorno;
}
/**
 * \brief calcula el precio unitario
 * \param precio el precio
 * \param kilometros los kilometros
 * \return retorna el precio unitario si esta OK, -1 en caso de ERROR
 */
float calculos_precioUnitario(float precio,float kilometros)
{
	float retorno = -1;
	if(precio > 0)
	{
		retorno = precio / kilometros;
	}
	return retorno;
}
/**
 * \brief Calcula la diferencia entre un precio y otro
 * \param precio1 el precio 1
 * \param precio2 el precio 2
 * \return retorna la diferencia de precio si esta OK, -1 en caso de ERROR
 */
float calculos_diferenciaPrecio(float precio1,float precio2)
{
	float retorno = -1;
	if(precio1 > 0 && precio2 > 0)
	{
		if(precio1 > precio2)
		{
			retorno = precio1 - precio2;
		}
		else if(precio2 > precio1)
		{
			retorno = precio2 - precio1;
		}
	}
	return retorno;
}
