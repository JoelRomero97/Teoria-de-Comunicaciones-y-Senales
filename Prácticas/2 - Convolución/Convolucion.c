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
	FILE * archivoEntrada, * archivoSalida;
	cabecera cab;
	int i, lectura, escritura, j = 0, k;
	short muestra;
	float * impulso = (float *) malloc (sizeof (float) * 20);
	float * entrada = (float *) malloc (sizeof (float) * 20);
	char * nombreModificado = (char *) malloc (sizeof (char));
	char * nombreArch = (char *) malloc (sizeof (char));
	system ("cls");
	if (argc < 3)
	{
		printf("Error, faltan argumentos.\n");
		printf ("Ejemplo: '%s Archivo1.wav Salida.wav'\n\n", argv [0]);
		exit (0);
	}
	else
	{
		nombreArch = (char *) argv [1];
		nombreModificado = (char *) argv [2];
	}

	//Abrimos los archivos en modo binario
	archivoEntrada = abreArchivo (nombreArch, nombreModificado,1);
	archivoSalida = abreArchivo (nombreArch, nombreModificado, 2);

	//Leemos e imprimimos la cabecera del archivo wav
	leerCabecera (archivoEntrada, archivoSalida, &cab);
	imprimir_cabecera (&cab);

	//Generamos la respuesta al impulso
	impulso = generaImpulso ();
	float max = 0;
	for (i = 0; i < TAM_ARREGLO; i ++)
		max += (impulso [i] * 32767);

	//Llenamos el arreglo de entrada con puros ceros
	memset (entrada, 0, TAM_ARREGLO);
	
	//Escribimos el resto de los datos realizando la convolución
	for (i = 0; i < cab.SubChunk2Size; i ++, j++)
	{
		lectura = fread(&muestra, sizeof (short), 1, archivoEntrada);
		for (k = (TAM_ARREGLO - 1); k >= 0; k --)
			entrada [k] = entrada [k - 1];
		entrada [0] = (muestra / max);																//Insertamos los datos en el arreglo
		muestra = convolucion (entrada, impulso);
		escritura = fwrite(&muestra, sizeof (short), lectura, archivoSalida);				//Escribimos los datos nuevos en el archivo
	}
	printf ("\n\n");
	fclose (archivoEntrada);
	fclose (archivoSalida);
	printf ("Archivo '%s' filtrado correctamente.\n", nombreArch);
	return 0;
}
