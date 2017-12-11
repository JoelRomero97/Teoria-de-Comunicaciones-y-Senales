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
	int opcion_seleccionada, i;
	float max = 32767;
	char * archivo_salida = (char *) malloc (sizeof (char));
	char * archivo_entrada = (char *) malloc (sizeof (char));
	if (argc < 4)
	{
		printf("Error, faltan argumentos.\n");
		printf ("Ejemplo: '%s -1 Archivo1.wav Salida.wav'\n\n", argv [0]);
		exit (0);
	}else
	{
		opcion_seleccionada = atoi (argv [1]);
		archivo_entrada = (char *) argv [2];
		archivo_salida = (char *) argv [3];
	}

	//Abrimos los archivos en modo binario
	entrada = abre_archivo (archivo_entrada, archivo_salida, 1);
	salida = abre_archivo (archivo_entrada, archivo_salida, 2);

	//Leemos e imprimimos la cabecera del archivo wav
	copiar_cabecera (entrada, salida, &cab);

	float * signal = (float *) malloc (sizeof (float) * (cab.SubChunk2Size / 2));
	printf ("\n\n");
	for (i = 0; i < (cab.SubChunk2Size / 2); i ++)
	{
		fread (&muestra, sizeof (short), 1, entrada);
		signal [i] = (muestra / max);
	}

	//AQUI VA EL ALGORITMO DE LA TRANSFORMADA
	if (opcion_seleccionada == -1)
		opcion_uno (salida, signal, &cab);
	else if (opcion_seleccionada == -2)
		opcion_dos (salida, signal, &cab);
	else if (opcion_seleccionada == -3)
		opcion_tres (salida, signal, &cab);
	else
	{
		printf ("\nOpcion invalida :(");
		exit (0);
	}
	printf ("\n\n");
	fclose (entrada);
	fclose (salida);
	//printf ("Se aplico la transformada discreta de fourier al archivo '%s' correctamente (Opcion %d).\n", archivo_entrada, opcion_seleccionada);
	return 0;
}
