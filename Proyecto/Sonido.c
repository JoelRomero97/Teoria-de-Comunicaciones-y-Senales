#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <unistd.h>
#include <string.h>
#include "Funciones.h"

int main(int argc, char const *argv[])
{
	system ("clear");
	int i, flag, tam;
	char tecla, aux = 'z';
	unsigned int segundos;
	snd_pcm_t * manejador;
	snd_pcm_uframes_t muestras = SAMPLES;
	manejador = establecer_parametros (manejador, &tam, &segundos);
	short * datos = (short *) malloc (sizeof (short) * tam);
	snd_pcm_prepare (manejador);
	while (segundos > 0)
	{
		//segundos = (segundos - 1);
		flag = snd_pcm_readi (manejador, datos, muestras);
		if (flag < 0)
		{
			printf ("\n\nNo fue posible recibir audio: %s\n\n", snd_strerror (flag));
			snd_pcm_prepare (manejador);
		}else if (flag == -EPIPE)
		{
			printf ("\n\nSe recibieron mas muestras de las esperadas: %s\n\n", snd_strerror (flag));
			snd_pcm_prepare (manejador);
		}else
		{
			tecla = tecla_presionada (datos);
			if (aux == tecla)
				printf ("Tecla presionada: %c\n\n", tecla);
			else
				aux = tecla;
		}
	}
	//Ya que se obtiene el sonido, cerramos el manejador
	snd_pcm_close (manejador);
	free (datos);
	return 0;
}
