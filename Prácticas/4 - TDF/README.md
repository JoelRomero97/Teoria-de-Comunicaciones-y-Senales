# TDF

# NOTA: PRÁCTICA COMPLETA, SIN EMBARGO, EL CÓDIGO SE SUBIRÁ AL CONCLUIR EL SEMESTRE PARA QUE NO LO VUELVAN A COPIAR XD

En este programa, se realiza la implementación de la Transformada Discreta de Fourier en C para poder observar una señal en el dominio de la frecuencia y poder comenzar a hacer el análisis para reconocer vocales o algún otro sonido por medio de sus frecuencias y picos por analizados con un diagrama de Bode.

NOTA: El costo del algoritmo que realiza la TDF es demasiado alto, esto será optimizado posteriormente realizando la Transformada Rápida de Fourier (FFT) utilizando menos operaciones y menos recursos de memoria.

# Compilación

gcc TDF.c -o TDF

# Ejecución

- Opción 1: Muestra en el canal izquierdo la señal original y en el canal derecho la magnitud de la TDF
  - TDF.exe -1 Entrada.wav Salida.wav

- Opción 2: Muestra en el canal izquierdo la parte real y en el canal derecho la parte imaginaria de la TDF
  - TDF.exe -2 Entrada.wav Salida.wav

- Opción 3: Muestra en el canal izquierdo la magnitud y en el canal derecho la fase de la TDF
  - TDF.exe -3 Entrada.wav Salida.wav

# Autor

Joel Mauricio Romero Gamarra
