#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct CABECERA
{
	unsigned char chunkID[4];
	unsigned int ChunkSize; 
	unsigned char format[4];
	unsigned char SubChunk1ID[4];
	unsigned int SubChunk1Size;
	unsigned int AudioFormat;
	unsigned int no_canal;
	unsigned int SimpleRate;
	unsigned int ByteRate;
	unsigned int block_align;
	unsigned int BitsPerSample;
	unsigned char SubChunk2ID[4];
	unsigned int SubChunk2Size;
	unsigned int data;
	
};

FILE *fp1, *fp2;
char *nombreArch;
char *nom_arch;
struct CABECERA cabecera;



int main(int argc, char const *argv[])
{
	unsigned char buffer4[4];
	unsigned char buffer2[2];
	unsigned char buf[1];
	unsigned char nombre_for[10];
	unsigned char *buffer;
	int data_ext_m1,valorsum;
	int comparacion1,comparacion2,comparacionf;
	int tamanio_total,i,j,contador,divisor4,a,valorMul,b;
	contador=0;
	char * nombreModificado = (char *) malloc (sizeof (char));
	char * nom_arch = (char *) malloc (sizeof (char));
	printf("Programa para bajar el volumen de un archivo wav\n");
	if (argc < 3)
	{
		printf("Error, faltan argumentos.\n");
	}else
	{
		nom_arch = (char *) argv [1];
		nombreModificado = (char *) argv [2];
	}
	// Se abre el archivo
	fp1=fopen(nom_arch,"rb");
	if (fp1 == NULL)
	{
		printf("Error al abrir archivo o el archivo no existe\n");
		exit(0);
	}
	else
		printf("Se abrio el archivo\n");
		
	fp2 = fopen(nombreModificado,"wb");
	if (fp2==NULL)
	{
		printf("No existe el archivo\n");
		exit(1);
	}
	else
		printf("Se creo el archivo modificado\n");
	int read = 0;
	
	//Lee la cabecera RIFF
	

	//ChunkID 
	read = fread(cabecera.chunkID,sizeof(cabecera.chunkID),1,fp1);
	printf("(1-4) chunkID: %s\n\n",cabecera.chunkID);
	read = fwrite (cabecera.chunkID, sizeof (cabecera.chunkID), 1, fp2);

	//ChunkSize 
	//Se convierten los datos a entero
	read = fread(buffer4, sizeof(buffer4),1,fp1);
	read = fwrite(buffer4, sizeof(buffer4),1,fp2);
	cabecera.ChunkSize = (buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24));
	printf("(5-8) ChunkSize:  %u\n\n",cabecera.ChunkSize);

	//Formato "format"
		
	read = fread(cabecera.format, sizeof(cabecera.format),1,fp1);
	printf("(9-12) Formato : %s\n\n",cabecera.format);
	read = fwrite (cabecera.format, sizeof (cabecera.format), 1, fp2);


	//SubChunk1ID formato de datos "fmt"
	
	read = fread(cabecera.SubChunk1ID,sizeof(cabecera.SubChunk1ID),1,fp1);
	printf("(13-16) SubChunk1ID: %s\n\n",cabecera.SubChunk1ID);
	read = fwrite (cabecera.SubChunk1ID, sizeof (cabecera.SubChunk1ID), 1, fp2);


	//SubChunk1Size
	read = fread(buffer4, sizeof(buffer4),1,fp1);
	read = fwrite(buffer4, sizeof(buffer4),1,fp2);
	cabecera.SubChunk1Size = buffer4[0] | (buffer4[1]<<8) | (buffer4[1]<<16) | (buffer4[1]<<24);	
	printf("(17-20) SubChunk1Size: %u\n\n",cabecera.SubChunk1Size);

	
	// Formato de audio

	read = fread(buffer2, sizeof(buffer2),1,fp1);
	read = fwrite(buffer2, sizeof(buffer2),1,fp2);
	cabecera.AudioFormat = buffer2[0] | (buffer2[1]<<8);
	if (cabecera.AudioFormat == 1)
		strcpy(nombre_for,"PCM");
	printf("(21-22) Formato de Audio: %u,%s\n\n",cabecera.AudioFormat,nombre_for);
	
	//Canales

	read = fread(buffer2, sizeof(buffer2),1,fp1);
	read = fwrite(buffer2, sizeof(buffer2),1,fp2);
	cabecera.no_canal = buffer2[0] | (buffer2[1]<<8);
	if (cabecera.no_canal == 1)
		strcpy(nombre_for,"Mono");
	else 
		strcpy(nombre_for,"Stereo");
	printf("(23-24) Numero de canal: %u, Tipo: %s\n\n",cabecera.no_canal,nombre_for);

	//SampleRate

	read = fread(buffer4, sizeof(buffer4),1,fp1);
	read = fwrite(buffer4, sizeof(buffer4),1,fp2);
	cabecera.SimpleRate = buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24);	
	printf("(25-28) SampleRate: %u\n\n",cabecera.SimpleRate);
	
	
	//ByteRate
	read = fread(buffer4, sizeof(buffer4),1,fp1);
	read = fwrite(buffer4, sizeof(buffer4),1,fp2);
	cabecera.ByteRate = buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24);	
	printf("(29-32) ByteRate: %u BitRate: %u\n\n",cabecera.ByteRate,cabecera.ByteRate*8);

	//Block Align
	read = fread(buffer2, sizeof(buffer2),1,fp1);
	read = fwrite(buffer2, sizeof(buffer2),1,fp2);
	cabecera.block_align = buffer2[0] | (buffer2[1]<<8);
	printf("(33-34) BlockAlign: %u\n\n",cabecera.block_align);

	//Bits per Sample
	read = fread(buffer2, sizeof(buffer2),1,fp1);
	read = fwrite(buffer2, sizeof(buffer2),1,fp2);
	cabecera.BitsPerSample = buffer2[0] | (buffer2[1]<<8);
	printf("(35-36) BitsPerSample: %u\n\n",cabecera.BitsPerSample);

	//SubChunk2ID
	read = fread(cabecera.SubChunk2ID,sizeof(cabecera.SubChunk2ID),1,fp1);
	printf("(37-40) SubChunk2ID: %s\n\n",cabecera.SubChunk2ID);
	read = fwrite(cabecera.SubChunk2ID,sizeof(cabecera.SubChunk2ID),1,fp2);


	//SubChunk2Size
	read = fread(buffer4, sizeof(buffer4),1,fp1);
	read = fwrite(buffer4, sizeof(buffer4),1,fp2);
	cabecera.SubChunk2Size = buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24);	
	printf("(41-44) SubChunk2Size: %u\n\n",cabecera.SubChunk2Size);	

	



	for(i=45;i<cabecera.SubChunk2Size;i++)
	{
		read = fread(buf, sizeof(buf),1,fp1);
		//buf [0] /= 2;
		read = fwrite(buf, sizeof(buf),1,fp2);
	}
	printf("\n");
	printf("Cerrando archivo original\n");
	printf("Cerrando archivo modificado\n");
	fclose(fp1);
	fclose(fp2);
}
