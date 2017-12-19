#define TIEMPO 0.5
#define SAMPLES 22050
#define sample_rate 44100
#define PI 3.141592653589

snd_pcm_t * establecer_parametros (snd_pcm_t * manejador, int * tam, unsigned int * segundos);
char tecla_presionada (short * datos);
float TDF (short * datos, int k);
int obtener_fila (float * muestras);
int obtener_columna (float * muestras);
