# TDF

En este programa, se realiza la implementación de la Transformada Discreta de Fourier en C para poder observar una señal en el dominio de la frecuencia y poder comenzar a hacer el análisis para reconocer vocales o algún otro sonido por medio de sus frecuencias y picos por analizados con un diagrama de Bode.

# Compilación

- gcc Cabecera.c -o Cabecera.o -c
- gcc TDF.c -o TDF Cabecera.o

# Ejecución

- Opción 1: Muestra en el canal izquierdo la señal original y en el canal derecho la magnitud de la TDF
  - ./TDF -1 Entrada.wav Salida.wav

- Opción 2: Muestra en el canal izquierdo la parte real y en el canal derecho la parte imaginaria de la TDF
  - ./TDF -2 Entrada.wav Salida.wav

- Opción 3: Muestra en el canal izquierdo la magnitud y en el canal derecho la fase de la TDF
  - ./TDF -3 Entrada.wav Salida.wav

# Nota

- El costo del algoritmo que realiza la TDF es demasiado alto, esto será optimizado posteriormente realizando la Transformada Rápida de Fourier (FFT) utilizando menos operaciones y menos recursos de memoria.
- Si se desea ejecutar el programa en Windows, deben comentarse las librerías sys/resource.h y sys/time.h, además, comentar las funciones uswtime y calculaTiempo.

# Autor

Joel Mauricio Romero Gamarra
