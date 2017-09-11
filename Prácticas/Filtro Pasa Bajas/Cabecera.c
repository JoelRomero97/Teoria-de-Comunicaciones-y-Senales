#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Cabecera.h"
#define PI 3.14159265
#define FREC_CORTE 1000

int i;					//Variable global para manejar ciclos

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
	lectura = fread(cab -> ChunkID,sizeof(cab -> ChunkID),1,archivoEntrada);
	printf("\n\n\n(1-4) Chunk ID: %s\n\n",cab -> ChunkID);
	escritura = fwrite (cab -> ChunkID, sizeof (cab -> ChunkID), 1, archivoSalida);

	//ChunkSize 
	//Se convierten los datos a entero
	lectura = fread(buffer4, sizeof(buffer4),1,archivoEntrada);
	escritura = fwrite(buffer4, sizeof(buffer4),1,archivoSalida);
	cab -> ChunkSize = (buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24));
	printf("(5-8) ChunkSize:  %u\n\n",cab -> ChunkSize);

	//Formato "Fmt"
	lectura = fread(cab -> Format, sizeof(cab -> Format),1,archivoEntrada);
	printf("(9-12) Format: %s\n\n",cab -> Format);
	escritura = fwrite (cab -> Format, sizeof (cab -> Format), 1, archivoSalida);


	//SubChunk1ID Formato de datos "fmt"
	lectura = fread(cab -> SubChunk1ID,sizeof(cab -> SubChunk1ID),1,archivoEntrada);
	printf("(13-16) SubChunk 1 ID: %s\n\n",cab -> SubChunk1ID);
	escritura = fwrite (cab -> SubChunk1ID, sizeof (cab -> SubChunk1ID), 1, archivoSalida);


	//SubChunk1Size
	lectura = fread(buffer4, sizeof(buffer4),1,archivoEntrada);
	escritura = fwrite(buffer4, sizeof(buffer4),1,archivoSalida);
	cab -> SubChunk1Size = buffer4[0] | (buffer4[1]<<8) | (buffer4[1]<<16) | (buffer4[1]<<24);	
	printf("(17-20) SubChunk 1 Size: %u\n\n",cab -> SubChunk1Size);

	
	// Formato de audio
	lectura = fread(buffer2, sizeof(buffer2),1,archivoEntrada);
	escritura = fwrite(buffer2, sizeof(buffer2),1,archivoSalida);
	cab -> AudioFormat = buffer2[0] | (buffer2[1]<<8);
	if (cab -> AudioFormat == 1)
		strcpy(formatoArchivo,"PCM");
	printf("(21-22) Audio Format: %u,%s\n\n",cab -> AudioFormat,formatoArchivo);
	
	//Canales
	lectura = fread(buffer2, sizeof(buffer2),1,archivoEntrada);
	escritura = fwrite(buffer2, sizeof(buffer2),1,archivoSalida);
	cab -> NumChannels = buffer2[0] | (buffer2[1]<<8);
	if (cab -> NumChannels == 1)
		strcpy(formatoArchivo,"Mono");
	else 
		strcpy(formatoArchivo,"Stereo");
	printf("(23-24) Number of Channels: %u, Tipo: %s\n\n",cab -> NumChannels,formatoArchivo);

	//SampleRate
	lectura = fread(buffer4, sizeof(buffer4),1,archivoEntrada);
	escritura = fwrite(buffer4, sizeof(buffer4),1,archivoSalida);
	cab -> SampleRate = buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24);	
	printf("(25-28) Sample Rate: %u\n\n",cab -> SampleRate);
	
	
	//ByteRate
	lectura = fread(buffer4, sizeof(buffer4),1,archivoEntrada);
	escritura = fwrite(buffer4, sizeof(buffer4),1,archivoSalida);
	cab -> ByteRate = buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24);	
	printf("(29-32) Byte Rate: %u BitRate: %u\n\n",cab -> ByteRate,cab -> ByteRate*8);

	//Block Align
	lectura = fread(buffer2, sizeof(buffer2),1,archivoEntrada);
	escritura = fwrite(buffer2, sizeof(buffer2),1,archivoSalida);
	cab -> BlockAlign = buffer2[0] | (buffer2[1]<<8);
	printf("(33-34) Block Align: %u\n\n",cab -> BlockAlign);

	//Bits per Sample
	lectura = fread(buffer2, sizeof(buffer2),1,archivoEntrada);
	escritura = fwrite(buffer2, sizeof(buffer2),1,archivoSalida);
	cab -> BitsPerSample = buffer2[0] | (buffer2[1]<<8);
	printf("(35-36) Bits Per Sample: %u\n\n",cab -> BitsPerSample);

	//SubChunk2ID
	lectura = fread(cab -> SubChunk2ID,sizeof(cab -> SubChunk2ID),1,archivoEntrada);
	printf("(37-40) SubChunk 2 ID: %s\n\n",cab -> SubChunk2ID);
	escritura = fwrite(cab -> SubChunk2ID,sizeof(cab -> SubChunk2ID),1,archivoSalida);


	//SubChunk2Size
	lectura = fread(buffer4, sizeof(buffer4),1,archivoEntrada);
	escritura = fwrite(buffer4, sizeof(buffer4),1,archivoSalida);
	cab -> SubChunk2Size = buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24);	
	printf("(41-44) SubChunk 2 Size: %u\n\n",cab -> SubChunk2Size);
}

float * generaImpulso ()
{
	float * impulso = (float *) malloc (sizeof (float) * 20);
	for (i = 0; i < 20; i ++)
	{
		impulso [i] = (exp ((-2 * PI * FREC_CORTE * i) / 44100));			//Fórmula de filtro RC con fc = 1,000 Hz
	}
	return impulso;
}

float convolucion (float * entrada, float * impulso, int ciclo)
{
	float respuesta;
	float aux, * entradaAux;
	for (i = 0; i < ciclo; i ++)
		entradaAux [i] = entrada [i];
	float * inicio = entradaAux;
	float * final = &entradaAux [ciclo - 1];

	//Recorremos cliclo - 1 posiciones a la izquierda los elementos
	for(;inicio <= final;inicio ++, final --)
	{
		aux = (* inicio);
		(* inicio) = (* final);
		(* final) = aux;
	}

	//Imprimimos la entrada
	printf("\n\nENTRADA:\n");
	for (i = 0; i < ciclo; i ++)
		printf("%.2f  ", entradaAux [i]);

	//Realizamos la convolución
	for (i = 0, respuesta = 0; i < ciclo; i ++)
		if (entradaAux [i] != 0)
			respuesta += (entradaAux [i] * impulso [i]);
	if (respuesta >= -32767 && respuesta <= 32767)
		return respuesta;
	else
		return 0;
}