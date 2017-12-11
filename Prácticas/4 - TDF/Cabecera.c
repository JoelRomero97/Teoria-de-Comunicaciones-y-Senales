#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Cabecera.h"
#define PI 3.14159265

int i;					//Variable global para manejar ciclos

FILE * abre_archivo (char * entrada, char * salida, int tipo)
{
	FILE * pt1, * pt2;
	pt1 = fopen (entrada, "rb");
	if (pt1 == NULL)
	{
		printf("Error al abrir archivo '%s'.\n", entrada);
		exit(0);
	}
	
	//Abrimos el archivo a escribir en modo binario	
	pt2 = fopen (salida, "wb");
	if (pt2 == NULL)
	{
		printf("Error al crear el archivo '%s'.\n", salida);
		exit(1);
	}
	if (tipo == 1)
	{
		printf("Archivo '%s' abierto correctamente.\n", entrada);
		return pt1;
	}else
	{
		printf("Archivo '%s' creado correctamente.\n", salida);
		return pt2;
	}
}

void copiar_cabecera (FILE * entrada, FILE * salida, cabecera * cab)
{
	rewind (entrada);
	rewind (salida);

	short archivo_stereo = 2;
	int n1;
	
	//ChunkID 
	fread (cab -> ChunkID, sizeof (char), 4, entrada);
	fwrite (cab -> ChunkID, sizeof (char), 4, salida);

	//ChunkSize 
	fread (&cab -> ChunkSize, sizeof (int), 1, entrada);
	n1 = (cab -> ChunkSize * 2);
	fwrite (&n1, sizeof (int), 1, salida);

	//Formato "Fmt"
	fread (cab -> Format, sizeof (char), 4, entrada);
	fwrite (cab -> Format, sizeof (char), 4, salida);

	//SubChunk1ID Formato de datos "fmt"
	fread (cab -> SubChunk1ID, sizeof (char), 4, entrada);
	fwrite (cab -> SubChunk1ID, sizeof (char), 4, salida);

	//SubChunk1Size
	fread (&cab -> SubChunk1Size, sizeof (int), 1, entrada);
	fwrite (&cab -> SubChunk1Size, sizeof (int), 1, salida);
	
	// Formato de audio
	fread (&cab -> AudioFormat, sizeof (short), 1, entrada);
	fwrite (&cab -> AudioFormat, sizeof (short), 1, salida);
	
	//Canales (POR LA NATURALEZA DEL PROBLEMA, SIEMPRE DEBEN SER 2 CANALES)
	fread (&cab -> NumChannels, sizeof (short), 1, entrada);
	//fwrite (&cab -> NumChannels, sizeof (short), 1, salida);
	fwrite (&archivo_stereo, sizeof (short), 1, salida);

	//SampleRate
	fread (&cab -> SampleRate, sizeof (int), 1, entrada);
	fwrite (&cab -> SampleRate, sizeof (int), 1, salida);
	
	//ByteRate
	fread (&cab -> ByteRate, sizeof (int), 1, entrada);
	n1 = (cab -> ByteRate * 2);
	fwrite (&n1, sizeof (int), 1, salida);

	//Block Align
	fread (&cab -> BlockAlign, sizeof (short), 1, entrada);
	n1 = (cab -> BlockAlign * 2);
	fwrite (&n1, sizeof (short), 1, salida);
	
	//Bits per Sample
	fread (&cab -> BitsPerSample, sizeof (short), 1, entrada);
	fwrite (&cab -> BitsPerSample, sizeof (short), 1, salida);

	//SubChunk2ID
	fread (cab -> SubChunk2ID, sizeof (char), 4, entrada);	
	fwrite (cab -> SubChunk2ID, sizeof (char), 4, salida);

	//SubChunk2Size
	fread (&cab -> SubChunk2Size, sizeof (int), 1, entrada);
	n1 = (cab -> SubChunk2Size * 2);
	fwrite (&n1, sizeof (int), 1, salida);
}

