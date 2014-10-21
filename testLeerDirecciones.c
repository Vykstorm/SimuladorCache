#include "leer.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* f = fopen("traza.txt", "r");
	if(!f) 
	{
		fprintf(stderr, "error al leer el fichero \"traza.txt\"");
		exit(-1);
	}
	
	unsigned int direccion;
	while(leer_direccion(f, &direccion))
		printf("%x ", direccion);
	printf("\n");
	fclose(f);
}
