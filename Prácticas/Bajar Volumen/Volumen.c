#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Cabecera.c"

int main(int argc, char const *argv[])
{
	FILE * archivoEntrada, * archivoSalida;
	cabecera cab;
	int i, lectura, escritura;
	short muestra;
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
	imprimir_cabecera (&cab);
	
	for (i = 0; i < (cab.SubChunk2Size); i ++)
	{
		lectura = fread(&muestra, sizeof (short), 1, archivoEntrada);
		muestra *= 0.5;																		//Dividimos a la mitad cada uno de los datos
		escritura = fwrite(&muestra, sizeof (short), lectura, archivoSalida);				//Escribimos los datos nuevos en el archivo
	}
	printf ("\n\n");
	fclose (archivoEntrada);
	fclose (archivoSalida);
	printf ("Archivo '%s' modificado correctamente.\n", nombreArch);
	return 0;
}
