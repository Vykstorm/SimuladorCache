#include "leer.h"

#include <string.h>

unsigned int leer_direccion(FILE* f)
{
	unsigned int dir;
	fscanf(f, "%x", &dir);
	return dir;
}


int leer_linea_configuracion(FILE* f, char* etiqueta, unsigned int* valor)
{
	char linea[64];
	if(fgets(linea, 64, f) != NULL)
	{
		printf("%s\n", linea);
		sscanf(linea, "%s:%d", etiqueta, valor);
		printf("%s\n", etiqueta);
		return 1;
	}

	return 0;

}

configuracion leer_configuracion(FILE* f)
{

	return config;
}
