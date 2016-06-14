#!/bin/bash

cd ~/bsp_11/Kurs-C/Examples

#Compilieren mit g++
g++ Ex433.cpp
#File so editieren, dass ein Fehler beim Compilieren auftritt
echo "cout" >> Ex433.cpp
#Umlenken der Augabe in ein File
g++ Ex433.cpp > out.txt 2>&1
#Umlenken der Ausgabe sodass diese sowohl im Terminal als auch in out.txt erscheint
g++ Ex433.cpp 2>&1 | tee ~/blatt_3/out.txt 


cd ~
exit 0
