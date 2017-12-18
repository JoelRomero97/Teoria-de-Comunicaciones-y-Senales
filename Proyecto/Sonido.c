#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <unistd.h>
#include "Funciones/Funciones.c"

int main(int argc, char const *argv[])
{
	system ("clear");
	int i, j, flag, muestras = 128;
	int tam;
	unsigned int canales = 2, latencia = 500000;
	int frecuencia = 44100;
	snd_pcm_t * manejador;
	snd_pcm_format_t formato = SND_PCM_FORMAT_S16_LE;			//Little Endian

	manejador = establecer_parametros (manejador);

	flag = snd_pcm_prepare (manejador);
	if (flag < 0)
	{
		printf ("\n\nNo fue posible preparar la interfaz de audio para usarse: %s\n", snd_strerror (flag));
		exit (1);
	}else
		printf ("Interfaz de audio lista.\n");

	tam = (((muestras * snd_pcm_format_width (formato)) / 8) * 2);
	short * datos = (short *) malloc (tam);

	for (i = 0; i < 10; i ++)
	{
		flag = snd_pcm_readi (manejador, datos, muestras);
		if (flag != muestras)
		{
			printf ("Error al recibir el audio: %s", snd_strerror (flag));
			exit (1);
		}else
		{
			for (j = 0; j < tam; j ++)
				if (datos [j] != 0)
					printf ("Muestra %d del ciclo %d: %d\n", (j + 1), (i + 1), datos [j]);
			printf ("\n\n");
		}
	}

	snd_pcm_close (manejador);
	return 0;
}
