#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.c"

////////////////////////////////////////////////////////////////////////////////////////
////									TDF.c 										////
////																				////
////																				////
//// Implementación de la Transformada Discreta de Fourier utilizando la fórmula, 	////
//// siendo un algoritmo extremadamente costoso computacionalmente, para observar	////
//// alguna señal en el dominio de la frecuencia, su magnitud y su fase.			////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	FILE * entrada, * salida;
	cabecera cab;
	short muestra;
	char * archivo_salida = (char *) malloc (sizeof (char));
	char * archivo_entrada = (char *) malloc (sizeof (char));
	system ("cls");
	if (argc < 3)
	{
		printf("Error, faltan argumentos.\n");
		printf ("Ejemplo: '%s Archivo1.wav Salida.wav'\n\n", argv [0]);
		exit (0);
	}else
	{
		archivo_entrada = (char *) argv [1];
		archivo_salida = (char *) argv [2];
	}

	//Abrimos los archivos en modo binario
	entrada = abre_archivo (archivo_entrada, archivo_salida, 1);
	salida = abre_archivo (archivo_entrada, archivo_salida, 2);

	//Leemos e imprimimos la cabecera del archivo wav
	copiar_cabecera (entrada, salida, &cab);
	imprimir_cabecera (&cab);

	printf ("\n\n");
	fclose (entrada);
	fclose (salida);
	printf ("Se aplico la transformada discreta de fourier al archivo '%s' correctamente.\n", archivo_entrada);
	return 0;
}
