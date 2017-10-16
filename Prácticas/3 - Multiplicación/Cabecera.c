#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Cabecera.h"
#define PI 3.14159265
#define FREC_CORTE 1000
#define TAM_ARREGLO 20

int i;					//Variable global para manejar ciclos
unsigned char buffer4 [4], buffer2 [2];

FILE * abreArchivo (char * archivo1, char * archivo2, char * salida, int tipo)
{
	FILE * archivo_1, * archivo_2, * archivo_salida;
	archivo_1 = fopen (archivo1,"rb");
	if (archivo_1 == NULL)
	{
		printf("Error al abrir archivo '%s'.\n", archivo1);
		exit (0);
	}

	archivo_2 = fopen (archivo2,"rb");
	if (archivo_2 == NULL)
	{
		printf("Error al abrir archivo '%s'.\n", archivo2);
		exit (0);
	}
	archivo_salida = fopen (salida,"wb");
	if (archivo_salida == NULL)
	{
		printf ("Error al crear el archivo '%s'.\n", salida);
		exit (0);
	}
	if (tipo == 1)
		return archivo_1;
	else if (tipo == 2)
		return archivo_2;
	else
		return archivo_salida;
}

void leer_cabecera (FILE * archivo1, FILE * archivo2, cabecera * cab1, cabecera * cab2)
{
	rewind (archivo1);
	rewind (archivo2);

	//ChunkID 
	fread (cab1 -> ChunkID, sizeof (cab1 -> ChunkID), 1, archivo1);
	fread (cab2 -> ChunkID, sizeof (cab2 -> ChunkID), 1, archivo2);

	//ChunkSize 
	fread (buffer4, sizeof (buffer4), 1, archivo1);
	cab1 -> ChunkSize = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
	fread (buffer4, sizeof (buffer4), 1, archivo2);
	cab2 -> ChunkSize = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));

	//Formato "Fmt"
	fread (cab1 -> Format, sizeof (cab1 -> Format), 1, archivo1);
	fread (cab2 -> Format, sizeof (cab2 -> Format), 1, archivo2);

	//SubChunk1ID Formato de datos "fmt"
	fread (cab1 -> SubChunk1ID, sizeof (cab1 -> SubChunk1ID), 1, archivo1);
	fread (cab2 -> SubChunk1ID, sizeof (cab2 -> SubChunk1ID), 1, archivo2);

	//SubChunk1Size
	fread (buffer4, sizeof (buffer4), 1, archivo1);
	cab1 -> SubChunk1Size = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
	fread (buffer4, sizeof (buffer4), 1, archivo2);
	cab2 -> SubChunk1Size = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
	
	// Formato de audio
	fread (buffer2, sizeof (buffer2), 1, archivo1);
	cab1 -> AudioFormat = (buffer2 [0] | (buffer2 [1] << 8));
	fread (buffer2, sizeof (buffer2), 1, archivo2);
	cab2 -> AudioFormat = (buffer2 [0] | (buffer2 [1] << 8));
	
	//Canales
	fread (buffer2, sizeof (buffer2), 1, archivo1);
	cab1 -> NumChannels = (buffer2 [0] | (buffer2 [1] << 8));
	fread (buffer2, sizeof (buffer2), 1, archivo2);
	cab2 -> NumChannels = (buffer2 [0] | (buffer2 [1] << 8));

	//SampleRate
	fread (buffer4, sizeof (buffer4), 1, archivo1);
	cab1 -> SampleRate = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
	fread (buffer4, sizeof (buffer4), 1, archivo2);
	cab2 -> SampleRate = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
	
	//ByteRate
	fread (buffer4, sizeof (buffer4), 1, archivo1);
	cab1 -> ByteRate = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
	fread (buffer4, sizeof (buffer4), 1, archivo2);
	cab2 -> ByteRate = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));

	//Block Align
	fread (buffer2, sizeof (buffer2), 1, archivo1);
	cab1 -> BlockAlign = (buffer2 [0] | (buffer2 [1] << 8));
	fread (buffer2, sizeof (buffer2), 1, archivo2);
	cab2 -> BlockAlign = (buffer2 [0] | (buffer2 [1] << 8));
	
	//Bits per Sample
	fread (buffer2, sizeof (buffer2), 1, archivo1);
	cab1 -> BitsPerSample = (buffer2 [0] | (buffer2 [1] << 8));
	fread (buffer2, sizeof (buffer2), 1, archivo2);
	cab2 -> BitsPerSample = (buffer2 [0] | (buffer2 [1] << 8));

	//SubChunk2ID
	fread (cab1 -> SubChunk2ID, sizeof (cab1 -> SubChunk2ID), 1, archivo1);	
	fread (cab2 -> SubChunk2ID, sizeof (cab2 -> SubChunk2ID), 1, archivo2);

	//SubChunk2Size
	fread (buffer4, sizeof (buffer4), 1, archivo1);
	cab1 -> SubChunk2Size = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
	fread (buffer4, sizeof (buffer4), 1, archivo2);
	cab2 -> SubChunk2Size = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
}

