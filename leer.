#ifndef __LEER__H
#	define __LEER__H

#include <stdio.h>

/**
Con este método obtenemos la siguiente dirección del fichero.
@param direccion Es la variable en donde se guardará la dirección de 32-bits.
@return Devuelve un 1 si se leyó la dirección, o un 0, si bién hemos llegado al final del fichero.
*/
int leer_direccion(FILE* f, unsigned int* direccion);


typedef struct
{
	unsigned int num_lineas; /* número de lineas de cache */
	unsigned int tamano_linea; /* tamaño de la línea de cache */
	unsigned int asociatividad; /* nºconjuntos, que debe
		ser potencia de 2 y inferior al número de líneas */
	unsigned short reemplazo;

}configuracion;

/**
@return Devuelve la configuración espeficada por el fichero f. (Configuración apuntada por el puntero config) Y si la
configuración no tiene el formato correcto, lanzamos un error.
*/
void leer_configuracion(FILE* f, configuracion* conf);



#endif
