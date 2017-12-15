#!/bin/bash
 
echo 'TIEMPOS CON LA TRANSFORMADA DISCRETA DE FOURIER' >> Tiempos.txt

#TDF

cd /home/joel/Escritorio/Señales/Transformada
gcc TDF.c -o TDF -lm

./TDF -2 Coseno32.wav TDF_Coseno32.wav >> Tiempos.txt
./TDF -2 Coseno64.wav TDF_Coseno64.wav >> Tiempos.txt
./TDF -2 Coseno128.wav TDF_Coseno128.wav >> Tiempos.txt
./TDF -2 Coseno256.wav TDF_Coseno256.wav >> Tiempos.txt
./TDF -2 Coseno512.wav TDF_Coseno512.wav >> Tiempos.txt
./TDF -2 Coseno1024.wav TDF_Coseno1024.wav >> Tiempos.txt
./TDF -2 Coseno2048.wav TDF_Coseno2048.wav >> Tiempos.txt
./TDF -2 Coseno4096.wav TDF_Coseno4096.wav >> Tiempos.txt
./TDF -2 Coseno8192.wav TDF_Coseno8192.wav >> Tiempos.txt
./TDF -2 Coseno16384.wav TDF_Coseno16384.wav >> Tiempos.txt
./TDF -2 Coseno32768.wav TDF_Coseno32768.wav >> Tiempos.txt
./TDF -2 Coseno65536.wav TDF_Coseno65536.wav >> Tiempos.txt
./TDF -2 Coseno131072.wav TDF_Coseno131072.wav >> Tiempos.txt

cd /home/joel/Escritorio/Señales/Transformada

chmod 777 FFT.sh

./FFT.sh