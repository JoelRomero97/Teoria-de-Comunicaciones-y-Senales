#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cabecera.h"

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
