#ifndef __LEER__H
#	define __LEER__H

#include <stdio.h>

/**
Con esta función obtenemos la siguiente dirección de 32-bits del fichero apuntado por f
@param f
@param direccion Es la variable donde se guardará la dirección
@return Devuelve un 1 si se ha leído una dirección o 0, si bien,
hemos llegado a fin de fichero.
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
@param conf Devuelve la configuración espeficada por el fichero f. (Configuración apuntada por el puntero config) Y si la
configuración no tiene el formato correcto, lanzamos un error.
*/
void leer_configuracion(FILE* f, configuracion* conf);



#endif
