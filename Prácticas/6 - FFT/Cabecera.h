typedef struct CABECERA
{
	char ChunkID[4];		//Contiene 'RIFF'
	int ChunkSize;			//Contiene el tamaño total del archivo - 8 bytes
	char Format[4];			//Contiene 'WAVE'

	//Aqui comienza el primer subchunk 'fmt'
	char SubChunk1ID[4];	//Contiene 'fmt'
	int SubChunk1Size;		//Contiene el tamaño del primer subchunk
	short AudioFormat;		//Formato de audio
	short NumChannels;		//Numero de canales
	int SampleRate;			//Frecuencia de muestreo
	int ByteRate;			//(SampleRate * Numero canales * Bits per Sample) / 8
	short BlockAlign;		//Bytes por muestra
	short BitsPerSample;	//8 bits, 16 bits, etc.
	
	//Aqui comienza el segundo subchunk 'data'
	char SubChunk2ID[4];	//Contiene 'data'
	int SubChunk2Size;		//Numero de bytes en los datos
}cabecera;

void imprimir_cabecera (cabecera * cab);
void opcion_uno (FILE * salida, float * re, float * im, int numero_muestras);
void opcion_dos (FILE * salida, float * re, float * im, int numero_muestras);
void opcion_tres (FILE * salida, float * re, float * im, int numero_muestras);
void swap (float * a, float * b);
void uswtime (double * usertime, double * walltime);
void calculaTiempo (double utime0, double wtime0, double utime1, double wtime1, int n, int opcion);
