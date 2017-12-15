#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.h"

////////////////////////////////////////////////////////////////////////////////////////
////									ITDF.c 										////
////																				////
////																				////
//// Implementación de la Transformada Discreta de Fourier Inversa para poder pasar ////
//// del dominio de la frecuencia al dominio del tiempo y reconstruir una señal.	////
//// Compilación: gcc Cabecera.c -o Cabecera.o -c 									////
////			  gcc ITDF.c -o ITDF Cabecera.o										////
//// Ejecuación: ITDF.exe -2 Entrada.wav Salida.wav									////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	FILE * entrada, * salida;
	cabecera cab;
	int i, numero_muestras;
	char * archivo_salida = (char *) malloc (sizeof (char));
	char * archivo_entrada = (char *) malloc (sizeof (char));
	if (argc < 3)
	{
		printf("Error, faltan argumentos.\n");
		printf ("Ejemplo: '%s Entrada.wav Salida.wav'\n\n", argv [0]);
		exit (0);
	}else
	{
		archivo_entrada = (char *) argv [1];
		archivo_salida = (char *) argv [2];
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

	//Copiar la cabecera del archivo de entrada al de salida
	fread (&cab, 44, 1, entrada);
	fwrite (&cab, 44, 1, salida);

	//Imprimir los valores de la cabecera
	imprimir_cabecera (&cab);

	numero_muestras = (cab.SubChunk2Size / cab.BlockAlign);

	short * re = (short *) malloc (sizeof (short) * numero_muestras);
	short * im = (short *) malloc (sizeof (short) * numero_muestras);

	for (i = 0; i < numero_muestras; i ++)
	{
		fread (&re [i], sizeof (short), 1, entrada);
		fread (&im [i], sizeof (short), 1, entrada);
	}
	transformada_inversa (salida, re, im, &cab);
	fclose (entrada);
	fclose (salida);
	return 0;
}
