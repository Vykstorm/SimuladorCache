#ifndef __UTIL_H__
#   define __UTIL_H__


/**
Extrae los bits de un número entero sin signo.
@param n Es el entero del que queremos extraer alguno de sus bits.
@param bitmenor Es la posición del bit contando de derecha a izquierda
(desde el más significativo al menos significativo). Este será el bit menos
significativo que extraeremos.
@param bitmayor Es la posición del bit contando de derecha a izquierda
(desde el más significativo al menos significativo). Este será el bit más
significativo que extraeremos.
@return Devuelve un número sin signo con los bits extraídos, desplazados hacía la
derecha, de forma que el bit menos significativo extraído de n, es el bit 0 del número
devuelto.
*/
unsigned int rangobits(unsigned int n, int bitmenor, int bitmayor);


/**
Calcula el logaritmo en base dos de un número entero potencia de dos.
Es decir, si x es de la forma 2^y, calcula 'y' devuelve y.
@param x Es un número entero potencia de 2 a excepción del 1.
*/
unsigned int log_base_2(unsigned int x);


#endif
