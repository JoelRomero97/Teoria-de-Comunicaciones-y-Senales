typedef struct CABECERA
{
	char ChunkID[4];					//Contiene las 'RIFF'
	int ChunkSize;						//Contiene el tamaño total sin contar este y el segmento anterior (8 bytes)
	unsigned char Format[4];			//Contiene 'WAVE'

	//Aqui comienza el primer subchunk 'fmt'
	char SubChunk1ID[4];				//Contiene 'fmt'
	int SubChunk1Size;					//Contiene el tamaño del resto de el primer subchunk
	short AudioFormat;					//Formato de audio, es es distinto de 1, es forma de compresión
	short NumChannels;					//Numero de canales, mono = 1, estereo = 2, etc.
	int SampleRate;						//8000, 44100, etc.
	int ByteRate;						//(SampleRate * Numero canales * Bits per Sample) / 8
	short BlockAlign;					//(Numero canales * Bits per Sample) / 8
	short BitsPerSample;				//8 bits, 16 bits, etc.
	
	//Aqui comienza el segundo subchunk 'data'
	char SubChunk2ID[4];				//Contiene 'data'
	int SubChunk2Size;					//Numero de bytes en los datos, es decir, bytes despues de este segmento
}cabecera;

FILE * abreArchivo (char * nombreArch, char * nombreModificado, int tipo);				//Para abrir los archivos de entrada y salida
void leerCabecera (FILE * archivoEntrada, FILE * archivoSalida, cabecera * cab);		//Para copiar e imprimir la cabecera
