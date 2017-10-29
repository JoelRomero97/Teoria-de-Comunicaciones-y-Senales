#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.c"

////////////////////////////////////////////////////////////////////////////////////////
////									Volumen.c 									////
////																				////
////																				////
//// Manipulación de un archivo WAV (multimedia), para bajar el volumen del mismo	////
//// a la mitad por medio del análisis de la cabecera que lo compone y un ciclo para////
//// recorrer todos los datos que lo componen.										////
//// NOTA: Los archivos generados para prueba, fueron creados con GoldWave.			////
////																				////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	FILE * entrada, * salida;
	cabecera cab;
	int i;
	short muestra;
	char * archivo_salida = (char *) malloc (sizeof (char));
	char * archivo_entrada = (char *) malloc (sizeof (char));
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
	entrada = abre_archivo (archivo_entrada, archivo_salida, 1);
	salida = abre_archivo (archivo_entrada, archivo_salida, 2);

	//Leemos e imprimimos la cabecera del archivo wav
	copiar_cabecera (entrada, salida, &cab);
	imprimir_cabecera (&cab);
	
	for (i = 0; i < (cab.SubChunk2Size / 2); i ++)
	{
		fread (&muestra, sizeof (short), 1, entrada);
		muestra *= 0.5;														//Dividimos a la mitad cada uno de los datos
		fwrite (&muestra, sizeof (short), 1, salida);				//Escribimos los datos nuevos en el archivo
	}
	printf ("\n\n");
	fclose (entrada);
	fclose (salida);
	printf ("Archivo '%s' filtrado correctamente.\n", archivo_entrada);
	return 0;
}
