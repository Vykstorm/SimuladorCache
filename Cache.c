#include "Cache.h"
#include "Util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define __malloc(__type, s) (__type*)malloc(sizeof(__type) * s);

/* Esta estructura de datos representa la información que guardaremos en nuestra "cache" por
cada bloque */
typedef struct
{
    unsigned int etiqueta; /* guardamos la etiqueta del bloque que se almacena. Tendrá un valor consistente si valido=1 */
    int valido; /* Tendrá valor 0 o 1 indicando si esta celda/linea esta ocupada por un bloque */
    unsigned int contador_lru; /* tendrá un valor consistente si valido=1 y la caché tiene algorimo de reemplazo lru.
    Valores grandes indican que la línea ha sido recientemente añadida, valores pequeños indican lo contrario. */
}linea;

unsigned int num_conjuntos; /* Será el número de conjuntos de la caché*/
unsigned int asociatividad; /* Será el número de líneas por conjunto de la caché */
unsigned short es_lru; /* 1 si la caché es lru, 0 si el reemplazo es aleatorio */

unsigned int num_bits_offset; /*'Será el número de bits de una dirección usado para indexar un byte dentro de un bloque */
unsigned int num_bits_indice; /* Será el número de bits usados para indexar el conjunto donde se mapean los bloques */
unsigned int num_bits_etiqueta; /* Será el numero de bits usados para indexar, dentro de un mismo conjunto,
    el bloque */



/* siempre se cumplirá que 32 = num_bits_offset + num_bits_indice + num_bits_etiqueta */


linea** cache; /* guarda toda la información de las líneas de la caché. Es una matriz donde a cada conjunto le corresponde
una fila, y hay tantas columnas como líneas por conjunto haya */



/* Funciones auxiliares */

/* Devuelve la etiqueta de una dirección */
unsigned int obtener_etiqueta(unsigned int direccion);

/* Devuelve el nºconjunto de una dirección */
unsigned int obtener_indice(unsigned int direccion);

/* Comprueba si un acceso es un acierto: Si el bloque con la etiqueta especificada está en el conjunto indicado (comparando
etiquetas) */
int es_acierto(unsigned int etiqueta, unsigned int indice);

/* Si el conjunto no esta lleno, reemplaza el bloque cuya etiqueta es la indicada en el primer hueco libre. Si esta lleno, se
selecciona un bloque de entre todos los del conjunto y se reemplaza por el nuevo (solo se reemplaza la etiqueta) */
void traer_bloque(unsigned int etiqueta, unsigned int indice);

/* Se actualizan los contadores lru. La precondición para este método es que exista un bloque con esta etiqueta en el conjunto
indicado, y que el algoritmo de reemplazo sea el lru. Los contadores de todas las líneas que tengan etiquetas no coincidentes,
son decrementadas si su contador es mayor que el contador actual de la línea cuya etiqueta sea coincidente. Posteriormente,
el contador de la línea con la etiqueta coincidente se establece al máximo (nºlines por conjunto) */
void actualizar_contadores(unsigned int etiqueta, unsigned int indice);



void inicializar_cache(const configuracion* conf)
{
    int i, j;

    num_conjuntos = conf->num_lineas / conf->asociatividad;
    asociatividad = conf->asociatividad;
    es_lru = conf->reemplazo;

    num_bits_offset = log_base_2(conf->tamano_linea);
    num_bits_indice = log_base_2(num_conjuntos);
    num_bits_etiqueta = 32 - num_bits_offset - num_bits_indice;

    /* inicializamos la caché, de forma que todas las líneas esten disponibles */
    cache = __malloc(linea*, num_conjuntos);
    for(i = 0; i != num_conjuntos; ++i)
        cache[i] = __malloc(linea, asociatividad);

    for(i = 0;i != num_conjuntos; ++i)
        for(j = 0; j != asociatividad; ++j)
        {
            linea* l = &cache[i][j];
            l->contador_lru = 1;
            l->valido = 0;
        }
}

