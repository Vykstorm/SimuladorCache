#include "leer.h"
#include <stdlib.h>
#include <stdio.h>


int main()
{
	FILE* f = fopen("config.txt",  "r");
	if(!f)
	{
		fprintf(stderr, "fallo al leer el fichero config.txt");	
		exit(-1);
	}
	
	configuracion conf;
	leer_configuracion(f, &conf);

	printf("Numero de lineas: %u\n", conf.num_lineas);
	printf("Tamano de linea: %u\n", conf.tamano_linea);	
	printf("Asociatividad: %u\n", conf.asociatividad);
	printf("Reemplazo: %hu (%s)\n", conf.reemplazo, conf.reemplazo ? "LRU" : "Aleatorio");

	fclose(f);
}
