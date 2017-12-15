#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "Cabecera.h"
#define PI 3.14159265

double utime0, wtime0, utime1, wtime1;

void imprimir_cabecera (cabecera * cab)
{
	char * formatoArchivo = (char *) malloc (sizeof (char));
	printf ("\n\n");
	printf ("(1-4) Chunk ID: %s\n", cab -> ChunkID);
	printf ("(5-8) ChunkSize:  %u\n", cab -> ChunkSize);
	printf ("(9-12) Format: %s\n", cab -> Format);
	printf ("(13-16) SubChunk 1 ID: %s\n", cab -> SubChunk1ID);
	printf ("(17-20) SubChunk 1 Size: %u\n", cab -> SubChunk1Size);
	if (cab -> AudioFormat == 1)
			strcpy (formatoArchivo, "PCM");
		printf ("(21-22) Audio Format: %u, %s\n", cab -> AudioFormat,formatoArchivo);
	if (cab -> NumChannels == 1)
			strcpy (formatoArchivo, "Mono");
		else 
			strcpy (formatoArchivo, "Stereo");
	printf ("(23-24) Number of Channels: %u, Tipo: %s\n", cab -> NumChannels,formatoArchivo);
	printf ("(25-28) Sample Rate: %u\n", cab -> SampleRate);
	printf ("(29-32) Byte Rate: %u BitRate: %u\n", cab -> ByteRate,cab -> ByteRate * 8);
	printf ("(33-34) Block Align: %u\n", cab -> BlockAlign);
	printf ("(35-36) Bits Per Sample: %u\n", cab -> BitsPerSample);
	printf ("(37-40) SubChunk 2 ID: %s\n", cab -> SubChunk2ID);
	printf ("(41-44) SubChunk 2 Size: %u\n", cab -> SubChunk2Size);
}

void transformada_inversa (FILE * salida, short * re, short * im, cabecera * cab)
{
	int k, n, numero_muestras;
	short parte_real, parte_imaginaria;
	double real, imaginario, angulo;
	numero_muestras = (cab -> SubChunk2Size / cab -> BlockAlign);
	fseek (salida, 44, SEEK_SET);
	uswtime (&utime0, &wtime0);
	for (k = 0; k < numero_muestras; k ++)
	{
		real = 0;
		imaginario = 0;
		for (n = 0; n < (numero_muestras / 2); n ++)
		{
			angulo = ((2 * PI * k * n) / numero_muestras);
			real += ((re [n] * cos (angulo)) - (im [n] * sin (angulo)));
			imaginario += ((im [n] * cos (angulo)) + (re [n] * sin (angulo)));
		}
		parte_real = (real * 2);
		parte_imaginaria = (imaginario * 2);
		fwrite (&parte_real, sizeof (short), 1, salida);
		fwrite (&parte_imaginaria, sizeof (short), 1, salida);
	}
	uswtime (&utime1, &wtime1);
	calculaTiempo (utime0, wtime0, utime1, wtime1, numero_muestras, 1);
}

void calculaTiempo (double utime0, double wtime0, double utime1, double wtime1, int n, int opcion)
{
	char * option = (char *) malloc (sizeof (char));
	switch (opcion)
	{
		case 1:
			strcpy (option, "Opcion 1");
			break;
		case 2:
			strcpy (option, "Opcion 2");
			break;
		case 3:
			strcpy (option, "Opcion 3");
			break;
	}
	printf("Tiempo con la %s para un archivo de %d muestras:\n\n", option, n);
	printf("Tiempo total:  %.10f s\n",  wtime1 - wtime0);
	printf("Tiempo de procesamiento en CPU: %.10f s\n",  utime1 - utime0);
	printf ("________________________________________________________________________________________________________________________");
}
