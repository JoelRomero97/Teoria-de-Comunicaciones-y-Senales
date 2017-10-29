#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cabecera.h"

int i;					//Variable global para manejar ciclos

FILE * abre_archivo (char * archivo1, char * archivo2, char * salida, int tipo)
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
	fread (cab1 -> ChunkID, sizeof (char), 4, archivo1);
	fread (cab2 -> ChunkID, sizeof (char), 4, archivo2);

	//ChunkSize 
	fread (&cab1 -> ChunkSize, sizeof (int), 1, archivo1);
	fread (&cab2 -> ChunkSize, sizeof (int), 1, archivo2);

	//Formato "Fmt"
	fread (cab1 -> Format, sizeof (char), 4, archivo1);
	fread (cab2 -> Format, sizeof (char), 4, archivo2);

	//SubChunk1ID Formato de datos "fmt"
	fread (cab1 -> SubChunk1ID, sizeof (char), 4, archivo1);
	fread (cab2 -> SubChunk1ID, sizeof (char), 4, archivo2);

	//SubChunk1Size
	fread (&cab1 -> SubChunk1Size, sizeof (int), 1, archivo1);
	fread (&cab2 -> SubChunk1Size, sizeof (int), 1, archivo2);
	
	// Formato de audio
	fread (&cab1 -> AudioFormat, sizeof (short), 1, archivo1);
	fread (&cab2 -> AudioFormat, sizeof (short), 1, archivo2);

	//Canales
	fread (&cab1 -> NumChannels, sizeof (short), 1, archivo1);
	fread (&cab2 -> NumChannels, sizeof (short), 1, archivo2);

	//SampleRate
	fread (&cab1 -> SampleRate, sizeof (int), 1, archivo1);
	fread (&cab2 -> SampleRate, sizeof (int), 1, archivo2);

	//ByteRate
	fread (&cab1 -> ByteRate, sizeof (int), 1, archivo1);
	fread (&cab2 -> ByteRate, sizeof (int), 1, archivo2);

	//Block Align
	fread (&cab1 -> BlockAlign, sizeof (short), 1, archivo1);
	fread (&cab2 -> BlockAlign, sizeof (short), 1, archivo2);

	//Bits per Sample
	fread (&cab1 -> BitsPerSample, sizeof (short), 1, archivo1);
	fread (&cab2 -> BitsPerSample, sizeof (short), 1, archivo2);

	//SubChunk2ID
	fread (cab1 -> SubChunk2ID, sizeof (char), 4, archivo1);
	fread (cab2 -> SubChunk2ID, sizeof (char), 4, archivo2);

	//SubChunk2Size
	fread (&cab1 -> SubChunk2Size, sizeof (int), 1, archivo1);
	fread (&cab2 -> SubChunk2Size, sizeof (int), 1, archivo2);
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

void copiar_cabecera (FILE * entrada, FILE * salida, cabecera * cab)
{
	rewind (entrada);
	rewind (salida);
	
	//ChunkID 
	fread (cab -> ChunkID, sizeof (char), 4, entrada);
	fwrite (cab -> ChunkID, sizeof (char), 4, salida);

	//ChunkSize 
	fread (&cab -> ChunkSize, sizeof (int), 1, entrada);
	fwrite (&cab -> ChunkSize, sizeof (int), 1, salida);

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
	
	//Canales
	fread (&cab -> NumChannels, sizeof (short), 1, entrada);
	fwrite (&cab -> NumChannels, sizeof (short), 1, salida);

	//SampleRate
	fread (&cab -> SampleRate, sizeof (int), 1, entrada);
	fwrite (&cab -> SampleRate, sizeof (int), 1, salida);
	
	//ByteRate
	fread (&cab -> ByteRate, sizeof (int), 1, entrada);
	fwrite (&cab -> ByteRate, sizeof (int), 1, salida);

	//Block Align
	fread (&cab -> BlockAlign, sizeof (short), 1, entrada);
	fwrite (&cab -> BlockAlign, sizeof (short), 1, salida);
	
	//Bits per Sample
	fread (&cab -> BitsPerSample, sizeof (short), 1, entrada);
	fwrite (&cab -> BitsPerSample, sizeof (short), 1, salida);

	//SubChunk2ID
	fread (cab -> SubChunk2ID, sizeof (char), 4, entrada);
	fwrite (cab -> SubChunk2ID, sizeof (char), 4, salida);

	//SubChunk2Size
	fread (&cab -> SubChunk2Size, sizeof (int), 1, entrada);
	fwrite (&cab -> SubChunk2Size, sizeof (int), 1, salida);
}
