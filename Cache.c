#include "Cache.h"

void inicializar_cache(const configuracion* conf)
{

}

unsigned int obtener_direccion_bloque(unsigned int direccion);

int es_acierto(unsigned int direccion_bloque);

void transferir_bloque(unsigned int direccion_bloque);



int acceder_direccion(unsigned int direccion)
{
    /* obtener el bloque que contiene el byte apuntado por la dirección a la que se accede.
    La dirección del bloque se obtiene extrayendo la etiqueta y el nºconjunto de la dirección */
    unsigned int direccion_bloque = obtener_direccion_bloque(direccion);

    /* comprobar si el acceso es un fallo o es un acierto, es decir, si se encuentra o no en cache dicho
    bloque */
    if(es_acierto(direccion_bloque))
        return 1;

    /* si es fallo, traer el bloque que contiene el dato apuntado por la dirección, a la caché */

    /* traer dicho bloque a la memoria cache */
    transferir_bloque(direccion_bloque);

    return 0;
}


unsigned int obtener_direccion_bloque(unsigned int direccion)
{

}

int es_acierto(unsigned int direccion_bloque)
{
    return 0;
}

void transferir_bloque(unsigned int direccion_bloque)
{

}



