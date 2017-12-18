#!/bin/bash

if [ -f Sonido ]; then
	rm Sonido
fi

if [ -f Funciones.o ]; then
	rm Funciones.o
fi

gcc Funciones.c -o Funciones.o -c -lm
gcc Sonido.c -o Sonido Funciones.o -lm -lasound
./Sonido