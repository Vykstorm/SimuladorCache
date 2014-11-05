#include <stdio.h>
#include <stdlib.h>
#include "Util.h"




unsigned int rangobits(unsigned int n, int bitmenor, int bitmayor)
{
    unsigned int d1=1, d2=1;
    if (bitmenor < 0 || bitmenor > 31) {
        fprintf(stderr, "rangobits: Error en bitmenor: %d\n", bitmenor);
        exit(-1);
    }
    else if (bitmayor < 0 || bitmayor > 31) {
        fprintf(stderr, "rangobits: Error en bitmayor: %d\n", bitmayor);
        exit(-1);
    }
    else if (bitmayor < bitmenor) {
        fprintf(stderr, "rangobits: Error en orden\n");
        exit(-1);
    }
    else if(bitmayor-bitmenor+1 < 32 ) {
        /* calcula 2 elevado a bitmenor */
        d1=d1<<bitmenor;
        /* calcula 2 elevado a (bitmayor-bitmenor+1) */
        d2=d2<<(bitmayor-bitmenor+1);
        n=n/d1;
        n=n%d2;
    }
    return n;
}

unsigned int log_base_2(unsigned int x)
{
    unsigned int s, r;
    r = 0; s = 1;
    while(s < x)
    {
        r++;
        s *= 2;
    }
    if(s > x)
    {
        fprintf(stderr, "log_base_2: %x no es un entero potencia de 2 mayor que 0\n", x);
        exit(-1);
    }
    return r;
}
