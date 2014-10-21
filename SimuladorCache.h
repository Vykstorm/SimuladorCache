#ifndef __SIMULADOR__H
#	define __SIMULADOR__H

# include "Leer.h"

/**
Ejecuta la simulación
@param traza Es el fichero con las direcciones de 32-bit "requeridas por la CPU"
@param conf Es la configuración de la cache.
@return Devuelve la tasa de fallos al acceder a dichas direcciones.
*/
double simular(FILE* traza, const configuracion* conf);


#endif
