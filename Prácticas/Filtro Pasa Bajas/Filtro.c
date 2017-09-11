#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cabecera.c"

int main(int argc, char const *argv[])
{
	FILE * archivoEntrada, * archivoSalida;
	cabecera cab;
	int i, lectura, escritura, j = 0;
	short muestra;
	float * impulso = (float *) malloc (sizeof (float) * 20);
	float * entrada = (float *) malloc (sizeof (float) * 20);
	char * nombreModificado = (char *) malloc (sizeof (char));
	char * nombreArch = (char *) malloc (sizeof (char));
	system ("cls");
	if (argc < 3)
		printf("Error, faltan argumentos.\n");
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

	//Generamos la respuesta al impulso
	impulso = generaImpulso ();
	
	//Escribimos el resto de los datos realizando la convolución
	while (j < cab.SubChunk2Size)
	{
		for (i = 0; i < 20; i ++, j++)
		{
			lectura = fread(&muestra, sizeof (short), 1, archivoEntrada);
			entrada [i] = muestra;																//Insertamos los datos en el arreglo
			muestra = convolucion (entrada, impulso, i + 1);
			printf("\nRESPUESTA A ESCRIBIR: %d\n\n", muestra);
			escritura = fwrite(&muestra, sizeof (short), lectura, archivoSalida);				//Escribimos los datos nuevos en el archivo
		}
	}
	printf ("\n\n");
	fclose (archivoEntrada);
	fclose (archivoSalida);
	printf ("Archivo '%s' modificado correctamente.\n", nombreArch);
	return 0;
}
