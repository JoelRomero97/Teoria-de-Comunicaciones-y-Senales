#include <stdlib.h>
#include <stdio.h>
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
	printf ("(41-44) SubChunk 2 Size: %u\n\n\n", cab -> SubChunk2Size);
}

void opcion_uno (FILE * salida, short * signal, cabecera * cab)
{
	int i, k, n;
	float max = 32767, muestras = (cab -> SubChunk2Size / cab -> BlockAlign);
	double real, imaginario, angulo;
	short parte_real, parte_imaginaria, original, magnitud;
	fseek (salida, 44, SEEK_SET);
	uswtime (&utime0, &wtime0);
	for (k = 0; k < muestras; k ++)
	{
		real = 0;
		imaginario = 0;
		original = signal [k];
		for (n = 0; n < muestras; n ++)
		{
			angulo = ((2 * PI * k * n) / muestras);
			real += (signal [n] * (cos (angulo)));
			imaginario -= (signal [n] * sin (angulo));
		}
		parte_real = (real / muestras);
		parte_imaginaria = (imaginario / muestras);
		magnitud = (short) sqrt (pow (parte_real, 2) + pow (parte_imaginaria, 2));
		fwrite (&original, sizeof (short), 1, salida);
		fwrite (&magnitud, sizeof (short), 1, salida);
	}
	uswtime (&utime1, &wtime1);
	calculaTiempo (utime0, wtime0, utime1, wtime1, muestras, 1);
}

void opcion_dos (FILE * salida, short * signal, cabecera * cab)
{
	int i, k, n;
	float max = 32767, muestras = (cab -> SubChunk2Size / cab -> BlockAlign);
	double real, imaginario, angulo;
	short parte_real, parte_imaginaria;
	fseek (salida, 44, SEEK_SET);
	uswtime (&utime0, &wtime0);
	for (k = 0; k < muestras; k ++)
	{
		real = 0;
		imaginario = 0;
		for (n = 0; n < muestras; n ++)
		{
			angulo = ((2 * PI * k * n) / muestras);
			real += (signal [n] * (cos (angulo)));
			imaginario -= (signal [n] * sin (angulo));
		}
		parte_real = (real / muestras);
		parte_imaginaria = (imaginario / muestras);
		fwrite (&parte_real, sizeof (short), 1, salida);
		fwrite (&parte_imaginaria, sizeof (short), 1, salida);
	}
	uswtime (&utime1, &wtime1);
	calculaTiempo (utime0, wtime0, utime1, wtime1, muestras, 2);
}

void opcion_tres (FILE * salida, short * signal, cabecera * cab)
{
	int i, k, n;
	float max = 32767, muestras = (cab -> SubChunk2Size / cab -> BlockAlign);
	double real, imaginario, angulo;
	short parte_real, parte_imaginaria, fase, magnitud;
	fseek (salida, 44, SEEK_SET);
	uswtime (&utime0, &wtime0);
	for (k = 0; k < muestras; k ++)
	{
		real = 0;
		imaginario = 0;
		for (n = 0; n < muestras; n ++)
		{
			angulo = ((2 * PI * k * n) / muestras);
			real += (signal [n] * (cos (angulo)));
			imaginario -= (signal [n] * sin (angulo));
		}
		parte_real = (real / muestras);
		parte_imaginaria = (imaginario / muestras);
		magnitud = (short) sqrt (pow (parte_real, 2) + pow (parte_imaginaria, 2));
		if (magnitud == 0)
			fase = 0;
		else
		{
			if ((parte_real == 0) && (parte_imaginaria < 0))
				fase = (short) (- PI / 2);
			else if ((parte_real == 0) && (parte_imaginaria > 0))
				fase = (short) (PI / 2);
			else if ((parte_real < 0) && (parte_imaginaria >= 0))
				fase = (short) (atan (parte_imaginaria / parte_real) + PI);
			else if ((parte_real < 0) && (parte_imaginaria < 0))
				fase = (short) (atan (parte_imaginaria / parte_real) - PI);
		}
		fwrite (&magnitud, sizeof (short), 1, salida);
		fwrite (&fase, sizeof (short), 1, salida);
	}
	uswtime (&utime1, &wtime1);
	calculaTiempo (utime0, wtime0, utime1, wtime1, muestras, 3);
}

void uswtime (double * usertime, double * walltime)
{
	double mega = 1.0e-6;
	struct rusage buffer;
	struct timeval tp;
	struct timezone tzp;
	getrusage (RUSAGE_SELF, &buffer);
	gettimeofday (&tp, &tzp);
	*usertime = (double) buffer.ru_utime.tv_sec +1.0e-6 * buffer.ru_utime.tv_usec;
	*walltime = (double) tp.tv_sec + 1.0e-6 * tp.tv_usec; 
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
