#!/bin/bash
for N in {1..100}
do
    i=$(($RANDOM%10)) # numero aleatorio entre 0 y 100
    ./ProyFinalClient.o $i & # el & es para ejecutar sin esperar a que termine el proceso
done
wait # para esperar a todos los procesos ejecutados