void imprimir_cabecera (cabecera * cab)
{
	char * formatoArchivo = (char *) malloc (sizeof (char));
	printf("\n\n\n(1-4) Chunk ID: %s\n",cab -> ChunkID);
	printf("(5-8) ChunkSize:  %u\n",cab -> ChunkSize);
	printf("(9-12) Format: %s\n",cab -> Format);
	printf("(13-16) SubChunk 1 ID: %s\n",cab -> SubChunk1ID);
	printf("(17-20) SubChunk 1 Size: %u\n",cab -> SubChunk1Size);
	if (cab -> AudioFormat == 1)
		strcpy(formatoArchivo,"PCM");
	printf("(21-22) Audio Format: %u,%s\n",cab -> AudioFormat,formatoArchivo);
	if (cab -> NumChannels == 1)
			strcpy(formatoArchivo,"Mono");
		else 
			strcpy(formatoArchivo,"Stereo");
	printf("(23-24) Number of Channels: %u, Tipo: %s\n",cab -> NumChannels,formatoArchivo);
	printf("(25-28) Sample Rate: %u\n",cab -> SampleRate);
	printf("(29-32) Byte Rate: %u BitRate: %u\n",cab -> ByteRate,cab -> ByteRate*8);
	printf("(33-34) Block Align: %u\n",cab -> BlockAlign);
	printf("(35-36) Bits Per Sample: %u\n",cab -> BitsPerSample);
	printf("(37-40) SubChunk 2 ID: %s\n",cab -> SubChunk2ID);
	printf("(41-44) SubChunk 2 Size: %u\n",cab -> SubChunk2Size);
}

void opcion_uno (FILE * salida, float * signal, cabecera * cab)
{
	int k, n;
	float max = 32767, muestras = ((cab -> SubChunk2Size) / 2);
	short * magnitud = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	short * real = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	short * imaginario = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	float parte_real, parte_imaginaria, angulo;
	
	for (k = 0; k < muestras; k ++)
	{
		//Se resetean los valores de la parte real e imaginaria en 0
		parte_real = 0;
		parte_imaginaria = 0;
		for (n = 0; n < muestras; n ++)
		{
			//Se calcula el angulo definido
			angulo = ((2 * PI * k * n) / muestras);

			//Se calculan las partes real e imaginaria de la TDF
			parte_real += (signal [n] * (cos (angulo)));
			parte_imaginaria += (signal [n] * sin (angulo));
		}
		//Se vuelven a dividir los coeficientes de la TDF entre el numero de muestras para tener valores entre 0 y 1
		parte_real = (parte_real / muestras);
		parte_imaginaria = (parte_imaginaria / muestras);

		//Volvemos a dimensionar los valores de la señal a escribir
		real [k] = (parte_real * max);
		imaginario [k] = (parte_imaginaria * -1 * max);
		signal [k] = (signal [k] * max);
	}

	//Avanzamos el apuntador al archivo para evitar errores
	fseek (salida, 44, SEEK_SET);
	
	//PARA ESCRIBIR LOS DATOS
	for (i = 0; i < muestras; i ++)
	{
		fwrite (&signal [i], sizeof (short), 1, salida);
		fwrite (&magnitud [i], sizeof (short), 1, salida);
	}	
}

void opcion_dos (FILE * salida, float * signal, cabecera * cab)
{
	int k, n;
	float max = 32767, muestras = ((cab -> SubChunk2Size) / 2);
	short * magnitud = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	short * real = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	short * imaginario = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	float parte_real, parte_imaginaria, angulo;
	
	for (k = 0; k < muestras; k ++)
	{
		//Se resetean los valores de la parte real e imaginaria en 0
		parte_real = 0;
		parte_imaginaria = 0;
		for (n = 0; n < muestras; n ++)
		{
			//Se calcula el angulo definido
			angulo = ((2 * PI * k * n) / muestras);

			//Se calculan las partes real e imaginaria de la TDF
			parte_real += (signal [n] * (cos (angulo)));
			parte_imaginaria += (signal [n] * sin (angulo));
		}
		//Se vuelven a dividir los coeficientes de la TDF entre el numero de muestras para tener valores entre 0 y 1
		parte_real = (parte_real / muestras);
		parte_imaginaria = (parte_imaginaria / muestras);

		//Volvemos a dimensionar los valores de la señal a escribir
		real [k] = (parte_real * max);
		imaginario [k] = (parte_imaginaria * -1 * max);
	}

	//Avanzamos el apuntador al archivo para evitar errores
	fseek (salida, 44, SEEK_SET);
	
	//PARA ESCRIBIR LOS DATOS
	for (i = 0; i < muestras; i ++)
	{
		//Escribimos en el canal izquierdo la parte real de la TDF
		fwrite (&real [i], sizeof (short), 1, salida);

		//Escribimos en el canal derecho la parte imaginaria de la TDF
		fwrite (&imaginario [i], sizeof (short), 1, salida);
	}
}
