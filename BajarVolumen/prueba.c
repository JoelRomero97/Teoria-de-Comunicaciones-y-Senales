#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct CABECERA
{
  unsigned char riff[4];
  unsigned int tam; 
  unsigned char wave[4];
  unsigned char fmt[4];
  unsigned int tam_formato;
  unsigned int tipo_formato;
  unsigned int no_canal;
  unsigned int frecuencia_muestreo;
  unsigned int rango_byte;
  unsigned int block_align;
  unsigned int bits_onda;
  unsigned char data[4];
  unsigned int tam_data;
} cabecera;

int main()
{
  system ("cls");
  int lectura = 0;
  cabecera cab;
  unsigned int x;
  unsigned char buffer4[4], buffer2 [2];
  char nombre_for[10] = "";
  FILE *ptOriginal, *ptModificado;
  
  printf("\n\nPrograma para bajar el volumen de un archivo wav\n\n\n");
  ptOriginal = fopen("Entrada.wav","rb");                                            //Abrimos el archivo
  if (ptOriginal == NULL)
  {
    printf("Error al abrir archivo\n");
    exit(0);
  }
  
  ptModificado = fopen("Modificado.wav","w");
  if (ptModificado == NULL)
  {
    printf("Error al abrir archivo\n");
    exit(0);
  }
  
  lectura = fread(cab.riff, sizeof(cab.riff), 1, ptOriginal);                        //Leemos el primer argumento de la cabecera
  lectura = fwrite (cab.riff, sizeof (cab.riff), 1, ptModificado);
  printf("(1-4) RIFF: %s\n",cab.riff);                                                //Imprimimos el valor del formato (RIFF)

  lectura = fread(buffer4, sizeof(buffer4), 1, ptOriginal);                           //Guardamos los siguientes 4 bytes
  lectura = fwrite (buffer4, sizeof (buffer4), 1, ptModificado);
  printf("%u, %u, %u, %u\n",buffer4[0],buffer4[1],buffer4[2],buffer4[3]);             //Imprimimos los 4 bytes leídos
  cab.tam = ((buffer4[0]) | (buffer4[1] << 8) | (buffer4[2] << 16) | (buffer4[3] << 24));
  printf("(5-8) Tamaño del RIFF: %u bytes.\n",cab.tam);

  lectura = fread(cab.wave, sizeof(cab.wave), 1, ptOriginal);                         //Leemos los siguientes 4 bytes
  lectura = fwrite (cab.wave, sizeof (cab.wave), 1, ptModificado);
  printf("(9-12) Onda : %s\n",cab.wave);                                              //Imprimimos bytes leídos

  lectura = fread(cab.fmt, sizeof(cab.fmt), 1, ptOriginal);
  lectura = fwrite (cab.fmt, sizeof (cab.fmt), 1, ptModificado);
  printf("(13-16) Fmt: %s\n", cab.fmt);

  lectura = fread(buffer4, sizeof(buffer4), 1, ptOriginal);                           //Leemos los siguientes 4 bytes
  lectura = fwrite (buffer4, sizeof (buffer4), 1, ptModificado);
  printf("%u, %u, %u, %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);         //Imprimimos bytes leídos
  cab.tam_formato = ((buffer4[0]) | (buffer4[1] << 8) | (buffer4[2] << 16) | (buffer4[3] << 24));
  printf("(17-20) Tamaño formato: %u\n",cab.tam_formato);

  lectura = fread (buffer2, sizeof(buffer2), 1, ptOriginal);
  lectura = fwrite (buffer2, sizeof (buffer2), 1, ptModificado);
  printf("%u, %u\n", buffer2[0], buffer2[1]);
  cab.tipo_formato = (buffer2[0] | (buffer2[1]<<8));
  if (cab.tipo_formato == 1)
    strcpy(nombre_for, "PCM");
  else if (cab.tipo_formato == 6)
    strcpy(nombre_for,"A-law");
  else if (cab.tipo_formato == 7)
    strcpy(nombre_for,"Mu-law");
  else 
    strcpy (nombre_for, "ERROR EN tipo_formato");
  printf("(21-22) Tipo de Formato: %u, %s\n", cab.tipo_formato, nombre_for);

  lectura = fread(buffer2, sizeof(buffer2),1,ptOriginal);
  lectura = fwrite (buffer2, sizeof (buffer2), 1, ptModificado);
  printf("%u, %u\n",buffer2[0],buffer2[1]);
  cab.no_canal = ((buffer2[0]) | (buffer2[1]<<8));
  printf("(23-24) Numero de canal: %u\n", cab.no_canal);

  lectura = fread(buffer4, sizeof(buffer4), 1, ptOriginal);
  lectura = fwrite (buffer4, sizeof (buffer4), 1, ptModificado);
  printf("%u, %u, %u, %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);
  cab.frecuencia_muestreo = ((buffer4[0]) | (buffer4[1] << 8) | (buffer4[2] << 16) | (buffer4[3] << 24));
  printf("(25-28) Frecuencia de onda: %u\n",cab.frecuencia_muestreo);

  lectura = fread(buffer4, sizeof(buffer4), 1, ptOriginal);
  lectura = fwrite (buffer4, sizeof (buffer4), 1, ptModificado);
  printf("%u, %u, %u, %u\n",buffer4[0],buffer4[1],buffer4[2],buffer4[3]);
  cab.rango_byte = ((buffer4[0]) | (buffer4[1]<<8) | (buffer4[2]<<16) | (buffer4[3]<<24));
  printf("(29-32) Rango de byte: %u Rango de Bit: %u\n",cab.rango_byte, cab.rango_byte * 8);

  lectura = fread(buffer2, sizeof(buffer2), 1, ptOriginal);
  lectura = fwrite (buffer2, sizeof (buffer2), 1, ptModificado);
  printf("%u, %u\n",buffer2[0],buffer2[1]);
  cab.block_align = ((buffer2[0]) | (buffer2[1]<<8));
  printf("(33-34) Espacio de bloque: %u\n",cab.block_align);

  lectura = fread(buffer2, sizeof(buffer2),1,ptOriginal);
  lectura = fwrite (buffer2, sizeof (buffer2), 1, ptModificado);
  printf("%u, %u\n",buffer2[0],buffer2[1]);
  cab.bits_onda = ((buffer2[0]) | (buffer2[1]<<8));
  printf("(35-36) Bits por onda: %u\n",cab.bits_onda);

  lectura = fread(cab.data, sizeof(cab.data), 1, ptOriginal);                        //Leemos el primer argumento de la cabecera
  lectura = fwrite (cab.data, sizeof (cab.data), 1, ptModificado);
  printf("(37-40) Data: %s\n",cab.data);

  lectura = fread(buffer4, sizeof(buffer4), 1, ptOriginal);
  lectura = fwrite (buffer4, sizeof (buffer4), 1, ptModificado);
  printf("%u, %u, %u, %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);
  cab.tam_data = ((buffer4[0]) | (buffer4[1] << 8) | (buffer4[2] << 16) | (buffer4[3] << 24));
  printf("(41-44) Tam_data: %u\n",cab.tam_data);

  fclose (ptModificado);
  fclose(ptOriginal);
}
