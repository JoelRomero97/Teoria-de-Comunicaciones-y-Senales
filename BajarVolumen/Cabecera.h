typedef struct CABECERA
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
	
}cabecera;

FILE * abreArchivo (char * nombreArch, char * nombreModificado, int tipo);
void leerCabecera (FILE * archivoEntrada, FILE * archivoSalida, cabecera * cab);