#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Cabecera.h"
#define PI 3.14159265
#define FREC_CORTE 1000
#define TAM_ARREGLO 20

int i;					//Variable global para manejar ciclos

FILE * abreArchivo (char * archivo1, char * archivo2, char * salida, int tipo)
{
	FILE * archivo_1, * archivo_2, * archivo_salida;
	archivo_1 = fopen (archivo1,"rb");
	if (archivo_1 == NULL)
	{
		printf("Error al abrir archivo '%s'.\n", archivo1);
		exit (0);
	}

	archivo_2 = fopen (archivo1,"rb");
	if (archivo_2 == NULL)
	{
		printf("Error al abrir archivo '%s'.\n", archivo1);
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

void leerCabecera (FILE * archivo1, FILE * archivo2, FILE * archivoSalida, cabecera * cab_1, cabecera * cab_2)
{
	//Ponemos los apuntadores de todos los archivos al inicio
	rewind (archivo1);
	rewind (archivo2);
	rewind (archivoSalida);

	//ChunkID
	fread (cab_1 -> ChunkID, sizeof (cab_1 -> ChunkID), 1, archivo1);
	fread (cab_2 -> ChunkID, sizeof (cab_2 -> ChunkID), 1, archivo2);

	//ChunkSize
	/*fread (buffer4_1, sizeof (buffer4_1), 1, archivo1);
	fread (buffer4_2, sizeof (buffer4_2), 1, archivo2);
	cab_1 -> ChunkSize = (buffer4_1 [0] | (buffer4_1 [1] << 8) | (buffer4_1 [2] << 16) | (buffer4_1 [3] << 24));
	cab_2 -> ChunkSize = (buffer4_2 [0] | (buffer4_2 [1] << 8) | (buffer4_2 [2] << 16) | (buffer4_2 [3] << 24));*/
	fread (&cab_1 -> ChunkSize, sizeof (cab_1 -> ChunkSize), 1, archivo1);
	fread (&cab_2 -> ChunkSize, sizeof (cab_2 -> ChunkSize), 1, archivo2);

	//Formato "Fmt"
	fread (cab_1 -> Format, sizeof (cab_1 -> Format), 1, archivo1);
	fread (cab_2 -> Format, sizeof (cab_2 -> Format), 1, archivo2);

	//SubChunk1ID Formato de datos "fmt"
	fread (cab_1 -> SubChunk1ID, sizeof (cab_1 -> SubChunk1ID), 1, archivo1);
	fread (cab_2 -> SubChunk1ID, sizeof (cab_2 -> SubChunk1ID), 1, archivo2);

	//SubChunk1Size
	/*fread (buffer4_1, sizeof (buffer4_1), 1, archivo1);
	fread (buffer4_2, sizeof (buffer4_2), 1, archivo2);
	cab_1 -> SubChunk1Size = buffer4_1 [0] | (buffer4_1 [1] << 8) | (buffer4_1 [1] << 16) | (buffer4_1 [1] << 24);
	cab_2 -> SubChunk1Size = buffer4_2 [0] | (buffer4_2 [1] << 8) | (buffer4_2 [1] << 16) | (buffer4_2 [1] << 24);*/
	fread (&cab_1 -> SubChunk1Size, sizeof (cab_1 -> SubChunk1Size), 1, archivo1);
	fread (&cab_2 -> SubChunk1Size, sizeof (cab_2 -> SubChunk1Size), 1, archivo2);
	
	// Formato de audio
	/*fread (buffer2_1, sizeof (buffer2_1), 1, archivo1);
	fread (buffer2_2, sizeof (buffer2_2), 1, archivo2);
	fwrite (buffer2_1, sizeof (buffer2_1), 1, archivoSalida);
	cab_1 -> AudioFormat = buffer2_1 [0] | (buffer2_1 [1] << 8);
	cab_2 -> AudioFormat = buffer2_2 [0] | (buffer2_2 [1] << 8);*/
	fread (&cab_1 -> AudioFormat, sizeof (cab_1 -> AudioFormat), 1, archivo1);
	fread (&cab_2 -> AudioFormat, sizeof (cab_2 -> AudioFormat), 1, archivo2);
	
	//Canales
	/*fread (buffer2_1, sizeof (buffer2_1), 1, archivo1);
	fread (buffer2_2, sizeof (buffer2_2), 1, archivo2);
	fwrite (buffer2_1, sizeof (buffer2_1), 1, archivoSalida);
	cab_1 -> NumChannels = buffer2_1 [0] | (buffer2_1 [1] << 8);
	cab_2 -> NumChannels = buffer2_2 [0] | (buffer2_2 [1] << 8);*/
	fread (&cab_1 -> NumChannels, sizeof (cab_1 -> NumChannels), 1, archivo1);
	fread (&cab_2 -> NumChannels, sizeof (cab_2 -> NumChannels), 1, archivo2);
	
	//SampleRate
	/*fread (buffer4_1, sizeof (buffer4_1), 1, archivo1);
	fread (buffer4_2, sizeof (buffer4_2), 1, archivo2);
	fwrite (buffer4_1, sizeof (buffer4_1), 1, archivoSalida);
	cab_1 -> SampleRate = buffer4_1 [0] | (buffer4_1 [1] << 8) | (buffer4_1 [2] << 16) | (buffer4_1 [3] << 24);
	cab_2 -> SampleRate = buffer4_2 [0] | (buffer4_2 [1] << 8) | (buffer4_2 [2] << 16) | (buffer4_2 [3] << 24);*/
	fread (&cab_1 -> SampleRate, sizeof (cab_1 -> SampleRate), 1, archivo1);
	fread (&cab_2 -> SampleRate, sizeof (cab_2 -> SampleRate), 1, archivo2);
	
	//ByteRate
	/*fread (buffer4_1, sizeof(buffer4_1), 1, archivo1);
	fread (buffer4_2, sizeof(buffer4_2), 1, archivo2);
	fwrite (buffer4_1, sizeof (buffer4_1), 1, archivoSalida);
	cab_1 -> ByteRate = buffer4_1 [0] | (buffer4_1 [1] << 8) | (buffer4_1 [2] << 16) | (buffer4_1 [3] << 24);	
	cab_2 -> ByteRate = buffer4_2 [0] | (buffer4_2 [1] << 8) | (buffer4_2 [2] << 16) | (buffer4_2 [3] << 24);*/
	fread (&cab_1 -> ByteRate, sizeof(cab_1 -> ByteRate), 1, archivo1);
	fread (&cab_2 -> ByteRate, sizeof(cab_2 -> ByteRate), 1, archivo2);
	
	//Block Align
	/*fread (buffer2_1, sizeof (buffer2_1), 1, archivo1);
	fread (buffer2_2, sizeof (buffer2_2), 1, archivo2);
	fwrite (buffer2_1, sizeof (buffer2_1), 1, archivoSalida);
	cab_1 -> BlockAlign = buffer2_1 [0] | (buffer2_1 [1] << 8);
	cab_2 -> BlockAlign = buffer2_2 [0] | (buffer2_2 [1] << 8);*/
	fread (&cab_1 -> BlockAlign, sizeof (cab_1 -> BlockAlign), 1, archivo1);
	fread (&cab_2 -> BlockAlign, sizeof (cab_2 -> BlockAlign), 1, archivo2);

	//Bits per Sample
	/*fread (buffer2_1, sizeof (buffer2_1), 1, archivo1);
	fread (buffer2_2, sizeof (buffer2_2), 1, archivo2);
	fwrite (buffer2_1, sizeof (buffer2_1), 1, archivoSalida);
	cab_1 -> BitsPerSample = buffer2_1 [0] | (buffer2_1 [1] << 8);
	cab_2 -> BitsPerSample = buffer2_2 [0] | (buffer2_2 [1] << 8);*/
	fread (&cab_1 -> BitsPerSample, sizeof (cab_1 -> BitsPerSample), 1, archivo1);
	fread (&cab_2 -> BitsPerSample, sizeof (cab_2 -> BitsPerSample), 1, archivo2);
	
	//SubChunk2ID
	fread (cab_1 -> SubChunk2ID, sizeof (cab_1 -> SubChunk2ID), 1, archivo1);
	fread (cab_2 -> SubChunk2ID, sizeof (cab_2 -> SubChunk2ID), 1, archivo2);
	
	//SubChunk2Size
	/*fread (buffer4_1, sizeof (buffer4_1), 1, archivo1);
	fread (buffer4_2, sizeof (buffer4_2), 1, archivo2);
	cab_1 -> SubChunk2Size = buffer4_1 [0] | (buffer4_1 [1] << 8) | (buffer4_1 [2] << 16) | (buffer4_1 [3] << 24);
	cab_2 -> SubChunk2Size = buffer4_2 [0] | (buffer4_2 [1] << 8) | (buffer4_2 [2] << 16) | (buffer4_2 [3] << 24);*/
	fread (&cab_1 -> SubChunk2Size, sizeof (cab_1 -> SubChunk2Size), 1, archivo1);
	fread (&cab_2 -> SubChunk2Size, sizeof (cab_2 -> SubChunk2Size), 1, archivo2);

	//Validación de los datos
	if ((cab_1 -> BitsPerSample) != (cab_2 -> BitsPerSample))
	{
		printf ("\n\nNo es posible realizar la multiplicacion debido a que no tiene los mismos bits por muestra\n\n");
		exit (0);
	}else if ((cab_1 -> SampleRate) != (cab_2 -> SampleRate))
	{
		printf ("\n\nNo es posible realizar la multiplicacion debido a que no tienen la misma frecuencia de muestreo\n\n");
		exit (0);
	}

	//Copiamos la cabecera correspondiente
	if ((cab_1 -> ChunkSize) >= (cab_2 -> ChunkSize))
	{
		fwrite (cab_1 -> ChunkID, sizeof (cab_1 -> ChunkID), 1, archivoSalida);
		fwrite (&cab_1 -> ChunkSize, sizeof (cab_1 -> ChunkSize), 1, archivoSalida);
		fwrite (cab_1 -> Format, sizeof (cab_1 -> Format), 1, archivoSalida);
		fwrite (cab_1 -> SubChunk1ID, sizeof (cab_1 -> SubChunk1ID), 1, archivoSalida);
		fwrite (&cab_1 -> SubChunk1Size, sizeof (cab_1 -> SubChunk1Size), 1, archivoSalida);
		fwrite (&cab_1 -> AudioFormat, sizeof (cab_1 -> AudioFormat), 1, archivoSalida);
		fwrite (&cab_1 -> NumChannels, sizeof (cab_1 -> NumChannels), 1, archivoSalida);
		fwrite (&cab_1 -> SampleRate, sizeof (cab_1 -> SampleRate), 1, archivoSalida);
		fwrite (&cab_1 -> ByteRate, sizeof (cab_1 -> ByteRate), 1, archivoSalida);
		fwrite (&cab_1 -> BlockAlign, sizeof (cab_1 -> BlockAlign), 1, archivoSalida);
		fwrite (&cab_1 -> BitsPerSample, sizeof (cab_1 -> BitsPerSample), 1, archivoSalida);
		fwrite (cab_1 -> SubChunk2ID, sizeof (cab_1 -> SubChunk2ID), 1, archivoSalida);
		fwrite (&cab_1 -> SubChunk2Size, sizeof (cab_1 -> SubChunk2Size), 1, archivoSalida);
	}else
	{
		fwrite (cab_2 -> ChunkID, sizeof (cab_2 -> ChunkID), 1, archivoSalida);
		fwrite (&cab_2 -> ChunkSize, sizeof (cab_2 -> ChunkSize), 1, archivoSalida);
		fwrite (cab_2 -> Format, sizeof (cab_2 -> Format), 1, archivoSalida);
		fwrite (cab_2 -> SubChunk1ID, sizeof (cab_2 -> SubChunk1ID), 1, archivoSalida);
		fwrite (&cab_2 -> SubChunk1Size, sizeof (cab_2 -> SubChunk1Size), 1, archivoSalida);
		fwrite (&cab_2 -> AudioFormat, sizeof (cab_2 -> AudioFormat), 1, archivoSalida);
		fwrite (&cab_2 -> NumChannels, sizeof (cab_2 -> NumChannels), 1, archivoSalida);
		fwrite (&cab_2 -> SampleRate, sizeof (cab_2 -> SampleRate), 1, archivoSalida);
		fwrite (&cab_2 -> ByteRate, sizeof (cab_2 -> ByteRate), 1, archivoSalida);
		fwrite (&cab_2 -> BlockAlign, sizeof (cab_2 -> BlockAlign), 1, archivoSalida);
		fwrite (&cab_2 -> BitsPerSample, sizeof (cab_2 -> BitsPerSample), 1, archivoSalida);
		fwrite (cab_2 -> SubChunk2ID, sizeof (cab_2 -> SubChunk2ID), 1, archivoSalida);
		fwrite (&cab_2 -> SubChunk2Size, sizeof (cab_2 -> SubChunk2Size), 1, archivoSalida);
	}
}

void imprimir_cabecera (cabecera * cab_1, cabecera * cab_2)
{
	char * cadena = (char *) malloc (sizeof (char));
	printf ("\t\t\tARCHIVO 1\n\n");
	printf ("(1-4) Chunk ID: %s\n", cab_1 -> ChunkID);
	printf ("(5-8) ChunkSize:  %u\n", cab_1 -> ChunkSize);
	printf ("(9-12) Format: %s\n", cab_1 -> Format);
	printf ("(13-16) SubChunk 1 ID: %s\n", cab_1 -> SubChunk1ID);
	printf ("(17-20) SubChunk 1 Size: %u\n", cab_1 -> SubChunk1Size);
	if (cab_1 -> AudioFormat == 1)
			strcpy (cadena, "PCM");
		printf ("(21-22) Audio Format: %u, %s\n", cab_1 -> AudioFormat, cadena);
	if (cab_1 -> NumChannels == 1)
			strcpy (cadena, "Mono");
		else
			strcpy (cadena,"Stereo");
	printf ("(23-24) Number of Channels: %u, Tipo: %s\n", cab_1 -> NumChannels,cadena);
	printf ("(25-28) Sample Rate: %u\n", cab_1 -> SampleRate);
	printf ("(29-32) Byte Rate: %u BitRate: %u\n", cab_1 -> ByteRate, cab_1 -> ByteRate*8);
	printf ("(33-34) Block Align: %u\n", cab_1 -> BlockAlign);
	printf ("(35-36) Bits Per Sample: %u\n", cab_1 -> BitsPerSample);
	printf ("(37-40) SubChunk 2 ID: %s\n", cab_1 -> SubChunk2ID);
	printf ("(41-44) SubChunk 2 Size: %u\n", cab_1 -> SubChunk2Size);

	printf ("\n\n\t\t\tARCHIVO 2\n\n");
	printf ("(1-4) Chunk ID: %s\n", cab_2 -> ChunkID);
	printf ("(5-8) ChunkSize:  %u\n", cab_2 -> ChunkSize);
	printf ("(9-12) Format: %s\n", cab_2 -> Format);
	printf ("(13-16) SubChunk 1 ID: %s\n", cab_2 -> SubChunk1ID);
	printf ("(17-20) SubChunk 1 Size: %u\n", cab_2 -> SubChunk1Size);
	if (cab_2 -> AudioFormat == 1)
			strcpy (cadena, "PCM");
		printf ("(21-22) Audio Format: %u, %s\n", cab_2 -> AudioFormat, cadena);
	if (cab_2 -> NumChannels == 1)
			strcpy (cadena, "Mono");
		else
			strcpy (cadena,"Stereo");
		printf ("(23-24) Number of Channels: %u, Tipo: %s\n", cab_2 -> NumChannels,cadena);
	printf ("(25-28) Sample Rate: %u\n", cab_2 -> SampleRate);
	printf ("(29-32) Byte Rate: %u BitRate: %u\n", cab_2 -> ByteRate, cab_2 -> ByteRate*8);
	printf ("(33-34) Block Align: %u\n", cab_2 -> BlockAlign);
	printf ("(35-36) Bits Per Sample: %u\n", cab_2 -> BitsPerSample);
	printf ("(37-40) SubChunk 2 ID: %s\n", cab_2 -> SubChunk2ID);
	printf ("(41-44) SubChunk 2 Size: %u\n", cab_2 -> SubChunk2Size);
}
