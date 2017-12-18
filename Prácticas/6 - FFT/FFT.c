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
////			  gcc FFT.c -o FFT Cabecera.o										////
//// Ejecuación: FFT.exe -2 Entrada.wav Salida.wav 0								////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	FILE * entrada, * salida;
	cabecera cab;
	short muestra;
	int opcion_seleccionada, i, numero_muestras, inversa;
	char * archivo_salida = (char *) malloc (sizeof (char));
	char * archivo_entrada = (char *) malloc (sizeof (char));
	if (argc < 5)
	{
		printf("Error, faltan argumentos.\n");
		printf ("Ejemplo: '%s -1 Entrada.wav Salida.wav 0'\n\n", argv [0]);
		exit (0);
	}else
	{
		opcion_seleccionada = atoi (argv [1]);
		archivo_entrada = (char *) argv [2];
		archivo_salida = (char *) argv [3];
		inversa = atoi (argv [4]);
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

	float * re = (float *) malloc (sizeof (float) * numero_muestras);
	float * im = (float *) malloc (sizeof (float) * numero_muestras);

	for (i = 0; i < numero_muestras; i ++)
	{
		fread (&muestra, sizeof (short), 1, entrada);
		re [i] = (float) muestra;
		im [i] = 0.0;
	}

	if (opcion_seleccionada == -1)
		opcion_uno (salida, re, im, numero_muestras, inversa);
	else if (opcion_seleccionada == -2)
		opcion_dos (salida, re, im, numero_muestras, inversa);
	else if (opcion_seleccionada == -3)
		opcion_tres (salida, re, im, numero_muestras, inversa);
	else
	{
		printf ("\nOpcion invalida");
		exit (0);
	}
	fclose (entrada);
	fclose (salida);
	return 0;
}
