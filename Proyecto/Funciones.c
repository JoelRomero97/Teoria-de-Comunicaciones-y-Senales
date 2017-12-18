#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <alsa/asoundlib.h>
#include <string.h>
#include "Funciones.h"

/*
establecer_parametros (manejador, tam, segundos)
Recibe: Apuntador de tipo snd_pcm_t, tamaño de arreglo para muestras, número de segundos que será leído el sonido
Retorna: Manejador con todos los parametros correctos para recibir sonido
Efecto: Establecer los parámetros necesarios para recibir sonido, como: tipo de muestras, frecuencia de muestreo, numero de canales, etc.
Requerimientos: Contar con la instalación de asoundlib en linux
*/
snd_pcm_t * establecer_parametros (snd_pcm_t * manejador, int * tam, unsigned int * segundos)
{
	int flag, dir, frecuencia = sample_rate;
	unsigned int canales = 2, val;
	char * dispositivo = "default";
	snd_pcm_uframes_t muestras = SAMPLES;
	snd_pcm_hw_params_t * hw_params;
	snd_pcm_format_t formato = SND_PCM_FORMAT_S16_LE;			//Little Endian
	snd_pcm_format_t acceso = SND_PCM_ACCESS_RW_INTERLEAVED;

	//Abrir la interfaz de audio para recibir sonido
	flag = snd_pcm_open (&manejador, dispositivo, SND_PCM_STREAM_CAPTURE, 0);
	if (flag < 0)
	{
		printf ("No fue posible abrir el dispositivo %s: %s\n", dispositivo, snd_strerror (flag));
		exit (1);
	}else
		printf ("\n\nInterfaz de audio abierta correctamente.\n");

	printf ("\n\nEstablecimiento de parametros de hardware y software:\n\n");

	//Asignar parámetros de hardware
	flag = snd_pcm_hw_params_malloc (&hw_params);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible asignar la estructura de parametros de hardware: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Parametros de hardware asignados correctamente.\n");

	//Inicializar la estructura de parámetros de hardware
	flag = snd_pcm_hw_params_any (manejador, hw_params);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible inicializar la estructura de parametros de hardware: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Estructura de parametros de hardware inicializada correctamente.\n");

	//Establecer tipo de acceso
	flag = snd_pcm_hw_params_set_access (manejador, hw_params, acceso);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible establecer tipo de acceso: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Tipo de acceso establecido correctamente.\n");

	//Establecer el formato de las muestras
	flag = snd_pcm_hw_params_set_format (manejador, hw_params, formato);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible establecer formato de muestra: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Formato de muestra establecido correctamente.\n");

	//Establecer la frecuencia de muestreo
	flag = snd_pcm_hw_params_set_rate_near (manejador, hw_params, &frecuencia, &dir);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible establecer la frecuencia de muestreo: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Frecuencia de muestreo establecida correctamente.\n");

	//Establecer numero de canales (1 - Mono)
	flag = snd_pcm_hw_params_set_channels (manejador, hw_params, canales);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible establecer el numero de canales: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Numero de canales establecido correctamente.\n");

	//Establecer el numero de frames
	flag = snd_pcm_hw_params_set_period_size_near (manejador, hw_params, &muestras, &dir);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible establecer el tamaño del periodo: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Tamaño del periodo establecido correctamente.\n");

	//Establecer los parametros de hardware y software en el manejador
	flag = snd_pcm_hw_params (manejador, hw_params);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible establecer los parametros de hardware y software: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Parametros de hardware y software establecidos correctamente.\n");

	//Usar un búfer suficientemente grande para contener un periodo
	flag = snd_pcm_hw_params_get_period_size (hw_params, &muestras, &dir);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible establecer el tamaño del buffer: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Tamaño del buffer establecido correctamente.\n");
	* tam = (muestras * 4);

	//Establecer un tiempo de 5 segundos para recibir sonido
	flag = snd_pcm_hw_params_get_period_time (hw_params, &val, &dir);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible establecer la duracion: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Duracion establecida correctamente.\n\n");
	*segundos = ((TIEMPO * 1000000) / val);

	//Ya que se establecieron todos los parametros, se libera la estructura
	snd_pcm_hw_params_free (hw_params);
	return manejador;
}

/*
tecla_presionada (datos)
Recibe: Arreglo que contiene los datos a procesar
Retorna: Char según la tecla que presione el usuario
Efecto: Procesa la TDF analizando las frecuencias para saber que tecla presionó el usuario y lo devuelve como char
Requerimientos: El arreglo de los datos debe ser no vacío
*/
char tecla_presionada (short * datos)
{
	int i, j, k, fila, columna, filas [4], columnas [4];
	int frecuencias [8] = {697, 770, 852, 941, 1209, 1336, 1477, 1633};
	char teclado [4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
	float * muestras = (float *) malloc (sizeof (float) * 8);
	float aux;
	for (k = 0; k < 8; k ++)
	{
		aux = ((SAMPLES * frecuencias [k]) / sample_rate);
		if (k < 4)
			filas [k] = round (aux);
		else
			columnas [k - 4] = round (aux);
	}
	for (k = 0, j = 0; k < SAMPLES; k ++)
	{
		for (i = 0; i < 4; i ++)
			if (k == filas [i] || k == columnas [i])
				muestras [j ++] = TDF (datos, k);
	}
	muestras [8] = '\0';
	fila = obtener_fila (muestras);
	columna = obtener_columna (muestras);
	if ((fila >= 0 && fila <= 3) && (columna >= 0 && columna <= 3))
		return teclado [fila][columna];
}

/*
TDF (datos, k)
Recibe: Arreglo que contiene los datos a procesar y entero para calcular la TDF justo en esa k
Retorna: TDF en la posición k del arreglo de los datos
Efecto: Procesa la TDF en un cierto valor de k
Requerimientos: El arreglo de los datos debe ser no vacío
*/
float TDF (short * datos, int k)
{
	int n, j;
	double parte_real = 0, parte_imaginaria = 0, magnitud = 0;
	for (n = 0, j = 0; n < SAMPLES; n ++, j += 2)
	{
		parte_real += (datos [j] * cos ((2 * PI * k * n) / SAMPLES));
		parte_imaginaria -= (datos [j] * sin ((2 * PI * k * n) / SAMPLES));
	}
	parte_real = pow (parte_real, 2);
	parte_imaginaria = pow (parte_imaginaria, 2);
	magnitud = sqrt (parte_real + parte_imaginaria);
	return magnitud;
}

/*
obtener_fila (muestras)
Recibe: Arreglo que contiene las frecuencias de la tecla leida
Retorna: El número de fila donde se encuentra la tecla presionada
Efecto: Escoge la fila de la tecla que se presionó
Requerimientos: N/A
*/
int obtener_fila (float * muestras)
{
	float frecuencia_maxima = -100000;
	int i, fila = -1;
	for (i = 0; i < 4; i ++)
		if (muestras [i] > frecuencia_maxima)
		{
			frecuencia_maxima = muestras [i];
			fila = i;
		}
	return fila;
}

/*
obtener_columna (muestras)
Recibe: Arreglo que contiene las frecuencias de la tecla leida
Retorna: El número de columna donde se encuentra la tecla presionada
Efecto: Escoge la columna de la tecla que se presionó
Requerimientos: N/A
*/
int obtener_columna (float * muestras)
{
	float frecuencia_maxima = -100000;
	int i, columna = -1;
	for (i = 4; i < 8; i ++)
		if (muestras [i] > frecuencia_maxima)
		{
			frecuencia_maxima = muestras [i];
			columna = (i - 4);
		}
	return columna;
}
