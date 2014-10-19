#include "leer.h"

#include <string.h>


unsigned int leer_direccion(FILE* f)
{
	unsigned int dir;
	/* leemos un entero hexadecimal desde el fichero */
	fscanf(f, "%x", &dir);
	return dir;
}


int leer_linea_configuracion(FILE* f, char* etiqueta, int* valor)
{
	char linea[64];
	if(fgets(linea, 64, f) != NULL)
	{
        /* si hay una nueva línea, procesarla y obtener la etiqueta y su valor */
        int items = sscanf(linea, "%[^ :\n]%*[ :]%d", etiqueta, valor);
        /* si hay etiqueta y valor, tendremos una nueva línea de configuración... */
        if(items == 2)
            return 1;

        /* en caso contrario, tendremos una línea vacía, luego procesamos la siguiente */
        return leer_linea_configuracion(f, etiqueta, valor);
	}

	return 0;
}

unsigned long int redondear_a_potencia_2(unsigned long int valor)
{
    /* redondeamos el valor a la primera potencia de 2 que sea mayor o igual que el valor */
    unsigned long int i = 1;
    while(i < valor)
        i *= 2;
    return i;
}

int es_potencia_2(unsigned long int valor)
{
    return redondear_a_potencia_2(valor) == valor;
}

void insertar_linea_configuracion(configuracion* conf, char* etiqueta, int valor)
{
    /* comprobamos la etiqueta de la línea */

    if(strcmp(etiqueta, "Rpla") != 0)
    {
        /* el valor de configuración no puede ser 0 para Tlin, Nlin y Asoc */
        if(valor <= 0)
        {
            fprintf(stderr, "el valor para la etiqueta \"%s\" debe ser un entero mayor que cero\n", etiqueta);
            exit(-1);
        }

        /* Para Nlin, Asoc y Rpla, deben ser multiplos de 2 */
        if(!es_potencia_2(valor))
        {
            fprintf(stderr, "el valor para la etiqueta \"%s\" debe ser un entero potencia de 2\n", etiqueta);
            exit(-1);
        }
    }
    if(strcmp(etiqueta, "Tlin") == 0)
        conf->tamano_linea = valor;
    else if(strcmp(etiqueta, "Nlin") == 0)
        conf->num_lineas = valor;
    else if(strcmp(etiqueta, "Asoc") == 0)
        conf->asociatividad = valor;
    else if(strcmp(etiqueta, "Rpla") == 0)
    {
        /* Rpla debe ser 0 o 1 */
        if((valor != 0) && (valor != 1))
        {
            fprintf(stderr, "el valor para la etiqueta reemplazo debe ser un 0 o un 1\n");
            exit(-1);
        }
        conf->reemplazo = valor;
    }
    else
    {
        /* línea de configuración errónea */
        fprintf(stderr, "configuracion no valida: \"%s\"\n", etiqueta);
        exit(-1);
    }
}

void inicializar_configuracion(configuracion* conf)
{
    /* inicializamos todas las configuraciones */
    conf->num_lineas = conf->tamano_linea = conf->asociatividad = 0;
    conf->reemplazo = 2;
}

void comprobar_configuracion(configuracion* conf)
{
    /* el fichero de configuración especificaba todas las configuraciones necesarias
    para la simulación */
    if(conf->num_lineas == 0)
        fprintf(stderr, "Numero de lineas no establecido en la configuracion\n");
    if(conf->tamano_linea == 0)
        fprintf(stderr, "Tamano de linea no establecido en la configuracion\n");
    if(conf->reemplazo == 2)
        fprintf(stderr, "Tipo de reemplazo no establecido en la configuracion\n");
    if(conf->asociatividad == 0)
        fprintf(stderr, "Asociatividad no establecida en la configuracion\n");

    if((conf->num_lineas == 0) || (conf->tamano_linea == 0) || (conf->reemplazo == 2) || (conf->asociatividad == 0))
        exit(-1);

    /* la asociatividad debe ser igual o inferior al número de
    lïneas */
    if(conf->asociatividad > conf->num_lineas)
    {
        fprintf(stderr, "La asociatividad debe ser menor o igual al numero de lineas\n");
        exit(-1);
    }
}

void leer_configuracion(FILE* f, configuracion* conf)
{
    char etiqueta[32];
    int valor;

    /* inicializamos la configuración */
    inicializar_configuracion(conf);

    /* leemos todas las líneas de configuración del fichero */
    while(leer_linea_configuracion(f, etiqueta, &valor))
        insertar_linea_configuracion(conf, etiqueta, valor); /* una vez leída la línea, la "insertamos" a la configuración */

    /* hemos leído todas las configuraciones que necesitamos ? ... */
    comprobar_configuracion(conf);
}
