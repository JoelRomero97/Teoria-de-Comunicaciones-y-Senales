#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.h"

////////////////////////////////////////////////////////////////////////////////////////
////									TDF.c 										////
////																				////
////																				////
//// Implementación de la Transformada Discreta de Fourier utilizando la fórmula, 	////
//// siendo un algoritmo extremadamente costoso computacionalmente, para observar	////
//// alguna señal en el dominio de la frecuencia, su magnitud y su fase.			////
//// Compilación: gcc Cabecera.c -o Cabecera.o -c 									////
////			  gcc TDF.c -o TDF Cabecera.o										////
//// Ejecuación: TDF.exe -2 Entrada.wav Salida.wav									////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	FILE * entrada, * salida;
	cabecera cab;
	short muestra;
	int opcion_seleccionada, i, numero_muestras;
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
	entrada = fopen (archivo_entrada, "rb");
	if (entrada == NULL)
	{
		printf ("Error al abrir el archivo: '%s'", archivo_entrada);
		exit (0);
	}
	salida = fopen (archivo_salida, "wb");
	if (salida == NULL)
	{
		printf ("Error al crear el archivo: '%s'", archivo_salida);
		exit (0);
	}

	//Leer la cabecera del archivo de entrada
	fread (&cab, 44, 1, entrada);

	numero_muestras = (cab.SubChunk2Size / cab.BlockAlign);

	//Modificar algunos parámetros de la cabecera
	cab.ChunkSize = (cab.ChunkSize * 2);
	cab.NumChannels = (short) 2;
	cab.ByteRate = (cab.ByteRate * 2);
	cab.BlockAlign = (short) 4;
	cab.BitsPerSample = (short) 16;
	cab.SubChunk2Size = (cab.SubChunk2Size * 2);

	//Copiar la cabecera modificada al archivo de salida
	fwrite (&cab, 44, 1, salida);

	//Imprimir los valores de la cabecera
	imprimir_cabecera (&cab);

	float * signal = (float *) malloc (sizeof (float) * (cab.SubChunk2Size / 2));
	printf ("\n\n");
	for (i = 0; i < numero_muestras; i ++)
	{
		fread (&muestra, sizeof (short), 1, entrada);
		signal [i] = (muestra / max);
	}

	if (opcion_seleccionada == -1)
		opcion_uno (salida, signal, &cab);
	else if (opcion_seleccionada == -2)
		opcion_dos (salida, signal, &cab);
	else if (opcion_seleccionada == -3)
		opcion_tres (salida, signal, &cab);
	else
	{
		printf ("\nOpcion invalida");
		exit (0);
	}
	fclose (entrada);
	fclose (salida);
	return 0;
}
