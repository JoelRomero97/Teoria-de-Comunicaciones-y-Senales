#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "MedirTiempo/tiempo.c"
#include "Cabecera.h"
#define PI 3.14159265

int i;					//Variable global para manejar ciclos
double utime0, stime0, wtime0, utime1, stime1, wtime1;

FILE * abre_archivo (char * entrada, char * salida, int tipo)
{
	FILE * pt1, * pt2;
	pt1 = fopen (entrada, "rb");
	if (pt1 == NULL)
	{
		printf("Error al abrir archivo '%s'.\n", entrada);
		exit(0);
	}
	
	//Abrimos el archivo a escribir en modo binario	
	pt2 = fopen (salida, "wb");
	if (pt2 == NULL)
	{
		printf("Error al crear el archivo '%s'.\n", salida);
		exit(1);
	}
	if (tipo == 1)
		return pt1;
	else
		return pt2;
}

void copiar_cabecera (FILE * entrada, FILE * salida, cabecera * cab)
{
	rewind (entrada);
	rewind (salida);

	short archivo_stereo = 2;
	int n1;
	
	//ChunkID 
	fread (cab -> ChunkID, sizeof (char), 4, entrada);
	fwrite (cab -> ChunkID, sizeof (char), 4, salida);

	//ChunkSize 
	fread (&cab -> ChunkSize, sizeof (int), 1, entrada);
	n1 = (cab -> ChunkSize * 2);
	fwrite (&n1, sizeof (int), 1, salida);

	//Formato "Fmt"
	fread (cab -> Format, sizeof (char), 4, entrada);
	fwrite (cab -> Format, sizeof (char), 4, salida);

	//SubChunk1ID Formato de datos "fmt"
	fread (cab -> SubChunk1ID, sizeof (char), 4, entrada);
	fwrite (cab -> SubChunk1ID, sizeof (char), 4, salida);

	//SubChunk1Size
	fread (&cab -> SubChunk1Size, sizeof (int), 1, entrada);
	fwrite (&cab -> SubChunk1Size, sizeof (int), 1, salida);
	
	// Formato de audio
	fread (&cab -> AudioFormat, sizeof (short), 1, entrada);
	fwrite (&cab -> AudioFormat, sizeof (short), 1, salida);
	
	//Canales (POR LA NATURALEZA DEL PROBLEMA, SIEMPRE DEBEN SER 2 CANALES)
	fread (&cab -> NumChannels, sizeof (short), 1, entrada);
	//fwrite (&cab -> NumChannels, sizeof (short), 1, salida);
	fwrite (&archivo_stereo, sizeof (short), 1, salida);

	//SampleRate
	fread (&cab -> SampleRate, sizeof (int), 1, entrada);
	fwrite (&cab -> SampleRate, sizeof (int), 1, salida);
	
	//ByteRate
	fread (&cab -> ByteRate, sizeof (int), 1, entrada);
	n1 = (cab -> ByteRate * 2);
	fwrite (&n1, sizeof (int), 1, salida);

	//Block Align
	fread (&cab -> BlockAlign, sizeof (short), 1, entrada);
	n1 = (cab -> BlockAlign * 2);
	fwrite (&n1, sizeof (short), 1, salida);
	
	//Bits per Sample
	fread (&cab -> BitsPerSample, sizeof (short), 1, entrada);
	fwrite (&cab -> BitsPerSample, sizeof (short), 1, salida);

	//SubChunk2ID
	fread (cab -> SubChunk2ID, sizeof (char), 4, entrada);	
	fwrite (cab -> SubChunk2ID, sizeof (char), 4, salida);

	//SubChunk2Size
	fread (&cab -> SubChunk2Size, sizeof (int), 1, entrada);
	n1 = (cab -> SubChunk2Size * 2);
	fwrite (&n1, sizeof (int), 1, salida);
}