void imprimir_cabecera (cabecera * cab, int tipo)
{
	char * formatoArchivo = (char *) malloc (sizeof (char));
	if (tipo == 1)
		strcpy (formatoArchivo, "Archivo 1");
	else if (tipo == 2)
		strcpy (formatoArchivo, "Archivo 2");
	else
		strcpy (formatoArchivo, "Archivo de Salida");
	printf ("\n\n\n\t\t\t\t%s\n", formatoArchivo);
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

void copiar_cabecera (cabecera * cab1, FILE * archivo1, FILE * salida)
{
	rewind (archivo1);
	rewind (salida);

	//ChunkID
	fread (cab1 -> ChunkID, sizeof (cab1 -> ChunkID), 1, archivo1);
	fwrite (cab1 -> ChunkID, sizeof (cab1 -> ChunkID), 1, salida);

	//ChunkSize
	fread (buffer4, sizeof (buffer4), 1, archivo1);
	fwrite (buffer4, sizeof (buffer4), 1, salida);
	cab1 -> ChunkSize = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));

	//Formato "Fmt"
	fread (cab1 -> Format, sizeof (cab1 -> Format), 1, archivo1);
	fwrite (cab1 -> Format, sizeof (cab1 -> Format), 1, salida);

	//SubChunk1ID Formato de datos "fmt"
	fread (cab1 -> SubChunk1ID, sizeof (cab1 -> SubChunk1ID), 1, archivo1);
	fwrite (cab1 -> SubChunk1ID, sizeof (cab1 -> SubChunk1ID), 1, salida);

	//SubChunk1Size
	fread (buffer4, sizeof (buffer4), 1, archivo1);
	fwrite (buffer4, sizeof (buffer4), 1, salida);
	cab1 -> SubChunk1Size = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
	
	// Formato de audio
	fread (buffer2, sizeof (buffer2), 1, archivo1);
	fwrite (buffer2, sizeof (buffer2), 1, salida);
	cab1 -> AudioFormat = (buffer2 [0] | (buffer2 [1] << 8));
	
	//Canales
	fread (buffer2, sizeof (buffer2), 1, archivo1);
	fwrite (buffer2, sizeof (buffer2), 1, salida);
	cab1 -> NumChannels = (buffer2 [0] | (buffer2 [1] << 8));

	//SampleRate
	fread (buffer4, sizeof (buffer4), 1, archivo1);
	fwrite (buffer4, sizeof (buffer4), 1, salida);
	cab1 -> SampleRate = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
	
	//ByteRate
	fread (buffer4, sizeof (buffer4), 1, archivo1);
	fwrite (buffer4, sizeof (buffer4), 1, salida);
	cab1 -> ByteRate = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));

	//Block Align
	fread (buffer2, sizeof (buffer2), 1, archivo1);
	fwrite (buffer2, sizeof (buffer2), 1, salida);
	cab1 -> BlockAlign = (buffer2 [0] | (buffer2 [1] << 8));
	
	//Bits per Sample
	fread (buffer2, sizeof (buffer2), 1, archivo1);
	fwrite (buffer2, sizeof (buffer2), 1, salida);
	cab1 -> BitsPerSample = (buffer2 [0] | (buffer2 [1] << 8));

	//SubChunk2ID
	fread (cab1 -> SubChunk2ID, sizeof (cab1 -> SubChunk2ID), 1, archivo1);
	fwrite (cab1 -> SubChunk2ID, sizeof (cab1 -> SubChunk2ID), 1, salida);

	//SubChunk2Size
	fread (buffer4, sizeof (buffer4), 1, archivo1);
	fwrite (buffer4, sizeof (buffer4), 1, salida);
	cab1 -> SubChunk2Size = (buffer4 [0] | (buffer4 [1] << 8) | (buffer4 [2] << 16) | (buffer4 [3] << 24));
}
