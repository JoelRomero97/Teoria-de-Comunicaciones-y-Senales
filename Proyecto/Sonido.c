#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <unistd.h>
#include "Funciones/Funciones.c"

int main(int argc, char const *argv[])
{
	system ("clear");
	int i, flag;
	int tam;
	unsigned int segundos;
	snd_pcm_t * manejador;
	snd_pcm_uframes_t muestras = 32;

	manejador = establecer_parametros (manejador, &tam, &segundos);

	char * datos = (char *) malloc (sizeof (char) * tam);

	while (segundos > 0)
	{
		segundos = (segundos - 1);
		flag = snd_pcm_readi (manejador, datos, muestras);
		if (flag < 0)
		{
			printf ("\n\nNo fue posible recibir audio: %s\n\n", snd_strerror (flag));
			exit (1);
		}else if (flag == -EPIPE)
		{
			printf ("\n\nSe recibieron mas muestras de las esperadas: %s\n\n", snd_strerror (flag));
			exit (1);
		}
	}
	snd_pcm_close (manejador);
	return 0;
}