int acceder_direccion(unsigned int direccion)
{
    unsigned int etiqueta, indice;

    /* obttener la etiqueta y el nºconjunto (índice), de la dirección */

    etiqueta = obtener_etiqueta(direccion);
    indice = obtener_indice(direccion);

    /* comprobar si el acceso es un fallo o es un acierto, es decir, si se encuentra o no en cache dicho
    bloque */
    if(es_acierto(etiqueta, indice))
    {
#ifdef _DEBUG
        printf("Acierto de cache para: %x\n", direccion);
#endif
        /* actualizamos los contadores lru */
        if(es_lru)
            actualizar_contadores(etiqueta, indice);
        return 1;
    }

#ifdef _DEBUG
    printf("Fallo en la cache para: %x\n", direccion);
#endif

    /* si es fallo, traer el bloque que contiene el dato apuntado por la dirección, a la caché */

    /* traer dicho bloque a la memoria cache */
    traer_bloque(etiqueta, indice);

    /* actualizamos los contadores lru */
    if(es_lru)
        actualizar_contadores(etiqueta, indice);

    return 0;
}

unsigned int obtener_etiqueta(unsigned int direccion)
{
    return rangobits(direccion, num_bits_offset + num_bits_indice, 31);
}

unsigned int obtener_indice(unsigned int direccion)
{
    return rangobits(direccion, num_bits_offset, num_bits_offset + num_bits_indice - 1);
}


int es_acierto(unsigned int etiqueta, unsigned int indice)
{
    /* buscar una línea que contenga un bloque donde el valor de su etiqueta es el mismo que
    la etiqueta dela dirección, dentro de las líneas del conjunto. */

    /* seleccionamos el conjunto */
    linea* l = cache[indice];

    /* buscamos la etiqueta */
    int j = 0;
    while((j < (asociatividad - 1)) && (!l[j].valido || (etiqueta != l[j].etiqueta) ))
        j++;
    return l[j].valido && (etiqueta == l[j].etiqueta);
}

void traer_bloque(unsigned int etiqueta, unsigned int indice)
{
    linea* l = cache[indice];
    int i, j;

    /* comprobamos si hay alguna línea vacía */
    i = 0;
    while((i < (asociatividad - 1)) && l[i].valido)
        i++;

    /* Si hay alguna línea vacía, "copiar" el bloque a esa línea, y establecer el "bit de validez"
    a cero. */
    if(!l[i].valido)
    {
        l[i].etiqueta = etiqueta;
        l[i].valido = 1;
    }
    else
    {
        /* Si no hay ninguna línea vacía pasamos al algoritmo de reemplazo ... */

        /* Seleccionamos él bloque a reemplazar, es decir, que bloque eliminamos */
        if(es_lru)
        {
            /* Seleccionamos la línea cuyo contador es mínimo */
            j = 0;
            for(i = 1; i != asociatividad; ++i)
                if(l[i].contador_lru < l[j].contador_lru)
                    j = i;
        }
        else
        {
            /* seleccionamos una línea de forma aleatoria */
            j = numero_aleatorio(0, asociatividad);
        }

        /* La línea con el bloque eliminado está vacía, y "copiamos" el nuevo bloque a esta línea */
        l[j].etiqueta = etiqueta;
    }
}


void actualizar_contadores(unsigned int etiqueta, unsigned int indice)
{
    linea* l =  cache[indice];
    int i, j;
    i = 0;
    while(!l[i].valido || (l[i].etiqueta != etiqueta))
        i++;

    /* actualizamos los contadores lru de un conjunto:
    1º Para toda línea cuya etiqueta no encaje con la especificada, su contador lru se decrementa si
    su valor actual es mayor que el contador de la línea con la etiqueta coincidente */
    for(j = 0; j != asociatividad; j++)
        if((j != i) && l[j].valido && (l[j].contador_lru > l[i].contador_lru))
            l[j].contador_lru--;

    /* Establecemos el contador lru de la línea con la etiqueta especificada al máximo */
    l[i].contador_lru = asociatividad;
}
