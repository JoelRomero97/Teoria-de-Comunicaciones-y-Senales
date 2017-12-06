# DTMF

# NOTA: YA SE RECIBE EL SONIDO Y SE GUARDA EN UN ARCHIVO WAV, PERO EL CÓDIGO SE SUBIRÁ AL FINAL DEL SEMESTRE PARA EVITAR QUE ELIOTH LO ROBE DE NUEVO AL IGUAL QUE LAS PRÁCTICAS ANTERIORES

Por medio del análisis del análisis de Fourier para pasar del dominio del tiempo al dominio de las frecuencias se hace un análisis de muestras recibidas por la tarjeta de sonido en lenguaje C para identificar que número del teclado del teléfono presionó el usuario.

Este análisis se puede aplicar exactamente igual para hacer el reconocimiento de las vocales en alguna palabra que diga el usuario ya que se forma cada vocal por 3 frecuencias y 3 anchos de banda distintos.

# Compilación

- gcc Sonido.c -o Sonido -lasound

# Ejecución

- ./Sonido
- Presionar alguna número del teclado de un celular para captar el sonido (graba durante 2 segundos)

# Autor

Joel Mauricio Romero Gamarra
