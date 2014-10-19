#include "leer.h"

#include <string.h>


unsigned int leer_direccion(FILE* f)
{
	unsigned int dir;
	/* leemos un entero hexadecimal desde el fichero */
	fscanf(f, "%x", &dir);
	return dir;
}


int leer_linea_configuracion(FILE* f, char* etiqueta, unsigned int* valor)
{
	char linea[64];
	if(fgets(linea, 64, f) != NULL)
	{
        /* si hay una nueva línea, procesarla y obtener la etiqueta y su valor */
        int items = sscanf(linea, "%[^ :\n]%*[ :]%u", etiqueta, valor);
        /* si hay etiqueta y valor, tendremos una nueva línea de configuración... */
        return items == 2;
	}

	return 0;
}

void insertar_linea_configuracion(configuracion* conf, char* etiqueta, unsigned int valor)
{
    /* comprobamos la etiqueta de la línea */
    if(strcmp(etiqueta, "Tlin") == 0)
        conf->tamano_linea = valor;
    else if(strcmp(etiqueta, "Nlin") == 0)
        conf->num_lineas = valor;
    else if(strcmp(etiqueta, "Asoc") == 0)
        conf->asociatividad = valor;
    else if(strcmp(etiqueta, "Rpla") == 0)
        conf->reemplazo = valor;
}

void leer_configuracion(FILE* f, configuracion* conf)
{
    char etiqueta[32];
    unsigned int valor;

    /* leemos todas las líneas de configuración del fichero */
    while(leer_linea_configuracion(f, etiqueta, &valor))
        insertar_linea_configuracion(conf, etiqueta, valor); /* una vez leída la línea, la "insertamos" a la configuración */
}
