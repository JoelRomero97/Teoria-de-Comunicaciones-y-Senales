#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <string.h>
#include "Funciones.h"
#define TIEMPO 1
#define sample_rate 44100

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
	char * dispositivo = "hw:0";
	snd_pcm_uframes_t muestras = 32;
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
	*tam = (muestras * 4);

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
generar_archivo_wav (datos)
Recibe: Arreglo que contiene los datos a escribir
Retorna: N/A
Efecto: Escribir los datos en un archivo wav eliminando los datos leídos del segundo canal (se convierte de un archivo stereo a un archivo mono)
Requerimientos: Conocer la estructura de un archivo wav y como crear uno
*/
void generar_archivo_wav (short * datos)
{
	cabecera cab;
	strcpy (cab.ChunkID, "RIFF");								//Especificacion de archivos multimedia
	//cab.ChunkSize = tam_total;								//Tamaño total del archivo - 8 bytes
	strcpy (cab.Format, "WAVE");								//Describe el formato del archivo (subchunk fmt y data)
	strcpy (cab.SubChunk1ID, "fmt ");							//Describe el formato de los datos
	//cab.SubChunk1Size = tam_subchunk_fmt;						//Tamaño del subchunk fmt
	cab.AudioFormat = 1;										//PCM
	cab.NumChannels = 1;										//Archivo Mono
	cab.SampleRate = sample_rate;								//Frecuencia de muestreo
	cab.ByteRate = ((sample_rate * 16) / 8);					//(SampleRate * NumChannels * BitsPerSample) / 8
	cab.BlockAlign = 2;											//(NumChannels * BitsPerSample) / 8
	cab.BitsPerSample = 16;										//2 bytes (short) = 16 bits
	strcpy (cab.SubChunk2ID, "data");							//Identificador del ultimo subchunk
	//cab.SubChunk2Size = tam_datos;							//Datos totales sin contar la cabecera
}
