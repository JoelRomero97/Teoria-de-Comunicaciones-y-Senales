# Multiplicación

Este programa realiza la multiplicación de 2 señales, independientemente del formato, ya que puede ser monoaural (1 solo canal) o estereofónico (2 canales). 

En el caso del sonido mono, la multiplicación es como cualquier otra, se multiplica una muestra del primer archivo, por una muestra del segundo archivo y te da la primer muestra del archivo de salida hasta que se terminen las muestras.

Para el caso de un archivo estéreo, por la estructura de un archivo WAV, se realiza la multiplicación como un par de números complejos, siendo la primer muestra la parte real y la segunda muestra la parte imaginaria, dándonos como resultado la parte real y la parte imaginaria del archivo de salida.

# Compilación y ejecución

gcc Multiplicacion.c -o Multiplicacion

Multiplicacion.exe Archivo1.wav Archivo2.wav Archivo_Salida.wav

# Autor

Joel Mauricio Romero Gamarra
