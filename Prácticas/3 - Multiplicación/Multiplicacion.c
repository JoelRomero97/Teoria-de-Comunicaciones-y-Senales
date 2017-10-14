#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.c"
#define TAM_ARREGLO 20

////////////////////////////////////////////////////////////////////////////////////////
////								Multiplicacion.c 								////
////																				////
////																				////
//// Multiplicación de 2 señales cualesquiera para generar una nueva señal, sin 	////
//// embargo la complejidad del mismo, recae en que existen 2 tipos de archivos con ////
//// 1 y 2 canales, mono y estéreo respectivamente, por lo tanto para estéreo se 	////
//// debe considerar a la señal del canal 1 como real y al otro como imaginario.	////
//// NOTA: Los archivos generados para prueba, fueron creados con GoldWave.			////
////																				////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	FILE * archivo_1, *archivo_2, * archivoSalida;
	cabecera cab_1, cab_2;
	int i, j;
	short muestra1, muestra2;
	char * salida = (char *) malloc (sizeof (char));
	char * archivo1 = (char *) malloc (sizeof (char));
	char * archivo2 = (char *) malloc (sizeof (char));
	system ("cls");
	if (argc < 4)
	{
		printf("\nError, faltan argumentos.\n\n");
		printf ("Ejemplo: '%s Archivo1.wav Archivo2.wav Salida.wav'\n\n", argv [0]);
		exit (0);
	}else
	{
		archivo1 = (char *) argv [1];
		archivo2 = (char *) argv [2];
		salida = (char *) argv [3];
	}

	//Abrimos los archivos en modo binario
	archivo_1 = abreArchivo (archivo1, archivo2, salida, 1);
	archivo_2 = abreArchivo (archivo1, archivo2, salida, 2);
	archivoSalida = abreArchivo (archivo1, archivo2, salida, 3);

	//Leemos e imprimimos la cabecera del archivo wav
	leerCabecera (archivo_1, archivo_2, archivoSalida, &cab_1, &cab_2);
	imprimir_cabecera (&cab_1, &cab_2);

	if ((cab_1.SubChunk2Size) >= (cab_2.SubChunk2Size))
	{
		for (i = 0, j = 0; i < cab_1.SubChunk2Size; i ++, j ++)
		{
			fread (&muestra1, sizeof (short), 1, archivo_1);
			if (j < cab_2.SubChunk2Size)
				fread (&muestra2, sizeof (short), 1, archivo_2);
			else
				muestra2 = 0;
			float muestra1_1 = (muestra1 / 32767);
			float muestra2_1 = (muestra2 / 32767);
			float resultado = (muestra1_1 * muestra2_1);
			muestra1 = (resultado * 32767);
			fwrite (&muestra1, sizeof (short), 1, archivoSalida);
		}
	}else
	{
		for (i = 0, j = 0; i < cab_2.SubChunk2Size; i ++, j++)
		{
			if (j < cab_1.SubChunk2Size)
				fread (&muestra1, sizeof (short), 1, archivo_1);
			else
				muestra1 = 0;
			fread (&muestra2, sizeof (short), 1, archivo_2);
			float muestra1_1 = (muestra1 / 32767);
			float muestra2_1 = (muestra2 / 32767);
			float resultado = (muestra1_1 * muestra2_1);
			muestra1 = (resultado * 32767);
			fwrite (&muestra1, sizeof (short), 1, archivoSalida);
		}
	}
	rewind (archivoSalida);
	char * cadena = (char *) malloc (sizeof (char));
	
	fread (cab_1.ChunkID, sizeof (cab_1.ChunkID), 1, archivoSalida);
	fread (&cab_1.ChunkSize, sizeof (cab_1.ChunkSize), 1, archivoSalida);
	fread (cab_1.Format, sizeof (cab_1.Format), 1, archivoSalida);
	fread (cab_1.SubChunk1ID, sizeof (cab_1.SubChunk1ID), 1, archivoSalida);
	fread (&cab_1.SubChunk1Size, sizeof (cab_1.SubChunk1Size), 1, archivoSalida);
	fread (&cab_1.AudioFormat, sizeof (cab_1.AudioFormat), 1, archivoSalida);
	fread (&cab_1.NumChannels, sizeof (cab_1.NumChannels), 1, archivoSalida);
	fread (&cab_1.SampleRate, sizeof (cab_1.SampleRate), 1, archivoSalida);
	fread (&cab_1.ByteRate, sizeof (cab_1.ByteRate), 1, archivoSalida);
	fread (&cab_1.BlockAlign, sizeof (cab_1.BlockAlign), 1, archivoSalida);
	fread (&cab_1.BitsPerSample, sizeof (cab_1.BitsPerSample), 1, archivoSalida);
	fread (cab_1.SubChunk2ID, sizeof (cab_1.SubChunk2ID), 1, archivoSalida);
	fread (&cab_1.SubChunk2Size, sizeof (cab_1.SubChunk2Size), 1, archivoSalida);

	printf ("\t\t\tARCHIVO DE SALIDA\n\n");
	printf ("(1-4) Chunk ID: %s\n", cab_1.ChunkID);
	printf ("(5-8) ChunkSize:  %u\n", cab_1.ChunkSize);
	printf ("(9-12) Format: %s\n", cab_1.Format);
	printf ("(13-16) SubChunk 1 ID: %s\n", cab_1.SubChunk1ID);
	printf ("(17-20) SubChunk 1 Size: %u\n", cab_1.SubChunk1Size);
	if (cab_1.AudioFormat == 1)
			strcpy (cadena, "PCM");
		printf ("(21-22) Audio Format: %u, %s\n", cab_1.AudioFormat, cadena);
	if (cab_1.NumChannels == 1)
			strcpy (cadena, "Mono");
		else
			strcpy (cadena,"Stereo");
	printf ("(23-24) Number of Channels: %u, Tipo: %s\n", cab_1.NumChannels,cadena);
	printf ("(25-28) Sample Rate: %u\n", cab_1.SampleRate);
	printf ("(29-32) Byte Rate: %u BitRate: %u\n", cab_1.ByteRate, cab_1.ByteRate*8);
	printf ("(33-34) Block Align: %u\n", cab_1.BlockAlign);
	printf ("(35-36) Bits Per Sample: %u\n", cab_1.BitsPerSample);
	printf ("(37-40) SubChunk 2 ID: %s\n", cab_1.SubChunk2ID);
	printf ("(41-44) SubChunk 2 Size: %u\n", cab_1.SubChunk2Size);


	printf ("\n\n");
	fclose (archivo_1);
	fclose (archivo_2);
	fclose (archivoSalida);
	printf ("Archivos '%s' y '%s' multiplicados correctamente.\n", archivo1, archivo2);
	return 0;
}
