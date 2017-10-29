#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.c"

int main (int argc, char const *argv[])
{
	FILE * archivo_1, *archivo_2, * archivoSalida;
	cabecera cab_1, cab_2;
	int i;
	short real1, imaginario1, real2, imaginario2;
	float max = 32767, real1_1, imaginario1_1, real2_1, imaginario2_1;
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
	archivo_1 = abre_archivo (archivo1, archivo2, salida, 1);
	archivo_2 = abre_archivo (archivo1, archivo2, salida, 2);
	archivoSalida = abre_archivo (archivo1, archivo2, salida, 3);

	//Leemos e imprimimos la cabecera del archivo wav
	leer_cabecera (archivo_1, archivo_2, &cab_1, &cab_2);
	imprimir_cabecera (&cab_1, 1);
	imprimir_cabecera (&cab_2, 2);

	if ((cab_1.ChunkSize) >= (cab_2.ChunkSize))
		copiar_cabecera (archivo_1, archivoSalida, &cab_1);
	else
		copiar_cabecera (archivo_2, archivoSalida, &cab_2);

	fseek (archivoSalida, 44, SEEK_SET);
	fseek (archivo_1, 44, SEEK_SET);
	fseek (archivo_2, 44, SEEK_SET);

	if ((cab_1.NumChannels == 1) && (cab_2.NumChannels == 1))					//Si son 2 archivos mono
	{
		if ((cab_1.SubChunk2Size) >= (cab_2.SubChunk2Size))
		{
			for (i = 0; i < (cab_1.SubChunk2Size / 2); i ++)
			{
				fread (&real1, sizeof (short), 1, archivo_1);
				real1_1 = (real1 / max);
				if (i >= (cab_2.SubChunk2Size / 2))
					real2 = 0;
				else
					fread (&real2, sizeof (short), 1, archivo_2);
				real2_1 = (real2 / max);
				real1 = (real1_1 * real2_1 * max);
				fwrite (&real1, sizeof (short), 1, archivoSalida);
			}
		}else
		{
			for (i = 0; i < (cab_2.SubChunk2Size / 2); i ++)
			{
				fread (&real1, sizeof (short), 1, archivo_2);
				real1_1 = (real1 / max);
				if (i >= (cab_1.SubChunk2Size / 2))
					real2 = 0;
				else
					fread (&real2, sizeof (short), 1, archivo_1);
				real2_1 = (real2 / max);
				real1 = (real1_1 * real2_1 * max);
				fwrite (&real1, sizeof (short), 1, archivoSalida);
			}
		}
	}else
	{
		if ((cab_1.SubChunk2Size) >= (cab_2.SubChunk2Size))
		{
			for (i = 0; i < (cab_1.SubChunk2Size / 4); i ++)
			{
				//Guardamos la parte real del número complejo
				fread (&real1, sizeof (short), 1, archivo_1);
				real1_1 = (real1 / max);
				if (i >= (cab_2.SubChunk2Size / 4))
				{
					real2 = 0;
					imaginario2 = 0;
				}else
				{
					fread (&real2, sizeof (short), 1, archivo_2);
					fread (&imaginario2, sizeof (short), 1, archivo_2);
				}
				real2_1 = (real2 / max);

				//Guardamos la parte imaginaria del número complejo
				fread (&imaginario1, sizeof (short), 1, archivo_1);
				imaginario1_1 = (imaginario1 / max);
				imaginario2_1 = (imaginario2 / max);

				real1 = (((real1_1 * real2_1) - (imaginario1_1 * imaginario2_1)) * max);
				imaginario1 = (((real1_1 * imaginario2_1) + (imaginario1_1 * real2_1)) * max);
				fwrite (&real1, sizeof (short), 1, archivoSalida);
				fwrite (&imaginario1, sizeof (short), 1, archivoSalida);
			}
		}else
		{
			for (i = 0; i < (cab_2.SubChunk2Size / 4); i ++)
			{
				//Guardamos la parte real del número complejo
				fread (&real1, sizeof (short), 1, archivo_2);
				real1_1 = (real1 / max);
				if (i >= (cab_1.SubChunk2Size / 4))
				{
					real2 = 0;
					imaginario2 = 0;
				}else
				{
					fread (&real2, sizeof (short), 1, archivo_1);
					fread (&imaginario2, sizeof (short), 1, archivo_1);
				}
				real2_1 = (real2 / max);

				//Guardamos la parte imaginaria del número complejo
				fread (&imaginario1, sizeof (short), 1, archivo_2);
				imaginario1_1 = (imaginario1 / max);
				imaginario2_1 = (imaginario2 / max);

				real1 = (((real1_1 * real2_1) - (imaginario1_1 * imaginario2_1)) * max);
				imaginario1 = (((real1_1 * imaginario2_1) + (imaginario1_1 * real2_1)) * max);
				fwrite (&real1, sizeof (short), 1, archivoSalida);
				fwrite (&imaginario1, sizeof (short), 1, archivoSalida);
			}
		}
	}
	printf ("\n\n");
	fclose (archivo_1);
	fclose (archivo_2);
	fclose (archivoSalida);
	printf ("Archivos '%s' y '%s' multiplicados correctamente en '%s'.\n\n", archivo1, archivo2, salida);
	return 0;
}
