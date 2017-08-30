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
	int lectura, escritura;
	unsigned char buffer4[4], buffer2 [2], * formatoArchivo;
	formatoArchivo = (char *) malloc (sizeof (char));

	//ChunkID 
	lectura = fread(cab -> chunkID,sizeof(cab -> chunkID),1,archivoEntrada);
	printf("(1-4) chunkID: %s\n\n",cab -> chunkID);
	escritura = fwrite (cab -> chunkID, sizeof (cab -> chunkID), 1, archivoSalida);

	//ChunkSize 
	//Se convierten los datos a entero
	lectura = fread(buffer4, sizeof(buffer4),1,archivoEntrada);
	escritura = fwrite(buffer4, sizeof(buffer4),1,archivoSalida);
	cab -> ChunkSize = (buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24));
	printf("(5-8) ChunkSize:  %u\n\n",cab -> ChunkSize);

	//Formato "format"
		
	lectura = fread(cab -> format, sizeof(cab -> format),1,archivoEntrada);
	printf("(9-12) Formato : %s\n\n",cab -> format);
	escritura = fwrite (cab -> format, sizeof (cab -> format), 1, archivoSalida);


	//SubChunk1ID formato de datos "fmt"
	
	lectura = fread(cab -> SubChunk1ID,sizeof(cab -> SubChunk1ID),1,archivoEntrada);
	printf("(13-16) SubChunk1ID: %s\n\n",cab -> SubChunk1ID);
	escritura = fwrite (cab -> SubChunk1ID, sizeof (cab -> SubChunk1ID), 1, archivoSalida);


	//SubChunk1Size
	lectura = fread(buffer4, sizeof(buffer4),1,archivoEntrada);
	escritura = fwrite(buffer4, sizeof(buffer4),1,archivoSalida);
	cab -> SubChunk1Size = buffer4[0] | (buffer4[1]<<8) | (buffer4[1]<<16) | (buffer4[1]<<24);	
	printf("(17-20) SubChunk1Size: %u\n\n",cab -> SubChunk1Size);

	
	// Formato de audio

	lectura = fread(buffer2, sizeof(buffer2),1,archivoEntrada);
	escritura = fwrite(buffer2, sizeof(buffer2),1,archivoSalida);
	cab -> AudioFormat = buffer2[0] | (buffer2[1]<<8);
	if (cab -> AudioFormat == 1)
		strcpy(formatoArchivo,"PCM");
	printf("(21-22) Formato de Audio: %u,%s\n\n",cab -> AudioFormat,formatoArchivo);
	
	//Canales

	lectura = fread(buffer2, sizeof(buffer2),1,archivoEntrada);
	escritura = fwrite(buffer2, sizeof(buffer2),1,archivoSalida);
	cab -> no_canal = buffer2[0] | (buffer2[1]<<8);
	if (cab -> no_canal == 1)
		strcpy(formatoArchivo,"Mono");
	else 
		strcpy(formatoArchivo,"Stereo");
	printf("(23-24) Numero de canal: %u, Tipo: %s\n\n",cab -> no_canal,formatoArchivo);

	//SampleRate

	lectura = fread(buffer4, sizeof(buffer4),1,archivoEntrada);
	escritura = fwrite(buffer4, sizeof(buffer4),1,archivoSalida);
	cab -> SimpleRate = buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24);	
	printf("(25-28) SampleRate: %u\n\n",cab -> SimpleRate);
	
	
	//ByteRate
	lectura = fread(buffer4, sizeof(buffer4),1,archivoEntrada);
	escritura = fwrite(buffer4, sizeof(buffer4),1,archivoSalida);
	cab -> ByteRate = buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24);	
	printf("(29-32) ByteRate: %u BitRate: %u\n\n",cab -> ByteRate,cab -> ByteRate*8);

	//Block Align
	lectura = fread(buffer2, sizeof(buffer2),1,archivoEntrada);
	escritura = fwrite(buffer2, sizeof(buffer2),1,archivoSalida);
	cab -> block_align = buffer2[0] | (buffer2[1]<<8);
	printf("(33-34) BlockAlign: %u\n\n",cab -> block_align);

	//Bits per Sample
	lectura = fread(buffer2, sizeof(buffer2),1,archivoEntrada);
	escritura = fwrite(buffer2, sizeof(buffer2),1,archivoSalida);
	cab -> BitsPerSample = buffer2[0] | (buffer2[1]<<8);
	printf("(35-36) BitsPerSample: %u\n\n",cab -> BitsPerSample);

	//SubChunk2ID
	lectura = fread(cab -> SubChunk2ID,sizeof(cab -> SubChunk2ID),1,archivoEntrada);
	printf("(37-40) SubChunk2ID: %s\n\n",cab -> SubChunk2ID);
	escritura = fwrite(cab -> SubChunk2ID,sizeof(cab -> SubChunk2ID),1,archivoSalida);


	//SubChunk2Size
	lectura = fread(buffer4, sizeof(buffer4),1,archivoEntrada);
	escritura = fwrite(buffer4, sizeof(buffer4),1,archivoSalida);
	cab -> SubChunk2Size = buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24);	
	printf("(41-44) SubChunk2Size: %u\n\n",cab -> SubChunk2Size);
}