#!/bin/bash
 
echo 'TIEMPOS CON LA TRANSFORMADA RAPIDA DE FOURIER' >> Tiempos.txt

#FFT

cd /home/joel/Escritorio/Señales/Transformada

gcc FFT.c -o FFT -lm

./FFT -2 Coseno32.wav FFT_Coseno32.wav >> Tiempos.txt

./FFT -2 Coseno64.wav FFT_Coseno64.wav >> Tiempos.txt

./FFT -2 Coseno128.wav FFT_Coseno128.wav >> Tiempos.txt

./FFT -2 Coseno256.wav FFT_Coseno256.wav >> Tiempos.txt

./FFT -2 Coseno512.wav FFT_Coseno512.wav >> Tiempos.txt

./FFT -2 Coseno1024.wav FFT_Coseno1024.wav >> Tiempos.txt

./FFT -2 Coseno2048.wav FFT_Coseno2048.wav >> Tiempos.txt

./FFT -2 Coseno4096.wav FFT_Coseno4096.wav >> Tiempos.txt

./FFT -2 Coseno8192.wav FFT_Coseno8192.wav >> Tiempos.txt

./FFT -2 Coseno16384.wav FFT_Coseno16384.wav >> Tiempos.txt

./FFT -2 Coseno32768.wav FFT_Coseno32768.wav >> Tiempos.txt

./FFT -2 Coseno65536.wav FFT_Coseno65536.wav >> Tiempos.txt

./FFT -2 Coseno131072.wav FFT_Coseno131072.wav >> Tiempos.txt