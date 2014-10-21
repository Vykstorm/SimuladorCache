#include <stdio.h>

#define MAX 64
double v[MAX], res;

int main() 
{
	FILE *f;
	f=fopen("traza.txt","w");
	int i;
	for (i=0 ;i<MAX ; i++) {
		res=res+v[i];
		fprintf(f, "%x ", (unsigned int)&res);
		fprintf(f, "%x ", (unsigned int)&v[i]);
		fprintf(f, "%x ", (unsigned int)&res);
	} 
}
