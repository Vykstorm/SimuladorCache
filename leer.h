#ifndef __LEER__H
#	define __LEER__H

#include <stdio.h>

/**
@return Devuelve la siguiente dirección de 32-bit del fichero apuntado por f.
Se supone que f es un manejador de fichero correcto.
Si no se pudo leer desde el fichero se genera un error.
*/
unsigned int leer_direccion(FILE* f);


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