void opcion_uno (FILE * salida, float * signal, cabecera * cab)
{
	int k, n;
	float max = 32767, muestras = ((cab -> SubChunk2Size) / 2);
	short * magnitud = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	short * new_signal = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	float parte_real, parte_imaginaria, angulo, modulo;

	//Se comienza a tomar tiempo
	uswtime (&utime0, &stime0, &wtime0);
	for (k = 0; k < muestras; k ++)
	{
		//Se resetean los valores de la parte real e imaginaria en 0
		parte_real = 0;
		parte_imaginaria = 0;
		for (n = 0; n < muestras; n ++)
		{
			//Se calcula el angulo definido
			angulo = ((2 * PI * k * n) / muestras);

			//Se calculan las partes real e imaginaria de la TDF
			parte_real += (signal [n] * (cos (angulo)));
			parte_imaginaria += (signal [n] * sin (angulo));
		}
		//Se vuelven a dividir los coeficientes de la TDF entre el numero de muestras para tener valores entre 0 y 1
		parte_real = (parte_real / muestras);
		parte_imaginaria = (parte_imaginaria / muestras);

		if ((parte_real == 0) && (parte_imaginaria == 0))
			modulo = 0;
		else
		{
			//Calculamos el cuadrado de la parte real y de la parte imaginaria
			parte_real = pow (parte_real, 2);
			parte_imaginaria = pow (parte_imaginaria, 2);

			//Calculamos la magnitud de cada coeficiente de la TDF
			modulo = sqrt ((parte_real + parte_imaginaria));
		}

		//Volvemos a dimensionar los valores de la magnitud para escribirlos
		magnitud [k] = (modulo * max);
	}
	uswtime (&utime1, &stime1, &wtime1);
	calculaTiempo (utime0, stime0, wtime0, utime1, stime1, wtime1, muestras, 1);

	//Redimensionamos el tamaño de la señal original para hacer la escritura
	for (k = 0; k < muestras; k ++)
		new_signal [k] = (signal [k] * max);

	//Avanzamos el apuntador al archivo para evitar errores
	fseek (salida, 44, SEEK_SET);
	
	//PARA ESCRIBIR LOS DATOS
	for (i = 0; i < muestras; i ++)
	{
		//Escribimos en el canal izquierdo la señal original
		fwrite (&new_signal [i], sizeof (short), 1, salida);

		//Escribimos en el canal derecho la magnitud de la TDF
		fwrite (&magnitud [i], sizeof (short), 1, salida);
	}	
}

void opcion_dos (FILE * salida, float * signal, cabecera * cab)
{
	int k, n;
	float max = 32767, muestras = ((cab -> SubChunk2Size) / 2);
	short * real = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	short * imaginario = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	float parte_real, parte_imaginaria, angulo;

	uswtime (&utime0, &stime0, &wtime0);
	for (k = 0; k < muestras; k ++)
	{
		//Se resetean los valores de la parte real e imaginaria en 0
		parte_real = 0;
		parte_imaginaria = 0;
		for (n = 0; n < muestras; n ++)
		{
			//Se calcula el angulo definido
			angulo = ((2 * PI * k * n) / muestras);

			//Se calculan las partes real e imaginaria de la TDF
			parte_real += (signal [n] * (cos (angulo)));
			parte_imaginaria += (signal [n] * sin (angulo));
		}
		//Se vuelven a dividir los coeficientes de la TDF entre el numero de muestras para tener valores entre 0 y 1
		parte_real = (parte_real / muestras);
		parte_imaginaria = (parte_imaginaria / muestras);

		//Volvemos a dimensionar los valores de la señal a escribir
		real [k] = (parte_real * max);
		imaginario [k] = (parte_imaginaria * -1 * max);
	}
	uswtime (&utime1, &stime1, &wtime1);
	calculaTiempo (utime0, stime0, wtime0, utime1, stime1, wtime1, muestras, 2);

	//Avanzamos el apuntador al archivo para evitar errores
	fseek (salida, 44, SEEK_SET);
	
	//PARA ESCRIBIR LOS DATOS
	for (i = 0; i < muestras; i ++)
	{
		//Escribimos en el canal izquierdo la parte real de la TDF
		fwrite (&real [i], sizeof (short), 1, salida);

		//Escribimos en el canal derecho la parte imaginaria de la TDF
		fwrite (&imaginario [i], sizeof (short), 1, salida);
	}
}

