#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.h"

////////////////////////////////////////////////////////////////////////////////////////
////									Volumen.c 									////
////																				////
////																				////
//// Manipulación de un archivo wav (multimedia), para bajar el volumen del mismo	////
//// a la mitad por medio del análisis de la cabecera que lo compone y un ciclo para////
//// recorrer todos los datos que lo componen.										////
//// Compilación: gcc Cabecera.c -o Cabecera.o -c 									////
////			  gcc Volumen.c -o Volumen Cabecera.o								////
//// Ejecuación: Volumen.exe Entrada.wav Salida.wav									////
////																				////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	FILE * entrada, * salida;
	cabecera cab;
	int i, numero_muestras;
	short muestra;
	char * archivo_entrada = (char *) malloc (sizeof (char));
	char * archivo_salida = (char *) malloc (sizeof (char));
	system ("cls");
	if (argc < 3)
	{
		printf("Error, faltan argumentos.\n");
		printf ("Ejemplo: '%s Archivo.wav Salida.wav'\n\n", argv [0]);
		exit (0);
	}else
	{
		archivo_entrada = (char *) argv [1];
		archivo_salida = (char *) argv [2];
	}

	//Abrimos los archivos en modo binario
	entrada = fopen (archivo_entrada, "rb");
	if (entrada == NULL)
	{
		printf ("Error al abrir el archivo '%s'", archivo_entrada);
		exit (0);
	}
	salida = fopen (archivo_salida, "wb");
	if (salida == NULL)
	{
		printf ("Error al abrir el archivo '%s'", archivo_salida);
		exit (0);
	}

	//Copiar la cabecera del archivo de entrada al de salida
	fread (&cab, 44, 1, entrada);
	fwrite (&cab, 44, 1, salida);

	//Imprimir los valores de la cabecera
	imprimir_cabecera (&cab);

	numero_muestras = (cab.SubChunk2Size / cab.BlockAlign);
	
	for (i = 0; i < numero_muestras; i ++)
	{
		fread (&muestra, sizeof (short), 1, entrada);
		muestra *= 0.5;
		fwrite (&muestra, sizeof (short), 1, salida);
	}
	printf ("\n\n");
	fclose (entrada);
	fclose (salida);
	return 0;
}
