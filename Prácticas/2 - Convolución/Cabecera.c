#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Cabecera.h"
#define PI 3.14159265
#define FREC_CORTE 1000
#define TAM_ARREGLO 20

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
	unsigned char buffer4[4], buffer2 [2];

	//ChunkID 
	fread (cab -> ChunkID, sizeof (cab -> ChunkID), 1, entrada);
	fwrite (cab -> ChunkID, sizeof (cab -> ChunkID), 1, salida);

	//ChunkSize 
	fread (buffer4, sizeof (buffer4), 1, entrada);
	fwrite (buffer4, sizeof (buffer4), 1, salida);
	cab -> ChunkSize = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));

	//Formato "Fmt"
	fread (cab -> Format, sizeof (cab -> Format), 1, entrada);
	fwrite (cab -> Format, sizeof (cab -> Format), 1, salida);

	//SubChunk1ID Formato de datos "fmt"
	fread (cab -> SubChunk1ID, sizeof (cab -> SubChunk1ID), 1, entrada);
	fwrite (cab -> SubChunk1ID, sizeof (cab -> SubChunk1ID), 1, salida);

	//SubChunk1Size
	fread (buffer4, sizeof (buffer4), 1, entrada);
	fwrite (buffer4, sizeof (buffer4), 1, salida);
	cab -> SubChunk1Size = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
	
	// Formato de audio
	fread (buffer2, sizeof (buffer2), 1, entrada);
	fwrite (buffer2, sizeof (buffer2), 1, salida);
	cab -> AudioFormat = (buffer2 [0] | (buffer2 [1] << 8));
	
	//Canales
	fread (buffer2, sizeof (buffer2), 1, entrada);
	fwrite (buffer2, sizeof (buffer2), 1, salida);
	cab -> NumChannels = (buffer2 [0] | (buffer2 [1] << 8));

	//SampleRate
	fread (buffer4, sizeof (buffer4), 1, entrada);
	fwrite (buffer4, sizeof (buffer4), 1, salida);
	cab -> SampleRate = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
	
	//ByteRate
	fread (buffer4, sizeof (buffer4), 1, entrada);
	fwrite (buffer4, sizeof (buffer4), 1, salida);
	cab -> ByteRate = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));

	//Block Align
	fread (buffer2, sizeof (buffer2), 1, entrada);
	fwrite (buffer2, sizeof (buffer2), 1, salida);
	cab -> BlockAlign = (buffer2 [0] | (buffer2 [1] << 8));
	
	//Bits per Sample
	fread (buffer2, sizeof (buffer2), 1, entrada);
	fwrite (buffer2, sizeof (buffer2), 1, salida);
	cab -> BitsPerSample = (buffer2 [0] | (buffer2 [1] << 8));

	//SubChunk2ID
	fread (cab -> SubChunk2ID, sizeof (cab -> SubChunk2ID), 1, entrada);	
	fwrite (cab -> SubChunk2ID, sizeof (cab -> SubChunk2ID), 1, salida);

	//SubChunk2Size
	fread (buffer4, sizeof (buffer4), 1, entrada);
	fwrite (buffer4, sizeof (buffer4), 1, salida);
	cab -> SubChunk2Size = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
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

float * generaImpulso ()
{
	float * impulso = (float *) malloc (sizeof (float) * TAM_ARREGLO);
	for (i = 0; i < TAM_ARREGLO; i ++)
	{
		impulso [i] = (exp ((-2 * PI * FREC_CORTE * i) / 44100));			//Fórmula de filtro RC con fc = 1,000 Hz
	}
	return impulso;
}

float convolucion (float * entrada, float * impulso)
{
	float respuesta = 0;

	//Realizamos la convolución
	for (i = 0; i < TAM_ARREGLO; i ++)
		if (entrada [i] != 0)
			respuesta += (entrada [i] * impulso [i]);

	//Como entran valores entre -1 y 1, comprobamos la respuesta, para saber que enviamos (aun así todos los multiplicamos por 32767 que es
	//el valor máximo que puede tomar un short)
	if (respuesta > 1)
		return (1 * 32767);
	if (respuesta < -1)
		return (-1 * 32767);
	else
		return (respuesta * 32767);
}