void opcion_tres (FILE * salida, float * signal, cabecera * cab)
{
	int k, n;
	float max = 32767, muestras = ((cab -> SubChunk2Size) / 2);
	short * magnitud = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	short * fase = (short *) malloc (sizeof (short) * (cab -> SubChunk2Size / 2));
	float parte_real, parte_imaginaria, angulo, fase_float, modulo;

	uswtime (&utime0, &stime0, &wtime0);
	for (k = 0; k < muestras; k ++)
	{
		//Se resetean los valores de la parte real e imaginaria en 0
		parte_real = 0;
		parte_imaginaria = 0;
		for (n = 0; n < muestras; n ++)
		{
			//Se calcula el angulo definido
			angulo = ((2 * PI * k * n) / muestras);

			//Se calculan las partes real e imaginaria de la TDF
			parte_real += (signal [n] * (cos (angulo)));
			parte_imaginaria += (signal [n] * sin (angulo));
		}
		//Se vuelven a dividir los coeficientes de la TDF entre el numero de muestras para tener valores entre 0 y 1
		parte_real = (parte_real / muestras);
		parte_imaginaria = (parte_imaginaria / muestras * -1);

		//Calculamos la fase de la TDF (como cualquier número complejo Z)
		//Si tanto la parte real como la parte imaginaria son 0, la magnitud es 0 al igual que la fase
		if ((parte_real == 0) && (parte_imaginaria == 0))
		{
			modulo = 0;
		}else
		{
			//Calculamos el cuadrado de la parte real y de la parte imaginaria
			parte_real = pow (parte_real, 2);
			parte_imaginaria = pow (parte_imaginaria, 2);

			//Calculamos la magnitud de cada coeficiente de la TDF
			modulo = sqrt ((parte_real + parte_imaginaria));
		}
		//Si la magnitud es 0
		if (modulo == 0)
		{
			fase_float = 0;
		//Si la magnitud es algo distinto de 0
		}else
		{
			//Si el angulo solo vive en el eje imaginario negativo
			if ((parte_real == 0) && (parte_imaginaria < 0))
			{
				fase_float = (- PI / 2);
			//Si el angulo solo vive en el eje imaginario positivo
			}else if ((parte_real == 0) && (parte_imaginaria > 0))
			{
				fase_float = (PI / 2);
			//Si el angulo solo vive en el eje real negativo
			}else if ((parte_real < 0) && (parte_imaginaria >= 0))
			{
				//Si vive en el eje real negativo o positivo
				fase_float = (atan (parte_imaginaria / parte_real) + PI);
			}else if ((parte_real < 0) && (parte_imaginaria < 0))
			{
				//Si el eje real e imaginario son negativos
				fase_float = (atan (parte_imaginaria / parte_real) - PI);
			}
		}

		//Dividimos entre el valor máximo que puede tomar un arctan
		fase_float = (fase_float / PI);

		//Volvemos a dimensionar los valores de la magnitud para escribirlos
		magnitud [k] = (modulo * max);
		fase [k] = (fase_float * max);
	}
	uswtime (&utime1, &stime1, &wtime1);
	calculaTiempo (utime0, stime0, wtime0, utime1, stime1, wtime1, muestras, 3);

	//Avanzamos el apuntador al archivo para evitar errores
	fseek (salida, 44, SEEK_SET);
	
	//PARA ESCRIBIR LOS DATOS
	for (i = 0; i < muestras; i ++)
	{
		//Escribimos en el canal derecho la magnitud de la TDF
		fwrite (&magnitud [i], sizeof (short), 1, salida);
		
		//Escribimos en el canal izquierdo la señal original
		fwrite (&fase [i], sizeof (short), 1, salida);
	}	
}

void calculaTiempo (double utime0, double stime0, double wtime0, double utime1, double stime1, double wtime1, int n, int opcion)
{
	char * option = (char *) malloc (sizeof (char));
	switch (opcion)
	{
		case 1:
			strcpy (option, "Opcion 1");
			break;
		case 2:
			strcpy (option, "Opcion 2");
			break;
		case 3:
			strcpy (option, "Opcion 3");
			break;
	}
	printf("Tiempo con la %s para un archivo de %d muestras:\n\n", option, n);
	printf("Tiempo total:  %.10f s\n",  wtime1 - wtime0);
	printf("Tiempo de procesamiento en CPU: %.10f s\n",  utime1 - utime0);
	printf ("________________________________________________________________________________________________________________________");
}
