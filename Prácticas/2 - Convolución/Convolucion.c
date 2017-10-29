#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.c"
#define TAM_ARREGLO 20

////////////////////////////////////////////////////////////////////////////////////////
////								Convolucion.c 									////
////																				////
////																				////
//// Por medio del uso de la convolución continua, se realiza el análisis para 		////
//// pasarla al tiempo discreto y poder acondicionar una señal pasando por una 		////
//// respuesta al impulso muy particular, que es la respuesta de un filtro digital	////
//// en configuración Pasa - Bajas para cualquier señal que pase por el programa.	////
//// NOTA: Los archivos generados para prueba, fueron creados con GoldWave.			////
////																				////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	FILE * entrada, * salida;
	cabecera cab;
	int i, k;
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
	entrada = abre_archivo (archivo_entrada, archivo_salida,1);
	salida = abre_archivo (archivo_entrada, archivo_salida, 2);

	//Leemos e imprimimos la cabecera del archivo wav
	copiar_cabecera (entrada, salida, &cab);
	imprimir_cabecera (&cab);

	//Generamos la respuesta al impulso
	impulso = generaImpulso ();
	float max = 0;
	for (i = 0; i < TAM_ARREGLO; i ++)
		max += (impulso [i] * 32767);

	//Llenamos el arreglo de entrada con puros ceros
	memset (signal, 0, TAM_ARREGLO);
	
	//Escribimos el resto de los datos realizando la convolución
	for (i = 0; i < (cab.SubChunk2Size / 2); i ++)
	{
		fread (&muestra, sizeof (short), 1, entrada);
		for (k = (TAM_ARREGLO - 1); k >= 0; k --)
			signal [k] = signal [k - 1];
		signal [0] = (muestra / max);									//Insertamos los datos en el arreglo
		muestra = convolucion (signal, impulso);
		fwrite (&muestra, sizeof (short), 1, salida);					//Escribimos los datos nuevos en el archivo
	}
	printf ("\n\n");
	fclose (entrada);
	fclose (salida);
	printf ("Archivo '%s' filtrado correctamente guardado en '%s'.\n", archivo_entrada, archivo_salida);
	return 0;
}
