# Convolución

Este programa realiza un filtrado de una señal en el dominio de la frecuencia, haciendo uso del concepto de convolución obteniendo la respuesta al impulso de un filtro RC en configuración pasa bajas (dejando pasar las frecuencias por debajo de la frecuencia de corte y eliminando las frecuencias por encima de la misma) para pasar toda la señal en bloques de 20 por el filtro digital eliminando las frecuencias no deseadas (en este caso, la frecuencia de corte es de 1 KHz).

NOTA: El costo del algoritmo que realiza la convolución es demasiado alto, esto puede ser optimizado utilizando la transformada Z (tanto en memoria como en número de operaciones).

# Compilación y ejecución

gcc Convolucion.c -o Convolucion

Convolucion.exe Archivo_Original.wav Archivo_Filtrado.wav

# Autor

Joel Mauricio Romero Gamarra
