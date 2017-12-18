# DTMF (Dual - Tone Multi - Frequency)

La marcación por tonos es utilizado por las telefonías para determinar que tecla fue presionada por el usuario, esto es gracias a que cada tecla está formada por 3 frecuencias, una por fila y otra por columna. Al aplicar la transformada de Fourier, podemos pasar al dominio de la frecuencia y determinar que frecuencia fue presionada, posteriormente, debemos encontrar la intersección de la frecuencia de la fila con la frecuencia de la columna y sabremos que digitó fue tecleado.

# Prerrequisitos

- sudo apt-get install libasound2-dev
- sudo apt-get install python-tk

# Ejecución (Servidor)

- python Servidor.py

# Compilación y ejecución (Cliente)

- chmod 777 Proyecto.sh
- ./Proyecto.sh

# Autores

Joel Mauricio Romero Gamarra

René Zavala Pérez
