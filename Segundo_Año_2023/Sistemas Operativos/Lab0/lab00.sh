#!/bin/bash

#Ejercicio 1
grep "model name" /proc/cpuinfo -m 1

#Ejercicio 2
grep "model name" /proc/cpuinfo | wc -l

#Ejercicio 3
wget https://www.gutenberg.org/files/11/11-0.txt && sed 's/Alice/Eduardo/g' 11-0.txt > Eduardo_in_wonderland.txt && rm 11-0.txt

#Ejercicio 4
#Temperatura maxima
sort -k 5 -n weather_cordoba.in | tail -1 | cut -d ' ' -f 1-3
#Temperatura minima
sort -k 6 -n weather_cordoba.in | head -1 | cut -d ' ' -f 1-3

#Ejercicio 5
sort -k 3 -n atpplayers.in

#Ejercicio 6
awk 'DG= $7-$8  {print $0, DG}' superliga.in | sort -k 2 -k 9 -n -r

#Ejercicio 7
ip link | grep 'link/ether' -i

#Ejercicio 8
#a)
mkdir Suits && for i in {1..10}; do touch Suits/sui_S01E"$i"_es.srt; done
#b)
cd Suits && for i in *_es.srt ;do mv -- "$i" "${i%_es.srt}.srt"; done


