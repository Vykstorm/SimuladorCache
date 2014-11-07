#include <stdio.h>
#include <stdlib.h>
#include "Leer.h"
#include "Cache.h"


/**
Esta función realiza la simulación y devuelve el nºaccesos totales a la caché y además, el nº de fallos que se produjeron.
@param traza Es el stream que apunta al archivo que contiene la traza de las
direcciones 32-bit.
@param conf Es la configuración para la cache.
@param accesos Es un puntero que guardará el nº de accesos realizados en total.
@param fallos Es un puntero que guardará el nº de fallos.
*/
void simular(FILE* traza, const configuracion* conf, unsigned int* accesos, unsigned int* fallos)
{
    unsigned int direccion;
    *accesos = *fallos = 0;

    /* Configuramos la caché */
    inicializar_cache(conf);

    /* accedemos secuencialmente a las direcciones indicadas en la traza y contamos el nºaccesos y
    nºfallos */
    while(leer_direccion(traza,&direccion))
    {
        ++(*accesos);
        if(!acceder_direccion(direccion))
            ++(*fallos);
    }

}

/**
El programa será invocado con la siguiente estructura:
SimuladorCache [fichero_configuracion] [traza_direcciones]

Los parámetros posibles que el programa toma son: fichero_configuración, traza_direcciones

Si no se especifica el fichero de configuración, para la configuración de la caché, se leerá por
defecto del fichero "config.txt" dentro del directorio actual. Si no existe tal fichero, se genera un
error.

La traza de direcciones indica la ruta del fichero que contiene las direcciones de 32-bit.
Si tal fichero no existe, se genera un error. Si el fichero de traza no se especifica, se leerán las direcciones
desde la entrada estandar (stdin)

*/

int main(int argc, char** argv)
{
    FILE *fichero_conf, *fichero_traza;
    configuracion conf;
    /* De donde vamos a leer el fichero de configuración de la caché ? */
    fichero_conf = fopen((argc >= 2) ? argv[1] : "config.txt", "r");

    if(!fichero_conf)
    {
        fprintf(stderr, "Fallo al abrir el fichero de configuracion \"%s\"\n", (argc >= 2) ? argv[1] : "config.txt");
        exit(-1);
    }

    /* De dónde leemos la traza ? */
    if(argc >= 3)
    {
        fichero_traza = fopen(argv[2], "r");
        if(!fichero_traza)
        {
            fprintf(stderr, "Fallo al leer el fichero de la traza de direcciones \"%s\"\n", argv[2]);
            exit(-1);
        }
    }
    else
        fichero_traza = stdin;


    /* Leemos la configuración de caché */
    leer_configuracion(fichero_conf, &conf);
    fclose(fichero_conf);


    /* Realizamos la simulación */
    unsigned int fallos, accesos;
    double freq_fallos;

    simular(fichero_traza, &conf, &accesos, &fallos);
    freq_fallos = (accesos > 0) ? (double)fallos / accesos : 1.0f;

#ifdef _DEBUG
    printf("Numero total de accesos: %u\n",  accesos);
    printf("Numero total de fallos: %u\n", fallos);
#endif

    printf("La frecuencia de fallos para esta cache es: %.3f %%\n", freq_fallos * 100);

    /* Cerramos el fichero de la traza de direcciones */
    fclose(fichero_traza);

    return 0;
}
