#include <stdio.h>
#include <stdlib.h>
#include "Cabecera.h"

FILE * abreArchivo (char * nombreArch, char * nombreModificado, int tipo)
{
	FILE * pt1, * pt2;
	pt1 = fopen (nombreArch,"rb");
	if (pt1 == NULL)
	{
		printf("Error al abrir archivo '%s'.\n", nombreArch);
		exit(0);
	}
	
	//Abrimos el archivo a escribir en modo binario	
	pt2 = fopen (nombreModificado,"wb");
	if (pt2 == NULL)
	{
		printf("Error al crear el archivo '%s'.\n", nombreModificado);
		exit(1);
	}
	if (tipo == 1)
	{
		printf("Archivo '%s' abierto correctamente.\n", nombreArch);
		return pt1;
	}
	else
	{
		printf("Archivo '%s' creado correctamente.\n", nombreModificado);
		return pt2;
	}
}

void leerCabecera (FILE * archivoEntrada, FILE * archivoSalida, cabecera * cab)
{
	//ChunkID 
	fread(cab -> ChunkID,sizeof(cab -> ChunkID),1,archivoEntrada);
	fwrite (cab -> ChunkID, sizeof (cab -> ChunkID), 1, archivoSalida);

	//ChunkSize 
	fread(&cab -> ChunkSize, sizeof(cab -> ChunkSize),1,archivoEntrada);
	fwrite(&cab -> ChunkSize, sizeof(cab -> ChunkSize),1,archivoSalida);
	
	//Formato "Fmt"
	fread(cab -> Format, sizeof(cab -> Format),1,archivoEntrada);
	fwrite (cab -> Format, sizeof (cab -> Format), 1, archivoSalida);

	//SubChunk1ID Formato de datos "fmt"
	fread(cab -> SubChunk1ID,sizeof(cab -> SubChunk1ID),1,archivoEntrada);
	fwrite (cab -> SubChunk1ID, sizeof (cab -> SubChunk1ID), 1, archivoSalida);

	//SubChunk1Size
	fread(&cab -> SubChunk1Size, sizeof(cab -> SubChunk1Size),1,archivoEntrada);
	fwrite(&cab -> SubChunk1Size, sizeof(cab -> SubChunk1Size),1,archivoSalida);
	
	// Formato de audio
	fread(&cab -> AudioFormat, sizeof(cab -> AudioFormat),1,archivoEntrada);
	fwrite(&cab -> AudioFormat, sizeof(cab -> AudioFormat),1,archivoSalida);
	
	//Canales
	fread(&cab -> NumChannels, sizeof(cab -> NumChannels),1,archivoEntrada);
	fwrite(&cab -> NumChannels, sizeof(cab -> NumChannels),1,archivoSalida);

	//SampleRate
	fread(&cab -> SampleRate, sizeof(cab -> SampleRate),1,archivoEntrada);
	fwrite(&cab -> SampleRate, sizeof(cab -> SampleRate),1,archivoSalida);
	
	//ByteRate
	fread(&cab -> ByteRate, sizeof(cab -> ByteRate),1,archivoEntrada);
	fwrite(&cab -> ByteRate, sizeof(cab -> ByteRate),1,archivoSalida);	

	//Block Align
	fread(&cab -> BlockAlign, sizeof(cab -> BlockAlign),1,archivoEntrada);
	fwrite(&cab -> BlockAlign, sizeof(cab -> BlockAlign),1,archivoSalida);

	//Bits per Sample
	fread(&cab -> BitsPerSample, sizeof(cab -> BitsPerSample),1,archivoEntrada);
	fwrite(&cab -> BitsPerSample, sizeof(cab -> BitsPerSample),1,archivoSalida);
	
	//SubChunk2ID
	fread(cab -> SubChunk2ID,sizeof(cab -> SubChunk2ID),1,archivoEntrada);
	fwrite(cab -> SubChunk2ID,sizeof(cab -> SubChunk2ID),1,archivoSalida);

	//SubChunk2Size
	fread(&cab -> SubChunk2Size, sizeof(cab -> SubChunk2Size),1,archivoEntrada);
	fwrite(&cab -> SubChunk2Size, sizeof(cab -> SubChunk2Size),1,archivoSalida);	
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
