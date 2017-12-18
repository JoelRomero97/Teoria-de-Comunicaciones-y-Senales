#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Funciones.h"

struct sockaddr_in conectServer;

int main(int argc, char const *argv[])
{
	system ("clear");
	int i, flag, tam;
	int socketCliente,co,sendi,r,puerto,direccion_ip;
	char tecla, aux = 'z';
	unsigned int segundos;
	snd_pcm_t * manejador;
	snd_pcm_uframes_t muestras = SAMPLES;
	if (argc < 3)
	{
		printf ("Error, faltan parametros\n");
		printf ("Ejemplo: '%s 3905 127.0.0.1'\n\n", argv [0]);
		exit (0);
	}
	socketCliente = socket (AF_INET, SOCK_STREAM, 0);
	if (socketCliente < 0)
	{
		printf ("Error al crear el socket\n");
		exit (0);
	}
	memset ((void *)&conectServer, 0, sizeof (conectServer));
	conectServer.sin_family = AF_INET;
	conectServer.sin_port = htons (atoi (argv [1]));	
	conectServer.sin_addr.s_addr = inet_addr (argv [2]);
	co = connect (socketCliente, (struct sockaddr *)&conectServer, sizeof (conectServer));
	if (co < 0)
	{
		printf ("Error de conexion\n");
		exit (0);
	}
	manejador = establecer_parametros (manejador, &tam, &segundos);
	short * datos = (short *) malloc (sizeof (short) * tam);
	snd_pcm_prepare (manejador);
	while (segundos > 0)
	{
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
			{
				printf ("Tecla presionada: %c\n\n", tecla);
				sendi = send (socketCliente, (void *)&tecla, 1, 0);
				if (sendi < 0)
				{
					printf ("Error al enviar\n");
					exit (0);
				}
				if (tecla == '#')
					break;
			}else
				aux = tecla;
		}
	}
	//Ya que se obtiene el sonido, cerramos el manejador y el descriptor del socket
	snd_pcm_close (manejador);
	close (socketCliente);
	free (datos);
	return 0;
}
