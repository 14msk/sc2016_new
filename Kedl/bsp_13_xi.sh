#!/bin/bash
cd ~

#Bilder verkleinern und als .png-File speichern

for i in $( find ~/blatt_3/Kurs-C -type f -name "*.gif" ); do
    convert -resize 50% ${i} ${i%.gif}.png
done 

cd ~
exit 0
