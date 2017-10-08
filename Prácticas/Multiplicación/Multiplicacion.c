#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.c"
#define TAM_ARREGLO 20

int main(int argc, char const *argv[])
{
	FILE * archivo_1, *archivo_2, * archivoSalida;
	cabecera cab_1, cab_2;
	int i;
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
	}
	else
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

	if ((cab_1.SubChunk2Size) > (cab_2.SubChunk2Size))
	{
		for (i = 0; i < cab_1.SubChunk2Size; i ++)
		{
			fread (&muestra1, sizeof (short), 1, archivo_1);
			fread (&muestra2, sizeof (short), 1, archivo_2);
			float muestra1_1 = (muestra1 / 32767);
			float muestra2_1 = (muestra2 / 32767);
			float resultado = (muestra1_1 * muestra2_1);
			muestra1 = (resultado * 32767);
			fwrite (&muestra1, sizeof (short), 1, archivoSalida);
		}
		for (i = 0; i < (cab_1.SubChunk2Size - cab_2.SubChunk2Size); i ++)
		{
			fread (&muestra1, sizeof (short), 1, archivo_1);
			muestra1 *= 0;
			fwrite (&muestra1, sizeof (short), 1, archivoSalida);
		}
	}else
	{
		for (i = 0; i < cab_1.SubChunk2Size; i ++)
		{
			fread (&muestra1, sizeof (short), 1, archivo_1);
			fread (&muestra2, sizeof (short), 1, archivo_2);
			float muestra1_1 = (muestra1 / 32767);
			float muestra2_1 = (muestra2 / 32767);
			float resultado = (muestra1_1 * muestra2_1);
			muestra1 = (resultado * 32767);
			fwrite (&muestra1, sizeof (short), 1, archivoSalida);
		}
		for (i = 0; i < (cab_2.SubChunk2Size - cab_1.SubChunk2Size); i ++)
		{
			fread (&muestra1, sizeof (short), 1, archivo_2);
			muestra1 *= 0;
			fwrite (&muestra1, sizeof (short), 1, archivoSalida);
		}
	}
	printf ("\n\n");
	fclose (archivo_1);
	fclose (archivo_2);
	fclose (archivoSalida);
	printf ("Archivos '%s' y '%s' multiplicados correctamente.\n", archivo1, archivo2);
	return 0;
}
