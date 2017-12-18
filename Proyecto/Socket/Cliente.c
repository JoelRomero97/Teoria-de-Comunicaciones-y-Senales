#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//SOCK_STREAM:llega todo pero lento
//SOCK_DGREAM:llega rapido pero no todos ni en orden 
struct sockaddr_in conectServer;

void main(int argc, char const *argv[])
{
	system("clear");
	int socketCliente,co,sendi,r,puerto,direccion_ip;
	char mensaje[100],mensaje2[100];
	//AF_INET paso 1 crear socket
	if (argc<3)
	{
		printf("Error:faltan parametros\n");
		exit(0);
	}

	socketCliente=socket(AF_INET,SOCK_STREAM,0);
	if(socketCliente<0)
	{
		printf("error:no se creo socket\n");
		exit(0);
	}
	//datos del servidor a conectar
	//paso 2 conectarse al servid
	memset((void *)&conectServer,0,sizeof(conectServer));
	conectServer.sin_family=AF_INET;
	conectServer.sin_port=htons(atoi(argv[1]));	
	conectServer.sin_addr.s_addr=inet_addr(argv[2]);
	co=connect(socketCliente,(struct sockaddr *)&conectServer,sizeof(conectServer));
	if(co<0)
	{
		printf("Error de conexion\n");
		exit(0);
	}
	//paso 3 enviar mensaje al servidor		
	while(1)
	{	
		printf("CLIENTE: ");
		scanf("%s",mensaje);
		//no es necesario hacer el cast
		sendi=send(socketCliente,(void *)&mensaje,strlen(mensaje),0);//regresa el numero de bytes
		if(sendi<0)
		{
			printf("Error al enviar\n");
			exit(0);
		}
		if(strcmp(mensaje,"#")==0)
		{
			break;
		}
	}
	shutdown(socketCliente,2);
	close(socketCliente);
}
