# ITDF

En este programa, se realiza la implementación de la Transformada Discreta de Fourier Inversa en C para poder regresar una señal que se encuentra en el dominio de la frecuencia (utilizando la práctica anterior) al dominio del tiempo, gracias a esto se puede muestrear y reconstruir una señal multiplicando en la frecuencia y aplicando la ITDF a la señal resultante de la multiplicación.

# Compilación

- gcc Cabecera.c -o Cabecera.o -c
- gcc ITDF.c -o ITDF Cabecera.o

# Ejecución

- ./ITDF Entrada.wav Salida.wav

# Notas

- El archivo wav resultante será stereo (2 canales), sin embargo, se puede crear un programa simple que elimine en todas las muestras el segundo canal para quedarse únicamente con el canal izquierdo.
- Si se desea ejecutar el programa en Windows, deben comentarse las librerías sys/resource.h y sys/time.h, además, comentar las funciones uswtime y calculaTiempo.

# Autor

Joel Mauricio Romero Gamarra
