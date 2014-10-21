#ifndef __CACHE__H
#	define __CACHE__H

#include "Leer.h"

/**
Inicializa la cache, configurandola con los datos introducir mediante
el fichero de configuración. Después de inicializar la caché, está
estará vacía (cualquier acceso a esta dará como resultado un fallo de carga, al menos el primer acceso)
*/
void inicializar_cache(const configuracion* conf);

/**
Accedemos a una direccion de memoria.
@param direccion Es la dirección de memoria a la que queremos acceder.
@return Devuelve un 0 si se produjo un fallo de caché al acceder o un 1
si se produjo un acierto de caché
*/
int acceder_direccion(unsigned int direccion);


#endif
