#!/bin/bash
if [ -f DTMF ]; then
	rm DTMF
fi

if [ -f Funciones.o ]; then
	rm Funciones.o
fi

gcc Funciones.c -o Funciones.o -c -lm
gcc DTMF.c -o DTMF Funciones.o -lm -lasound
./DTMF 3905 127.0.0.1