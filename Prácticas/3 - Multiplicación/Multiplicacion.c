#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.h"

////////////////////////////////////////////////////////////////////////////////////////
////								Multiplicacion.c 								////
////																				////
////																				////
//// Implementacion de la multiplicacion de 2 señales en archivos wav, ya sea mono	////
//// por mono, o estéreo por estéreo.												////
//// Compilación: gcc Cabecera.c -o Cabecera.o -c 									////
////			  gcc Multiplicacion.c -o Multiplicacion Cabecera.o					////
//// Ejecuación: Multiplicacion.exe Archivo 1.wav Archivo 2.wav Salida.wav			////
////																				////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main (int argc, char const *argv[])
{
	FILE * archivo_1, *archivo_2, * salida, * grande, * chico;
	cabecera cab_1, cab_2;
	int i, numero_muestras_1, numero_muestras_2, numero_muestras, aux;
	short real1, imaginario1, real2, imaginario2;
	float max = 32767, real1_1, imaginario1_1, real2_1, imaginario2_1;
	char * archivo1 = (char *) malloc (sizeof (char));
	char * archivo2 = (char *) malloc (sizeof (char));
	char * archivo_salida = (char *) malloc (sizeof (char));
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
		archivo_salida = (char *) argv [3];
	}

	//Abrimos los archivos en modo binario
	archivo_1 = fopen (archivo1, "rb");
	if (archivo_1 == NULL)
	{
		printf ("Error al abrir el archivo: '%s'", archivo1);
		exit (0);
	}
	archivo_2 = fopen (archivo2, "rb");
	if (archivo_2 == NULL)
	{
		printf ("Error al abrir el archivo: '%s'", archivo2);
		exit (0);
	}
	salida = fopen (archivo_salida, "wb");
	if (salida == NULL)
	{
		printf ("Error al crear el archivo: '%s'", archivo_salida);
		exit (0);
	}

	//Leer las cabeceras de ambos archivos de entrada
	fread (&cab_1, 44, 1, archivo_1);
	fread (&cab_2, 44, 1, archivo_2);

	//Imprimir los valores de la cabecera
	imprimir_cabecera (&cab_1, 1);
	imprimir_cabecera (&cab_2, 2);

	numero_muestras_1 = (cab_1.SubChunk2Size / cab_1.BlockAlign);
	numero_muestras_2 = (cab_2.SubChunk2Size / cab_2.BlockAlign);

	//Copiar cabecera del archivo más grande en el de salida
	if (numero_muestras_1 >= numero_muestras_2)
		fwrite (&cab_1, 44, 1, salida);
	else
		fwrite (&cab_2, 44, 1, salida);

	if ((cab_1.NumChannels == 1) && (cab_2.NumChannels == 1))
	{
		if (numero_muestras_1 >= numero_muestras_2)
		{
			numero_muestras = numero_muestras_1;
			aux = numero_muestras_2;
			grande = archivo_1;
			chico = archivo_2;
		}else
		{
			numero_muestras = numero_muestras_2;
			aux = numero_muestras_1;
			grande = archivo_2;
			chico = archivo_1;
		}
		for (i = 0; i < numero_muestras; i ++)
		{
			fread (&real1, sizeof (short), 1, grande);
			real1_1 = (real1 / max);
			if (i >= aux)
				real2 = 0;
			else
				fread (&real2, sizeof (short), 1, chico);
			real2_1 = (real2 / max);
			real1 = (real1_1 * real2_1 * max / 2);
			fwrite (&real1, sizeof (short), 1, salida);
		}
	}else
	{
		if (numero_muestras_1 >= numero_muestras_2)
		{
			numero_muestras = numero_muestras_1;
			aux = numero_muestras_2;
			grande = archivo_1;
			chico = archivo_2;
		}else
		{
			numero_muestras = numero_muestras_2;
			aux = numero_muestras_1;
			grande = archivo_2;
			chico = archivo_1;
		}
		for (i = 0; i < numero_muestras; i ++)
		{
			//Parte real del número complejo
			fread (&real1, sizeof (short), 1, grande);
			real1_1 = (real1 / max);
			if (i >= aux)
			{
				real2 = 0;
				imaginario2 = 0;
			}else
			{
				fread (&real2, sizeof (short), 1, chico);
				fread (&imaginario2, sizeof (short), 1, chico);
			}
			real2_1 = (real2 / max);

			//Parte imaginaria del número complejo
			fread (&imaginario1, sizeof (short), 1, grande);
			imaginario1_1 = (imaginario1 / max);
			imaginario2_1 = (imaginario2 / max);

			real1 = (((real1_1 * real2_1) - (imaginario1_1 * imaginario2_1)) * max / 2);
			imaginario1 = (((real1_1 * imaginario2_1) + (imaginario1_1 * real2_1)) * max / 2);
			fwrite (&real1, sizeof (short), 1, salida);
			fwrite (&imaginario1, sizeof (short), 1, salida);
		}
	}
	printf ("\n\n");
	fclose (archivo_1);
	fclose (archivo_2);
	fclose (salida);
	return 0;
}
