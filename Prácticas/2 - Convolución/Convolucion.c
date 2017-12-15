#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.h"
#define TAM_ARREGLO 20

////////////////////////////////////////////////////////////////////////////////////////
////								Convolucion.c 									////
////																				////
////																				////
//// Por medio del uso de la convolución continua, se realiza el análisis para 		////
//// pasarla al tiempo discreto y poder acondicionar una señal pasando por una 		////
//// respuesta al impulso muy particular, que es la respuesta de un filtro digital	////
//// en configuración Pasa - Bajas para cualquier señal que pase por el programa.	////
//// Compilación: gcc Cabecera.c -o Cabecera.o -c 									////
////			  gcc Convolucion.c -o Convolucion Cabecera.o						////
//// Ejecuación: Convolucion.exe Entrada.wav Salida.wav								////
////																				////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	FILE * entrada, * salida;
	cabecera cab;
	int i, k, numero_muestras;
	short muestra;
	float * impulso = (float *) malloc (sizeof (float) * 20);
	float * signal = (float *) malloc (sizeof (float) * 20);
	char * archivo_salida = (char *) malloc (sizeof (char));
	char * archivo_entrada = (char *) malloc (sizeof (char));
	system ("cls");
	if (argc < 3)
	{
		printf("Error, faltan argumentos.\n");
		printf ("Ejemplo: '%s Archivo1.wav Salida.wav'\n\n", argv [0]);
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

	//Generamos la respuesta al impulso
	impulso = generar_impulso ();
	float max = 0;
	for (i = 0; i < TAM_ARREGLO; i ++)
		max += (impulso [i] * 32767);

	//Llenamos el arreglo de entrada con puros ceros
	memset (signal, 0, TAM_ARREGLO);

	numero_muestras = (cab.SubChunk2Size / cab.BlockAlign);
	
	//Escribimos el resto de los datos realizando la convolución
	for (i = 0; i < numero_muestras; i ++)
	{
		fread (&muestra, sizeof (short), 1, entrada);
		for (k = (TAM_ARREGLO - 1); k >= 0; k --)
			signal [k] = signal [k - 1];
		signal [0] = (muestra / max);
		muestra = convolucion (signal, impulso);
		fwrite (&muestra, sizeof (short), 1, salida);
	}
	printf ("\n\n");
	fclose (entrada);
	fclose (salida);
	return 0;
}
