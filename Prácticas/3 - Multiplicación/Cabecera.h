typedef struct CABECERA
{
	char ChunkID[4];					//Contiene las 'RIFF'
	unsigned int ChunkSize;				//Contiene el tamaño total sin contar este y el segmento anterior (8 bytes)
	unsigned char Format[4];			//Contiene 'WAVE'

	//Aqui comienza el primer subchunk 'fmt'
	char SubChunk1ID[4];				//Contiene 'fmt'
	unsigned int SubChunk1Size;			//Contiene el tamaño del resto de el primer subchunk
	unsigned int AudioFormat;			//Formato de audio, es es distinto de 1, es forma de compresión
	unsigned int NumChannels;			//Numero de canales, mono = 1, estereo = 2, etc.
	unsigned int SampleRate;			//8000, 44100, etc.
	unsigned int ByteRate;				//(SampleRate * Numero canales * Bits per Sample) / 8
	unsigned int BlockAlign;			//(Numero canales * Bits per Sample) / 8
	unsigned int BitsPerSample;			//8 bits, 16 bits, etc.
	
	//Aqui comienza el segundo subchunk 'data'
	char SubChunk2ID[4];				//Contiene 'data'
	unsigned int SubChunk2Size;			//Numero de bytes en los datos, es decir, bytes despues de este segmento
}cabecera;

FILE * abreArchivo (char * archivo1, char * archivo2, char * salida, int tipo);
void leer_cabecera (FILE * archivo1, FILE * archivo2, cabecera * cab1, cabecera * cab2);
void imprimir_cabecera (cabecera * cab, int tipo);
void copiar_cabecera (cabecera * cab1, FILE * archivo1, FILE * salida);
