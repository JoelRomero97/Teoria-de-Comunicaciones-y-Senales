#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include "Funciones.h"

snd_pcm_t * establecer_parametros (snd_pcm_t * manejador)
{
	int flag;
	int resampling = 1;											//0 para deshabilitar
	unsigned int canales = 2, latencia = 500000;
	int frecuencia = 44100;
	char * dispositivo = "hw:0";
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
	flag = snd_pcm_hw_params_set_rate_near (manejador, hw_params, &frecuencia, 0);
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

	//Establecer los parametros de hardware y software en el manejador
	flag = snd_pcm_hw_params (manejador, hw_params);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible establecer los parametros de hardware y software: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("\nParametros de hardware y software establecidos correctamente.\n\n");

	//Ya que se establecieron todos los parametros, se libera la estructura
	snd_pcm_hw_params_free (hw_params);
	
	/*
	ESTABLECER LOS PARAMETROS DE HARDWARE EN 1 MISMA FUNCION
	flag = snd_pcm_set_params (manejador, formato, acceso, canales, frecuencia, resampling, latencia);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible establecer los parametros de hardware y software: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Parametros de hardware y software establecidos correctamente.\n");
	*/
	return manejador;
}
